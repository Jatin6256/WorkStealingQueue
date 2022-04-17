#include <iostream>
#include "../headers/checkPrime.hpp"

CheckPrime::CheckPrime()
{
    number = 2;
    std::cout << "CheckPrime Default Constructor" << std::endl;
}

CheckPrime::CheckPrime(int n)
{
    number = n;
    std::cout << "CheckPrime Constructor" << std::endl;
}

void CheckPrime::run()
{

    std::cout << "Check Prime Run: " << number << std::endl;

    if (number <= 1){
        std::cout << "Not Prime" << std::endl;
        return;
    }

    // Check from 2 to n-1
    for (int i = 2; i < number; i++)
        if (number % i == 0){
            std::cout << number << " is Not prime" << "\n";
            return;
        }
            

    std::cout << number << " is prime" << "\n";
    return;
    
}
