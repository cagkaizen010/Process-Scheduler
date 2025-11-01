
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
    this->processMap[process->getName()] = process;
}

void Scheduler::stop(){
    this->running = false;
}

std::shared_ptr<Process> Scheduler::findProcess(std::string processName){

    if(this->processMap.find(processName)!= this->processMap.end()) return this-> processMap[processName];
    else return nullptr;
}

std::vector<Scheduler::ProcessInfo> Scheduler::getRunningProcessInfo() const{
    std::vector<ProcessInfo> ptList;
    // for(ProcessList i: this->processList  )

    for(int i = 0; i < this->processList.size(); i++){
        if(this->processList[i]->getStatus() == ProcessState::READY){
            ProcessInfo pt{ this->processList[i]->getID(),
                            this->processList[i]->getCPUCoreID(),
                            this->processList[i]->getCommandCounter(),
                            this->processList[i]->getLinesOfCode(),
                            this->processList[i]->getRemainingTime()  
                        };
            ptList.push_back(pt);
        }
    }
    return ptList;
}

std::string Scheduler::getName() {
    return this->processName;
}

// Might not be needed
std::string Scheduler::getLatestMsg() {
    std::string displayMsg = this->outputBuffer.str();
    this->outputBuffer.str(std::string());
    return displayMsg;
}

