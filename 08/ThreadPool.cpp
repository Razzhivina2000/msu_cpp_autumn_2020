#include <iostream>
#include <vector>
#include <mutex>
#include <future>
#include <queue>
#include <condition_variable>
#include <unistd.h>
#include "ThreadPool.h"

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
