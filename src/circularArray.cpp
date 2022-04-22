#include "../headers/circularArray.hpp"
#include<iostream>
CircularArray::CircularArray() {}

CircularArray::CircularArray(int capacity) {
    if (debugMode)
        std::cout << "CircularArray Constructor run line 14 CircularArray.cpp" << "\n";
    logCapacity = capacity;
    currentTasks = new RunnableTask*[1 << logCapacity];
}

int CircularArray::capacity() {
    if (debugMode)
        std::cout << "CircularArray capacity() run line 12 CircularArray.cpp" << "\n";
    return 1 << logCapacity;
}

RunnableTask* CircularArray::get(int i){
    if (debugMode)
        std::cout << "CircularArray get() run line 17 CircularArray.cpp" << "\n";
    return currentTasks[i % capacity()];
}

void CircularArray::put(RunnableTask* task, int i) {
    if (debugMode)
        std::cout << "CircularArray put run line 22 CircularArray.cpp" << "\n";
    currentTasks[i % capacity()] = task;
}

CircularArray* CircularArray::resize(int bottom, int top) {
    if (debugMode)
        std::cout << "CircularArray resize() run line 27 CircularArray.cpp" << "\n";
    CircularArray* newTasks = new CircularArray(logCapacity + 1);
    for (int i = top; i < bottom; i++) {
        newTasks->put(get(i), i);
    }
    return newTasks;
}