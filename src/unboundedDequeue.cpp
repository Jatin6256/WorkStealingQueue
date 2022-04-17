#include<iostream>
#include "../headers/unboundedDequeue.hpp"

// UnboundedDequeue::UnboundedDequeue() {}

UnboundedDequeue::UnboundedDequeue()
{
    std::cout << "UnboundedDequeue constructor line 7 UnboundedDequeue.cpp" << "\n";
    LOG_CAPACITY = 4;
    tasks = new CircularArray(4);
    top = new std::atomic<int>(0);
}

bool UnboundedDequeue::isEmpty()
{
    // std::cout << "UnboundedDequeue isEmpty line 16 UnboundedDequeue.cpp" << "\n";
    int localTop = top->load();
    int localBottom = bottom;
    return (localBottom <= localTop);
}

void UnboundedDequeue::pushBottom(RunnableTask *task)
{
    std::cout << "UnboundedDequeue pushBottom() line 24 UnboundedDequeue.cpp" << "\n";
    int oldBottom = bottom;
    int oldTop = top->load();
    CircularArray *currentTasks = tasks;
    int size = oldBottom - oldTop;
    if (size >= currentTasks->capacity() - 1)
    {
        currentTasks = currentTasks->resize(oldBottom, oldTop);
        tasks = currentTasks;
    }
    tasks->put(task, oldBottom);
    bottom = oldBottom + 1;
}

RunnableTask *UnboundedDequeue::popTop()
{
    std::cout << "UnboundedDequeue popTop() line 40 UnboundedDequeue.cpp" << "\n";
    int oldTop = top->load();
    int newTop = oldTop + 1;
    int oldBottom = bottom;
    CircularArray *currentTasks = tasks;
    int size = oldBottom - oldTop;
    if (size <= 0)
        return nullptr;
    RunnableTask *r = tasks->get(oldTop);
    if (top->compare_exchange_strong(oldTop, newTop))
        return r;
    return nullptr;
}

RunnableTask *UnboundedDequeue::popBottom()
{
    std::cout << "UnboundedDequeue popBottom() line 56 UnboundedDequeue.cpp" << "\n";
    CircularArray* currentTasks = tasks;
    bottom--;
    int oldTop = top -> load();
    int newTop = oldTop + 1;
    int size = bottom - oldTop;
    if (size < 0)
    {
        bottom = oldTop;
        return nullptr;
    }
    RunnableTask *r = tasks -> get(bottom);
    if (size > 0)
        return r;
    if (!top -> compare_exchange_strong(oldTop, newTop))
        r = nullptr;
    bottom = oldTop + 1;
    return r;
}