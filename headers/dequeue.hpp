#ifndef DEQUEUE_HPP
#define DEQUEUE_HPP
#include "./runnableTask.hpp"

class Dequeue {
    public:
        virtual void pushBottom(RunnableTask* task) = 0;
        virtual RunnableTask* popBottom() = 0;
        virtual bool isEmpty() = 0;
        virtual RunnableTask* popTop() = 0;
        
};

#endif