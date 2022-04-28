#ifndef WORKSTEALINGDEQUEUE_HPP
#define WORKSTEALINGDEQUEUE_HPP
#include<iostream>
#include <stdlib.h>
#include<time.h>
#include <vector>
#include "../headers/dequeue.hpp"


class WorkStealingDequeues
{
    Dequeue** queue;
    int length;
    bool hasConcurrentPushTopMethod;
    std::vector<int>* resultArray;
    static const bool debugMode = true; 

    public:
        WorkStealingDequeues(Dequeue** myQueue, int l, bool hasConcurrentPushTopMethod);
        void run(int id,int start,int end);
        void runMM(int id,int* row,int* column,int* store, int length);
        std::vector<int>* getResult();
};

#endif 