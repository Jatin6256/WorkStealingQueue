#ifndef BOUNDEDEQUEUE_HPP
#define BOUNDEDDEQUEUE_HPP
#include <atomic>
#include "./dequeue.hpp"
#include "./runnableTask.hpp"

template <typename T>
struct StampedReference{
    T value;
    int stamp;
    StampedReference() : value(0), stamp(0){};
    StampedReference(T value, int stamp) : value(value), stamp(stamp){};
};

class BoundedDequeue: public Dequeue {
    RunnableTask* tasks;
    volatile int bottom;
    std::atomic<StampedReference<int>>* top;
    public:
        BoundedDequeue();
        BoundedDequeue(int capacity);
        void pushBottom(RunnableTask* task);
        RunnableTask* popBottom();
        bool isEmpty();
        RunnableTask* popTop();

};
#endif