#include <cstdio>

#include "process.h"

Process::Process(ProcessState state, std::string name, int pid){
    this->state = state;
    this->name= name;
    this->pid= pid;
}

void Process::PRINT(std::string msg ){
    std::cout << msg << std::endl;
}