
#include "./runnableTask.hpp"

class CheckPrime: public RunnableTask{
    int number;

    public:
        CheckPrime();
        void run();
};