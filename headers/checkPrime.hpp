#ifndef CHECKPRIME_HPP
#define CHECKPRIME_HPP
#include "./runnableTask.hpp"

class CheckPrime: public RunnableTask{
    int number;
    static const bool debugMode = true;

    public:
        CheckPrime();
        CheckPrime(int n);
        void run();
};

#endif