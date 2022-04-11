#include<atomic>
#include "./dequeue.hpp"

class UnboundedDequeue: public Dequeue {
    static int LOG_CAPACITY;
    volatile int bottom;
    std::atomic<int> top;
    public:
        UnboundedDequeue();
        UnboundedDequeue(int capacity);
        void pushBottom(RunnableTask* task);
        RunnableTask* popBottom();
        bool isEmpty();
        RunnableTask* popTop();

};