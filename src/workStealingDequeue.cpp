#include "../headers/workStealingDequeue.hpp"

WorkStealingDequeues::WorkStealingDequeues(Dequeue** myQueue, int l)
{
    queue = myQueue;
    length = l;
    srand(time(0));
}

void WorkStealingDequeues::run(int id)
{
    int me = id;
    RunnableTask *task = queue[me] -> popBottom();
    while (true)
    {
        while (task != NULL)
        {
            task->run();
            task = queue[me] -> popBottom();
        }
        while (task == NULL)
        {
            // TODO
            // Thread.yield();
            int victim = rand() % length;
            while (victim == me)
            {
                victim = rand() % length;
            }

            if (!queue[victim] -> isEmpty())
            {
                task = queue[victim] -> popTop();
            }
        }
    }
}