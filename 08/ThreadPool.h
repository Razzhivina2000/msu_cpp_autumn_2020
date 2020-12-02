#pragma once

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

