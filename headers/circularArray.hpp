#ifndef CIRCULARARRAY_HPP
#define CIRCULARARRAY_HPP
#include "./runnableTask.hpp"

class CircularArray
{

private:
    int logCapacity;
    RunnableTask **currentTasks;
    static const bool debugMode = true;

public:
    CircularArray();
    CircularArray(int capacity);
    int capacity();
    RunnableTask *get(int index);
    void put(RunnableTask *task, int index);
    CircularArray *resize(int bottom, int top);
};

#endif