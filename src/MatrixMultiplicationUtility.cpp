#include <iostream>
#include "../headers/MatrixMultiplicationUtility.hpp"
#include<math.h>

MatrixMultiplicationUtility::MatrixMultiplicationUtility()
{
    if (debugMode)
        std::cout << "CheckPrime Default Constructor" << std::endl;
}

MatrixMultiplicationUtility::MatrixMultiplicationUtility(int* row,int* column,int* store,int l)
{
    if (debugMode)
        std::cout << "CheckPrime Constructor" << std::endl;
    this->row = row;
    this->column = column;
    this->store = store;
    this->length = l;
}

int MatrixMultiplicationUtility::run(){

    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += row[i] * column[i];
    }

    *store = sum;
    return 1;
}
