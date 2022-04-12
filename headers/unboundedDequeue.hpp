#ifndef UNBOUNDEDEQUEUE_HPP
#define UNBOUNDEDDEQUEUE_HPP
#include<atomic>
#include "./dequeue.hpp"
#include "./circularArray.hpp"

class UnboundedDequeue: public Dequeue {
    int LOG_CAPACITY;
    volatile int bottom;
    std::atomic<int>* top;
    // TODO make it volatile
    CircularArray* tasks;
    public:
        UnboundedDequeue();
        UnboundedDequeue(int capacity);
        void pushBottom(RunnableTask* task);
        RunnableTask* popBottom();
        bool isEmpty();
        RunnableTask* popTop();

};
#endif