#include<iostream>
#include "../headers/runnableTask.hpp"


int RunnableTask::run() {
    std::cout << "Runnable Task Run" << std::endl;
  return -1;
}

void RunnableTask::run(int* store) {
    std::cout << "Runnable Task Run 2" << std::endl;
}