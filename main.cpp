#include <iostream>
#include "./headers/checkPrime.hpp"
#include "./headers/workStealingDequeue.hpp"
#include "./headers/unboundedDequeue.hpp"
#include "./headers/boundedDequeue.hpp"

void *testWorkStealing(void *sharedBlock);
int numOfThreads = 4, numOfTasks=4;

struct SharedValue
{
    int threadNumber;	// to track thread number
    Dequeue **boundedDequeue;
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

    // WorkStealingDequeues workStealingDequeues(unboundedDequeue, 3);
    
    // workStealingDequeues.run(0);

    struct SharedValue sharedContent[numOfThreads];
    int rc;
	pthread_t threads[numOfThreads]; //array to store thread id of threads


    Dequeue** boundedDequeue = new Dequeue*[numOfThreads];
    for (int i = 0; i < numOfThreads; i++)
    {
        for (int j = 0; j < numOfTasks; j++)
        {
            boundedDequeue[i] = new BoundedDequeue(numOfTasks); 
            CheckPrime checkPrime(rand() % 100);
            boundedDequeue[i]->pushBottom(&checkPrime);  
        } 
    }

    for (int i = 0; i < numOfThreads; i++){
        sharedContent[i] = {i, boundedDequeue};
    }

    // create threads
    for (int i = 0; i < numOfThreads; i++) {
        //creates threads and allots its task
        rc = pthread_create(&threads[i], NULL, testWorkStealing, (void *)&sharedContent[i]);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    // waiting for thread
    for (int i = 0; i < numOfThreads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}


void *testWorkStealing(void* sharedBlock){
    SharedValue *sharedContent = (SharedValue *)sharedBlock;
    int lVar;
    int id = (*sharedContent).threadNumber;
    Dequeue** boundedDequeue = (*sharedContent).boundedDequeue;

    WorkStealingDequeues workStealingDequeues(boundedDequeue, numOfTasks*numOfThreads);

    workStealingDequeues.run(id);

    return NULL;
}