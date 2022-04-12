#ifndef WORKSTEALINGDEQUEUE_HPP
#define WORKSTEALINGDEQUEUE_HPP
#include<iostream>
#include <stdlib.h>
#include<time.h>
#include "../headers/dequeue.hpp"


class WorkStealingDequeues
{
    Dequeue** queue;
    int length;
public:
    WorkStealingDequeues(Dequeue** myQueue, int l);
    void run(int id);
};

#endif  