#include <iostream>
#include "./headers/checkPrime.hpp"
#include "./headers/workStealingDequeue.hpp"
#include "./headers/unboundedDequeue.hpp"
#include "./headers/boundedDequeue.hpp"

void *testWorkStealing(void *sharedBlock);
int numOfThreads = 2, numOfTasks = 2;

struct SharedValue
{
    int threadNumber; // to track thread number
    // Dequeue **boundedDequeue;
    WorkStealingDequeues *workStealingDequeues;

    SharedValue()
    {
        workStealingDequeues = nullptr;
    }

    SharedValue(int threadNumber, WorkStealingDequeues *workStealingDequeues)
    {
        this->threadNumber = threadNumber;
        this->workStealingDequeues = workStealingDequeues;
    }
};

int main()
{
    // CheckPrime checkPrime1(2);
    // CheckPrime checkPrime2(3);
    // CheckPrime checkPrime3(5);

    // Dequeue** unboundedDequeue = new Dequeue*[3];
    // for (int i = 0; i < 3; i++)
    // {
    //     unboundedDequeue[i] = new UnboundedDequeue();
    //     unboundedDequeue[i] -> pushBottom(&checkPrime1);
    // }

    // workStealingDequeues.run(0);

    struct SharedValue *sharedContent[numOfThreads];
    int rc;
    pthread_t threads[numOfThreads]; // array to store thread id of threads
    srand(time(0));

    // Dequeue** boundedDequeue = new Dequeue*[numOfThreads];
    // for (int i = 0; i < numOfThreads; i++)
    // {
    //     for (int j = 0; j < numOfTasks; j++)
    //     {
    //         boundedDequeue[i] = new BoundedDequeue(numOfTasks);
    //         CheckPrime checkPrime(rand() % 100);
    //         boundedDequeue[i]->pushBottom(&checkPrime);
    //     }
    // }

    Dequeue **unboundedDequeue = new Dequeue *[numOfThreads];
    for (int i = 0; i < numOfThreads; i++)
    {
        unboundedDequeue[i] = new UnboundedDequeue();

        for (int j = 0; j < numOfTasks; j++)
        {
            int random = rand() % 100;
            std::cout << "random: " << random << "\n";
            CheckPrime* checkPrime = new CheckPrime(random);
            unboundedDequeue[i]->pushBottom(checkPrime);
        }
    }

    WorkStealingDequeues *workStealingDequeues = new WorkStealingDequeues(unboundedDequeue, numOfThreads);

    for (int i = 0; i < numOfThreads; i++)
    {
        sharedContent[i] = new SharedValue(i, workStealingDequeues);
    }

    // create threads
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

    return 0;
}

void *testWorkStealing(void *sharedBlock)
{
    SharedValue *sharedContent = (SharedValue *)sharedBlock;
    int lVar;
    int id = sharedContent->threadNumber;
    WorkStealingDequeues *workStealingDequeues = sharedContent->workStealingDequeues;

    workStealingDequeues->run(id);

    return NULL;
}