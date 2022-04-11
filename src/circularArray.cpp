#include "../headers/circularArray.hpp"
CircularArray::CircularArray() {}

CircularArray::CircularArray(int capacity) {
    logCapacity = capacity;
    currentTasks = new RunnableTask*[1 << logCapacity];
}

int CircularArray::capacity() {
    return 1 << logCapacity;
}

RunnableTask* CircularArray::get(int i){
    return currentTasks[i % capacity()];
}

void CircularArray::put(RunnableTask* task, int i) {
    currentTasks[i % capacity()] = task;
}

CircularArray* CircularArray::resize(int bottom, int top) {
    CircularArray* newTasks = new CircularArray(logCapacity + 1);
    for (int i = top; i < bottom; i++) {
        newTasks->put(get(i), i);
    }
    return newTasks;
}