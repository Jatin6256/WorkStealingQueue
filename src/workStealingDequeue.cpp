#include "../headers/workStealingDequeue.hpp"
#include "thread"

WorkStealingDequeues::WorkStealingDequeues(Dequeue** myQueue, int l)
{
    std::cout << "WorkStealingDequeues constructor line 6 WorkStealingDequeues.cpp" << "\n";
    queue = myQueue;
    length = l;
    srand(time(0));
}

void WorkStealingDequeues::run(int id)
{
    std::cout << "WorkStealingDequeues run line 14 WorkStealingDequeues.cpp" << "\n";
    std::cout << (std::this_thread::get_id()) << "\n";
    int me = id;
    RunnableTask *task = queue[me] -> popBottom();
    while (true)
    {
        while (task != nullptr)
        {
            task->run();
            task = queue[me] -> popBottom();
        }
        int count = length;
        while (task == nullptr && count > 0)
        {
            // TODO
            // Thread.yield();
            std::this_thread::yield();
            int victim = rand() % length;
            while (victim == me)
            {
                victim = rand() % length;
            }

            if (!queue[victim] -> isEmpty())
            {
                task = queue[victim] -> popTop();
                // count = length;
            }

            count--;
        }
    }
}