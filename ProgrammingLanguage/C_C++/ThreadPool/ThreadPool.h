#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <vector>
#include <utility>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPool
{
public:
    enum TaskPrioE { Low, Middle, High };
    using Task = std::function<void()>;
    using TaskPair = std::pair<TaskPrioE, Task>;
    
    ThreadPool();
    ~ThreadPool();
    
    void start();
    void stop();
    void addTask(const Task&);
    void addTask(const TaskPair&);
    
private:
    struct TaskPriorityCmp
    {
        bool operator()(const ThreadPool::TaskPair& p1, const ThreadPool::TaskPair& p2)
        {
            return p1.first > p2.first;
        }
    }
    using Threads = std::vector<std::thread*>;
    using Tasks = std::priority_queue<TaskPair, std::vector<TaskPair>, TaskPriorityCmp>;
    ThreadPool(const ThreadPool&) = delete;
    const ThreadPool& operator=(const ThreadPool&) = delete;
    
    void threadLoop();
    Task take();
    bool pred();
    
    Threads m_threads;
    Tasks m_tasks;
    
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_isStarted;
};

void ThreadPoolTest : public ThreadPool
{
public:
    ThreadPoolTest() {}
    ~ThreadPoolTest() {}
    
    void testMain();

private:
    void print();
};
#endif // THREAD_POOL_H_