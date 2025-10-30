#include "Process.h"

Process::Process(ProcessState state, std::string name, int pid){
    this->state = state;
    this->name= name;
    this->pid= pid;
}



std::string Process::getName(){
    return "getName() placeholder";
}

Process::ProcessState Process::getState() {
    ProcessState state;
    return state;
}

int Process::getPID(){
    return 1;
}

int Process::getCPUCoreID(){
    return 1;
}

int Process::getCommandCounter(){
    return 1;
}

int Process::getLinesOfCode(){
    return 1;
}

int Process::getRemainingTime(){
    return 1;
}