#include "../headers/workStealingDequeue.hpp"
#include "../headers/checkPrime.hpp"
#include "thread"

WorkStealingDequeues::WorkStealingDequeues(Dequeue **myQueue, int l)
{
    std::cout << "WorkStealingDequeues constructor line 6 WorkStealingDequeues.cpp"
              << "\n";
    queue = myQueue;
    length = l;
    srand(time(0));
}

void WorkStealingDequeues::run(int id,int start, int end)
{
    std::cout << "WorkStealingDequeues run line 14 WorkStealingDequeues.cpp"
              << "\n";
    // std::cout << (std::this_thread::get_id()) << "\n";
    int me = id;
    int numberOfTaskToPush = 1;
    int totalTask = end - start;
    int taskPushed = 0;
    std::cout << "me: " << me << "\n";

    RunnableTask *task = queue[me]->popBottom();
    while (true)
    {

        // std::cout << "hello1"
        //           << "\n";
        std::cout << "me: " << me << "\n";


        while (task != nullptr)
        {
            std::cout << "me: " << me << "\n";

            // std::cout << "hello2"
            //           << "\n";
            // std::cout << task;
            task->run();
            task = queue[me]->popBottom();
        }

        bool hasPushedTask = false;
        int currentTaskPushed = 0;
        while(currentTaskPushed < numberOfTaskToPush && taskPushed < totalTask){
            CheckPrime* checkPrime = new CheckPrime(start + taskPushed + 1);
            queue[me]->pushBottom(checkPrime);
            taskPushed++;
            currentTaskPushed++;
            hasPushedTask = true;
        }
        if(hasPushedTask){
            numberOfTaskToPush *= 2;
            if(numberOfTaskToPush > totalTask){
                numberOfTaskToPush = totalTask - taskPushed;
            }

            task = queue[me]->popBottom();
        }
        int count = length;
        // std::cout << "hello3"
        //           << "\n";
        while (task == nullptr && !hasPushedTask && count > 0 )
        {
            std::cout << "entered while loop" << "\n";
            // std::cout << "hello4"
            //           << "\n";

            std::this_thread::yield();
            int victim = rand() % length;
            while (victim == me)
            {
                victim = rand() % length;
            }

            if (!queue[victim]->isEmpty())
            {
                task = queue[victim]->popTop();
                // count = length;
            }

            count--;
        }

        if (count == 0)
        {
            break;
        }
    }
}