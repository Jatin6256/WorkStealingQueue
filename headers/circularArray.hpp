#include "./runnableTask.hpp"

class CircularArray {

    private:
        int logCapacity;
        RunnableTask** currentTasks;
    public:
        CircularArray();
        CircularArray(int capacity);
        int capacity();
        RunnableTask* get(int index);
        void put(RunnableTask* task, int index);
        CircularArray* resize(int bottom,int top);
};