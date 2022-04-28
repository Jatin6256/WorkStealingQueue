#ifndef MMU_HPP
#define MMU_HPP
#include "./runnableTask.hpp"

class MatrixMultiplicationUtility: public RunnableTask{
    int* row;
    int* column;
    int* store;
    int length; 
    static const bool debugMode = false;

    public:
        MatrixMultiplicationUtility();
        MatrixMultiplicationUtility(int* row,int* column,int* store, int l);
        int run();
};

#endif