#include <iostream>
#include "../headers/checkPrime.hpp"
#include<math.h>

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

int CheckPrime::run()
{
    if (debugMode)
        std::cout << "Check Prime Run: " << number << std::endl;

    if (number <= 1)
    {
        if (debugMode)
            std::cout << number << " is Not prime"
                      << "\n";

        return -1;
    }

    // Check from 2 to n-1
    for (int i = 2; i <= sqrt(number); i++)
        if (number % i == 0)
        {
            if (debugMode)
                std::cout << number << " is Not prime"
                          << "\n";
            return -1;
        }

    if (debugMode)
        std::cout << number << " is prime"
                  << "\n";
    return number;
}
