#include "../headers/workStealingDequeue.hpp"
#include "../headers/checkPrime.hpp"
#include "../headers/MatrixMultiplicationUtility.hpp"

#include "thread"
#include <iostream>
#include <vector>
#include <mutex>

std::mutex mtx;

WorkStealingDequeues::WorkStealingDequeues(Dequeue **myQueue, int l, bool hasConcurrentPushTopMethod)
{
    if (debugMode)
        std::cout << "WorkStealingDequeues constructor line 6 WorkStealingDequeues.cpp"
                  << "\n";
    queue = myQueue;
    resultArray = new std::vector<int>();
    length = l;
    this->hasConcurrentPushTopMethod = hasConcurrentPushTopMethod;
    srand(time(0));
}

void WorkStealingDequeues::run(int id, int start, int end)
{
    if (debugMode)
        std::cout << "WorkStealingDequeues run line 14 WorkStealingDequeues.cpp"
                  << "\n";
    int me = id;
    int numberOfTaskToPush = 1;
    int totalTask = end - start;
    int taskPushed = 0;
    if (debugMode)
        std::cout << "me: " << me << "\n";

    RunnableTask *task = queue[me]->popBottom();
    while (true)
    {

        while (task != nullptr)
        {
            if (debugMode)
                std::cout << "me: " << me << "\n";

            int result = task->run();

            if (result >= 0)
            {
                mtx.lock();
                resultArray->push_back(result);
                mtx.unlock();
            }
            task = queue[me]->popBottom();
        }

        bool hasPushedTask = false;
        int currentTaskPushed = 0;
        while (currentTaskPushed < numberOfTaskToPush && taskPushed < totalTask)
        {
            CheckPrime *checkPrime = new CheckPrime(start + taskPushed + 1);
            if (debugMode)
                std::cout << "pushed: " << start + taskPushed + 1 << "\n";
            queue[me]->pushBottom(checkPrime);
            taskPushed++;
            currentTaskPushed++;
            hasPushedTask = true;
        }
        if (hasPushedTask)
        {
            numberOfTaskToPush *= 2;
            if (numberOfTaskToPush > totalTask)
            {
                numberOfTaskToPush = totalTask - taskPushed;
            }

            task = queue[me]->popBottom();
        }
        if (!hasConcurrentPushTopMethod && hasPushedTask)
        {
            continue;
        }

        if (!hasConcurrentPushTopMethod && !hasPushedTask)
        {
            return;
        }
        int count = length;
        while (task == nullptr && !hasPushedTask && count > 0)
        {
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

void WorkStealingDequeues::runMM(int id, int *row, int *column, int *store, int length)
{
    if (debugMode)
        std::cout << "WorkStealingDequeues run line 14 WorkStealingDequeues.cpp"
                  << "\n";

    int me = id;
    if (debugMode)
        std::cout << "me: " << me << "\n";

    queue[me]->pushBottom(new MatrixMultiplicationUtility(row, column, length));

    RunnableTask *task = queue[me]->popBottom();
    while (true)
    {

        while (task != nullptr)
        {
            if (debugMode)
                std::cout << "me: " << me << "\n";

            task->run();
            task = queue[me]->popBottom();
        }

        int count = this->length;
        while (task == nullptr && count > 0)
        {
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
std::vector<int> *WorkStealingDequeues::getResult()
{
    return resultArray;
}