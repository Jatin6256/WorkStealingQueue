#include <iostream>
#include "../headers/MatrixMultiplicationUtility.hpp"
#include<math.h>

MatrixMultiplicationUtility::MatrixMultiplicationUtility()
{
    if (debugMode)
        std::cout << "CheckPrime Default Constructor" << std::endl;
}

MatrixMultiplicationUtility::MatrixMultiplicationUtility(int* row,int* column,int l)
{
    if (debugMode)
        std::cout << "CheckPrime Constructor" << std::endl;
    this->row = row;
    this->column = column;
    this->length = l;
}

void MatrixMultiplicationUtility::run(int* store){

    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += row[i] * column[i];
    }

    *store = sum;
}
