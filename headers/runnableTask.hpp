#ifndef RUNNABLETASK_HPP
#define RUNNABLETASK_HPP
class RunnableTask{
public:
    virtual int run();
    virtual void run(int* store);
};
#endif