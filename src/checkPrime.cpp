#include<iostream>
#include "../headers/checkPrime.hpp"

CheckPrime::CheckPrime()
{
    number = 2;
    std::cout << "CheckPrime Default Constructor" << std::endl;
}

CheckPrime::CheckPrime(int n){
    number = n;
    std::cout << "CheckPrime Constructor" << std::endl;

}

void CheckPrime::run() {
    std::cout << "Check Prime Run" << std::endl;
}

