#include <cstdio>

#include "Scheduler.h"

Scheduler::Scheduler(SchedulingAlgorithm algo, int pid, std::string processName ){
    this->algo = algo;
    this->pid = pid;
    this->processName = processName;
    this->running = true;
}

void Scheduler::addProcess(std::shared_ptr<Process> process){
    this->readyQueue.push(process);
    this->processList.push_back(process);
    // this->processMap[process->getName()] = process;
}

std::vector<Scheduler::ProcessInfo> Scheduler::getRunningProcessInfo() const{
    std::vector<ProcessInfo> processList;

    for (int i = 0; i < this->processList.size(); i++){
        if(this->processList[i]->getState() == Process:ProcessState::RUNNING)
    }
}
