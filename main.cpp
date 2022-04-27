#include <iostream>
#include "./headers/checkPrime.hpp"
#include "./headers/workStealingDequeue.hpp"
#include "./headers/unboundedDequeue.hpp"
#include "./headers/boundedDequeue.hpp"
#include "./headers/normalDequeue.hpp"
#include <chrono>
using namespace std::chrono;

void *testWorkStealing(void *sharedBlock);
bool debugMode = false;

struct SharedValue
{
    int threadNumber; // to track thread number
    // Dequeue **boundedDequeue;
    WorkStealingDequeues *workStealingDequeues;
    int start, end;

    SharedValue()
    {
        workStealingDequeues = nullptr;
    }

    SharedValue(int threadNumber, WorkStealingDequeues *workStealingDequeues, int start, int end)
    {
        this->threadNumber = threadNumber;
        this->workStealingDequeues = workStealingDequeues;
        this->start = start;
        this->end = end;
    }
};

struct SharedValueMM
{
    int threadNumber; // to track thread number
    // Dequeue **boundedDequeue;
    WorkStealingDequeues *workStealingDequeues;
    int *row;
    int *column;
    int *store;
    int length;

    SharedValueMM()
    {
        workStealingDequeues = nullptr;
    }

    SharedValueMM(int threadNumber, WorkStealingDequeues *workStealingDequeues, int *row, int *column,int* store, int length)
    {
        this->threadNumber = threadNumber;
        this->workStealingDequeues = workStealingDequeues;
        this->row = row;
        this->column = column;
        this->store = store;
        this->length = length;
    }
};
int main()
{
    int taskType;
    std::cin >> taskType;

    if (taskType == 1)
    {
        int checkPrimeUpto;
        int queueType;
        int numOfThreads;

        std::cout << "Enter Number Of threads: ";
        std::cin >> numOfThreads;
        std::cout << "Check Primes Upto: ";
        std::cin >> checkPrimeUpto;
        std::cout << "Available QueueTypes -> \n1: Normal Queue \n2: Bounded Queue \n3: UnBounded Queue \n";
        std::cout << "Enter QueueType: ";
        std::cin >> queueType;

        struct SharedValue *sharedContent[numOfThreads];
        int rc;
        pthread_t threads[numOfThreads]; // array to store thread id of threads
        srand(time(0));
        int taskSize = checkPrimeUpto / numOfThreads;
        Dequeue **normalDequeue;
        Dequeue **boundedDequeue;
        Dequeue **unboundedDequeue;
        WorkStealingDequeues *workStealingDequeues;

        if (queueType == 1)
        {
            normalDequeue = new Dequeue *[numOfThreads];
            for (int i = 0; i < numOfThreads; i++)
            {
                normalDequeue[i] = new NormalDequeue();
            }
            workStealingDequeues = new WorkStealingDequeues(normalDequeue, numOfThreads, false);
        }
        else if (queueType == 2)
        {
            boundedDequeue = new Dequeue *[numOfThreads];
            for (int i = 0; i < numOfThreads; i++)
            {
                boundedDequeue[i] = new BoundedDequeue(taskSize);
            }
            workStealingDequeues = new WorkStealingDequeues(boundedDequeue, numOfThreads, true);
        }
        else if (queueType == 3)
        {
            unboundedDequeue = new Dequeue *[numOfThreads];
            for (int i = 0; i < numOfThreads; i++)
            {
                unboundedDequeue[i] = new UnboundedDequeue();
            }
            workStealingDequeues = new WorkStealingDequeues(unboundedDequeue, numOfThreads, true);
        }

        int start = 0;
        for (int i = 0; i < numOfThreads; i++)
        {
            if (i == numOfThreads - 1)
            {
                sharedContent[i] = new SharedValue(i, workStealingDequeues, start, checkPrimeUpto);
                break;
            }
            sharedContent[i] = new SharedValue(i, workStealingDequeues, start, start + taskSize);
            start += taskSize;
        }

        // create threads
        auto startTime = high_resolution_clock::now();
        for (int i = 0; i < numOfThreads; i++)
        {
            // creates threads and allots its task
            rc = pthread_create(&threads[i], NULL, testWorkStealing, (void *)sharedContent[i]);
            if (rc)
            {
                printf("ERROR; return code from pthread_create() is %d\n", rc);
                exit(EXIT_FAILURE);
            }
        }

        // waiting for thread
        for (int i = 0; i < numOfThreads; i++)
        {
            pthread_join(threads[i], NULL);
        }
        auto stopTime = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stopTime - startTime);

        std::cout << duration.count() << " microseconds"
                  << "\n";
        std::cout << "prime Count:" << workStealingDequeues->getResult()->size()
                  << "\n";
    }
    else if (taskType == 2)
    {
        int n1, m1;
        int n2, m2;
        std::cin >> n1 >> m1;
        std::cin >> n2 >> m2;

        if (m1 != n2)
        {
            std::cout << "Invalid Matrix dimensions for multiplication"
                      << "\n";
            return 0;
        }

        int **a;
        int **b;
        int **c;
        int queueType;

        a = new int *[n1];
        b = new int *[n2];
        c = new int *[n1];
        for (int i = 0; i < n1; i++)
        {
            a[i] = new int[m1];
        }

        for (int i = 0; i < n2; i++)
        {
            b[i] = new int[m2];
        }

        for (int i = 0; i < n1; i++)
        {
            c[i] = new int[m2];
        }

        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m1; j++)
            {
                std::cin >> a[i][j];
            }
        }

        for (int i = 0; i < n2; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                std::cin >> b[i][j];
            }
        }

        std::cin >> queueType;
        int numOfThreads = n1 * m2;
        struct SharedValueMM *sharedContent[numOfThreads];
        int rc;
        pthread_t threads[n1 * m2]; // array to store thread id of threads
        srand(time(0));
        Dequeue **normalDequeue;
        Dequeue **boundedDequeue;
        Dequeue **unboundedDequeue;
        WorkStealingDequeues *workStealingDequeues;

        if (queueType == 1)
        {
            normalDequeue = new Dequeue *[numOfThreads];
            for (int i = 0; i < numOfThreads; i++)
            {
                normalDequeue[i] = new NormalDequeue();
            }
            workStealingDequeues = new WorkStealingDequeues(normalDequeue, numOfThreads, false);
        }
        else if (queueType == 2)
        {
            boundedDequeue = new Dequeue *[numOfThreads];
            for (int i = 0; i < numOfThreads; i++)
            {
                boundedDequeue[i] = new BoundedDequeue(2 * m1);
            }
            workStealingDequeues = new WorkStealingDequeues(boundedDequeue, numOfThreads, true);
        }
        else if (queueType == 3)
        {
            unboundedDequeue = new Dequeue *[numOfThreads];
            for (int i = 0; i < numOfThreads; i++)
            {
                unboundedDequeue[i] = new UnboundedDequeue();
            }
            workStealingDequeues = new WorkStealingDequeues(unboundedDequeue, numOfThreads, true);
        }

        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                sharedContent[i] = new SharedValueMM(i, workStealingDequeues, a[i], b[j],&c[i][j],m1);
            }
            
        }

        // create threads
        auto startTime = high_resolution_clock::now();
        for (int i = 0; i < numOfThreads; i++)
        {
            // creates threads and allots its task
            rc = pthread_create(&threads[i], NULL, testWorkStealing, (void *)sharedContent[i]);
            if (rc)
            {
                printf("ERROR; return code from pthread_create() is %d\n", rc);
                exit(EXIT_FAILURE);
            }
        }

        // waiting for thread
        for (int i = 0; i < numOfThreads; i++)
        {
            pthread_join(threads[i], NULL);
        }
        auto stopTime = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stopTime - startTime);

        std::cout << duration.count() << " microseconds"
                  << "\n";

        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                std::cout << c[i][j] << " ";
            }
            std::cout << "\n";
        }
        
    }

    return 0;
}

void *testWorkStealingWithMM(void *sharedBlock)
{
    SharedValueMM *sharedContent = (SharedValueMM *)sharedBlock;
    int lVar;
    int id = sharedContent->threadNumber;
    int *row = sharedContent->row;
    int *column = sharedContent->column;
    int *store = sharedContent->store;
    int length = sharedContent->length;
    WorkStealingDequeues *workStealingDequeues = sharedContent->workStealingDequeues;
    workStealingDequeues->runMM(id, row, column, store, length);

    return NULL;
}

void *testWorkStealing(void *sharedBlock)
{
    SharedValue *sharedContent = (SharedValue *)sharedBlock;
    int lVar;
    int id = sharedContent->threadNumber;
    int start = sharedContent->start;
    int end = sharedContent->end;
    if (debugMode)
        std::cout << id << " " << start << " " << end << "\n";
    WorkStealingDequeues *workStealingDequeues = sharedContent->workStealingDequeues;
    workStealingDequeues->run(id, start, end);

    return NULL;
}