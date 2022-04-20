#include<iostream>
#include "../headers/boundedDequeue.hpp"
#include "../headers/runnableTask.hpp"

BoundedDequeue::BoundedDequeue() {}

BoundedDequeue::BoundedDequeue(int capacity)
{
    std::cout << "BoundedDequeue constructor line 7 boundedDequeue.cpp" << "\n";
    tasks = new RunnableTask*[capacity];
    StampedReference<int> topInput;
    top = new std::atomic<StampedReference<int>>(topInput);
    bottom = 0;
}

bool BoundedDequeue::isEmpty()
{
    std::cout << "BoundedDequeue isEmpty line 15 boundedDequeue.cpp" << "\n";
    int localTop = top->load().value;
    int localBottom = bottom;
    return (localBottom <= localTop);
}

void BoundedDequeue::pushBottom(RunnableTask *task)
{
    std::cout << "BoundedDequeue pushBottom() line 23 boundedDequeue.cpp" << "\n";
    tasks[bottom] = task;
    bottom++;
}

RunnableTask *BoundedDequeue::popTop()
{
    std::cout << "BoundedDequeue popTop() line 30 boundedDequeue.cpp" << "\n";
    StampedReference<int> oldTop = top->load();
    StampedReference<int>  newTop(oldTop.value+1, oldTop.stamp+1);
    
    if(bottom <= oldTop.value)
        return nullptr;

    RunnableTask *r = tasks[oldTop.value];

    if (top->compare_exchange_strong(oldTop, newTop))
        return r;
    return nullptr;
}

RunnableTask *BoundedDequeue::popBottom()
{
    std::cout << "BoundedDequeue popBottom() line 46 boundedDequeue.cpp" << "\n";
    if(bottom == 0)
        return nullptr;
    bottom--;

    RunnableTask *r = tasks[bottom];
    
    StampedReference<int> oldTop = top->load();
    StampedReference<int>  newTop(0, oldTop.stamp+1);

    if (bottom > oldTop.value)
        return r;

    if(bottom == oldTop.value){
        bottom = 0;
        if (top->compare_exchange_strong(oldTop, newTop))
            return r;
    }
    top->store(newTop);
    return nullptr;
}