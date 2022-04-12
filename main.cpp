#include<iostream>
#include "./headers/checkPrime.hpp"
#include "./headers/workStealingDequeue.hpp"
#include "./headers/unboundedDequeue.hpp"

int main()
{
    CheckPrime checkPrime1(2);
    CheckPrime checkPrime2(3);
    CheckPrime checkPrime3(5);

    Dequeue** unboundedDequeue = new Dequeue*[3];
    for (int i = 0; i < 3; i++)
    {
        unboundedDequeue[i] = new UnboundedDequeue(); 
        unboundedDequeue[i] -> pushBottom(&checkPrime1);  
    }

    WorkStealingDequeues workStealingDequeues(unboundedDequeue, 3);
    
    workStealingDequeues.run(0);
    
    
    std::cout << "Hello World!" << std::endl;
    return 0;
}