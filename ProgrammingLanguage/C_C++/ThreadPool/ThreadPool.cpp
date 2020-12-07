#include "ThreadPool.h"

#include <iostream>

ThreadPool::ThreadPool()
: m_mutex()
, m_cv()
, m_isStarted(false)
{
    
}

ThreadPool::~ThreadPool()
{
    if (m_isStarted)
    {
        stop();
    }
}

void ThreadPool::start()
{
    for (int i = 0; i < 3; ++i)
    {
        m_threads.push_back(new std::thread(std::bind(&ThreadPool::threadLoop, this)));
    }
    m_isStarted = true;
}

void ThreadPool::stop()
{
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_isStarted = false;
        m_cv.notify_all();
    }
    
    for (auto& th : m_threads)
    {
        th->join();
        delete th;
    }
    m_threads.clear();
}

void ThreadPool::threadLoop()
{
    while (m_isStarted)
    {
        Task task = take();
        if (task)
        {
            task();
        }
    }
}

void ThreadPool::addTask(const Task& task)
{
    std::unique_lock<std::mutex> lck(m_mutex);
    TaskPair taskPair(Middle, task);
    m_tasks.push(taskPair);
    m_cv.notify_one();
}

void ThreadPool::addTask(const TaskPair& taskPair)
{
    std::unique_lock<std::mutex> lck(m_mutex);
    m_tasks.push(taskPair);
    m_cv.notify_one();
}

bool ThreadPool::pred()
{
    return !(m_tasks.empty() && m_isStarted);
}

ThreadPool::Task ThreadPool::take()
{
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_cv.wait(lck, std::bind(&ThreadPool::pred, this));
    }
    Task task;
    Tasks::size_type size = m_tasks.size();
    if (!m_tasks.empty() && m_isStarted)
    {
        task = m_tasks.top().second;
        m_tasks.pop();
    }
    
    return task;
}

void ThreadPoolTest::testMain()
{
    start();
    addTask(std::bind(&ThreadPoolTest::print, this));
    addTask(std::bind(&ThreadPoolTest::print, this));
    addTask(std::bind(&ThreadPoolTest::print, this));
    addTask(std::bind(&ThreadPoolTest::print, this));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    stop();
}

void ThreadPoolTest::print()
{
    std::cout << "Hello world!" << std::endl;
}