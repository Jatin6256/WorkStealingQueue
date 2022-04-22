#include<iostream>
#include "../headers/normalDequeue.hpp"

// UnboundedDequeue::UnboundedDequeue() {}

NormalDequeue::NormalDequeue()
{
    tasks = new std::deque<RunnableTask*>();
    if(debugMode)
        std::cout << "NormalDequeue constructor line 7 NormalDequeue.cpp" << "\n";
}

bool NormalDequeue::isEmpty()
{
    // std::cout << "UnboundedDequeue isEmpty line 16 UnboundedDequeue.cpp" << "\n";
    return tasks -> empty();

}

void NormalDequeue::pushBottom(RunnableTask *task)
{
    if(debugMode)
        std::cout << "NormalDequeue pushBottom() line 18 NormalDequeue.cpp" << "\n";
    tasks -> push_back(task);
}


RunnableTask* NormalDequeue::popTop()
{
    if (debugMode)
        std::cout << "NormalDequeue popTop() line 24 NormalDequeue.cpp" << "\n";
    RunnableTask* r = tasks -> front();
    tasks -> pop_front();
    return r;
}


RunnableTask* NormalDequeue::popBottom()
{
    if (debugMode)
        std::cout << "NormalDequeue popBottom() line 30 NormalDequeue.cpp" << "\n";
    if(tasks -> empty())
        return nullptr;
    RunnableTask* r = tasks -> back();
    tasks -> pop_back();
    return r;
}
