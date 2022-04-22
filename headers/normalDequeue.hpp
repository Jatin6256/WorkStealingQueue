#ifndef NORMALDEQUEUE_HPP
#define NORMALDEQUEUE_HPP
#include<atomic>
#include "./dequeue.hpp"
#include "./circularArray.hpp"
#include <queue>

class NormalDequeue: public Dequeue {
    
    std::deque<RunnableTask*>* tasks;
    static const bool debugMode = false; 

    public:
        NormalDequeue();
        void pushBottom(RunnableTask* task);
        RunnableTask* popBottom();
        bool isEmpty();
        RunnableTask* popTop();

};
#endif