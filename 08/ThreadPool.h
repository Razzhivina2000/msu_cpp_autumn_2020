#pragma once

#include <vector>
#include <mutex>
#include <future>
#include <queue>
#include <condition_variable>
#include <unistd.h>

class ThreadPool
{
    size_t poolSize;
    std::mutex m;
    std::condition_variable v;
    std::queue<std::packaged_task<void()>> tasks;
    std::vector<std::future<void>> pool;
    
    void work();
    
public:
    explicit ThreadPool(size_t poolSize) : poolSize(poolSize) {
        for(size_t i = 0; i < poolSize; ++i) {
            pool.push_back(std::async( std::launch::async, [this]{ work(); } ));
        }
    }

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
    
    ~ThreadPool();
};


void ThreadPool::work() {
    while(true) {
        std::packaged_task<void()> func;
        {
            std::unique_lock<std::mutex> lock(m);
            while(tasks.empty()) {
                v.wait(lock);
            }
            func = std::move(tasks.front());
            tasks.pop();
        }
        func();
     }
}

template <class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))> {

    auto task = std::make_shared< std::packaged_task<typename std::result_of<Func(Args...)>::type()> > (std::bind(std::forward<Func>(func), std::forward<Args>(args)...));

    auto result = task->get_future();
    {
        std::unique_lock<std::mutex> lock(m);
        tasks.emplace([task]() { (*task)(); });
    }
    v.notify_one();
    return result;
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> l(m);
        for(size_t i = 0; i < poolSize; ++i) {
            tasks.push({});
        }
    }
    v.notify_all();
    pool.clear();
}


