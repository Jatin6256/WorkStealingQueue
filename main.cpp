#include <iostream>
#include "./headers/checkPrime.hpp"
#include "./headers/workStealingDequeue.hpp"
#include "./headers/unboundedDequeue.hpp"
#include "./headers/boundedDequeue.hpp"
#include "./headers/normalDequeue.hpp"
#include "./headers/MatrixMultiplicationUtility.hpp"
#include <fstream>
#include <chrono>
using namespace std::chrono;

void *testWorkStealing(void *sharedBlock);
void *testWorkStealingWithMM(void *sharedBlock);
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
    // int *row;
    // int *column;
    // int *store;
    // int length;

    SharedValueMM()
    {
        workStealingDequeues = nullptr;
    }

    SharedValueMM(int threadNumber, WorkStealingDequeues *workStealingDequeues)
    {
        this->threadNumber = threadNumber;
        this->workStealingDequeues = workStealingDequeues;
        // this->row = row;
        // this->column = column;
        // this->store = store;
        // this->length = length;
    }
};
int main()
{
    srand(time(0));
    int taskType;

    std::cout << "Task Type 1: Checking Prime Numbers \nTask Type 2: Matrix Multiplication\n";
    std::cout << "Enter type of tasks: ";
    std::cin >> taskType;

    if (taskType == 1)
    {
        int checkPrimeUpto;
        int queueType;
        int numOfThreads;

        std::cout << "Enter Number Of threads: ";
        std::cin >> numOfThreads;
        if (numOfThreads <= 0)
        {
            std::cout << "Invalid Number of threads" << std::endl;
            return 0;
        }
        std::cout << "Check Primes Upto: ";

        std::cin >> checkPrimeUpto;
        if (checkPrimeUpto <= 0)
        {
            std::cout << "Invalid Number" << std::endl;
            return 0;
        }
        std::cout << "Available QueueTypes -> \n1: Normal Queue \n2: Bounded Queue \n3: UnBounded Queue \n";
        std::cout << "Enter QueueType: ";
        std::cin >> queueType;

        struct SharedValue *sharedContent[numOfThreads];
        int rc;
        pthread_t threads[numOfThreads]; // array to store thread id of threads
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
        else
        {
            std::cout << "Invalid Queue Type";
            return 0;
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

        std::cout << "prime Count:" << workStealingDequeues->getResult()->size()
                  << "\n";
        std::cout << "Time Taken: " << duration.count() << " microseconds"
                  << "\n";
    }
    else if (taskType == 2)
    {

        std::fstream matrix1, matrix2, result;
        matrix1.open("matrix1.txt", std::ios::app);
        if (!matrix1)
        {
            std::cout << "Unable to open file";
            exit(1); // terminate with error
        }

        matrix2.open("matrix2.txt", std::ios::app);
        if (!matrix2)
        {
            std::cout << "Unable to open file";
            exit(1); // terminate with error
        }

        result.open("matrixResult.txt", std::ios::app);
        if (!matrix2)
        {
            std::cout << "Unable to open file";
            exit(1); // terminate with error
        }
        int n1, m1;
        int n2, m2;
        std::cout << "Enter size of matrix 1 (row column) ";
        std::cin >> n1 >> m1;
        std::cout << "Enter size of matrix 2 (row column)";
        std::cin >> n2 >> m2;

        if (m1 != n2)
        {
            std::cout << "Invalid Matrix dimensions for multiplication"
                      << "\n";
            return 0;
        }
        int range;
        std::cout << "Enter range of matrix values: ";
        std::cin >> range;

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
                a[i][j] = rand() % range;
            }
        }

        for (int i = 0; i < n2; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                b[i][j] = rand() % range;
            }
        }
        std::cout << "Available QueueTypes -> \n1: Normal Queue \n2: Bounded Queue \n3: UnBounded Queue \n";
        std::cout << "Enter queue type";
        std::cin >> queueType;
        int numOfThreads = 4;
        struct SharedValueMM *sharedContent[numOfThreads];
        int rc;
        pthread_t threads[numOfThreads]; // array to store thread id of threads
        // std::cout << "num of threads:" << numOfThreads << "\n";
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
                boundedDequeue[i] = new BoundedDequeue(n1 * m2);
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
        else
        {
            std::cout << "Invalid queue type"
                      << "\n";
            return 0;
        }

        for (int i = 0; i < numOfThreads; i++)
        {
            sharedContent[i] = new SharedValueMM(i, workStealingDequeues);
        }

        auto startTime = high_resolution_clock::now();

        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                int id = rand() % numOfThreads;
                workStealingDequeues->pushTask(id, new MatrixMultiplicationUtility(a[i], b[j], &c[i][j], m1));
            }
        }

        // create threads
        for (int i = 0; i < numOfThreads; i++)
        {
            // creates threads and allots its task
            rc = pthread_create(&threads[i], NULL, testWorkStealingWithMM, (void *)sharedContent[i]);
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

        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                matrix1 << a[i][j] << " ";
            }
            std::cout << "\n";
        }
        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                matrix2 << b[i][j] << " ";
            }
            std::cout << "\n";
        }

        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                result << c[i][j] << " ";
            }
            std::cout << "\n";
        }

        std::cout << "Time Taken: " << duration.count() << " microseconds"
                  << "\n";
    }
    else
    {
        std::cout << "Invalid task type"
                  << "\n";
    }

    return 0;
}

void *testWorkStealingWithMM(void *sharedBlock)
{
    SharedValueMM *sharedContent = (SharedValueMM *)sharedBlock;
    int lVar;
    int id = sharedContent->threadNumber;
    if (debugMode)
        std::cout << "id:" << id << "\n";
    WorkStealingDequeues *workStealingDequeues = sharedContent->workStealingDequeues;
    workStealingDequeues->runMM(id);

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