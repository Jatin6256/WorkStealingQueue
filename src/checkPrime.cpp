#include <iostream>
#include "../headers/checkPrime.hpp"

CheckPrime::CheckPrime()
{
    number = 2;
    if (debugMode)
        std::cout << "CheckPrime Default Constructor" << std::endl;
}

CheckPrime::CheckPrime(int n)
{
    number = n;
    if (debugMode)
        std::cout << "CheckPrime Constructor" << std::endl;
}

void CheckPrime::run()
{
    if (debugMode)
        std::cout << "Check Prime Run: " << number << std::endl;

    if (number <= 1)
    {
        if (debugMode)
            std::cout << number << " is Not prime"
                      << "\n";

        return;
    }

    // Check from 2 to n-1
    for (int i = 2; i < number; i++)
        if (number % i == 0)
        {
            if (debugMode)
                std::cout << number << " is Not prime"
                          << "\n";
            return;
        }

    if (debugMode)
        std::cout << number << " is prime"
                  << "\n";
    return;
}
