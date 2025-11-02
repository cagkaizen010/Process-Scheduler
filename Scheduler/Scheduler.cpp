
#include "Scheduler.h"
Scheduler::Scheduler() {

}

Scheduler* Scheduler::_staticSchedulerPtr = nullptr;
Scheduler* Scheduler::get(){
    return _staticSchedulerPtr;
}

void Scheduler::initialize(int cpuNum, std::string scheduler, int quantumCycles, int batchProcessFreq, int minIns, int maxIns, int delaysPerExec){
    _staticSchedulerPtr = new Scheduler();

    for(int i = 0; i < cpuNum; i++)
        _staticSchedulerPtr-> _CPUList.push_back(std::make_shared<CPU>());

    _staticSchedulerPtr->batchProcessFreq = batchProcessFreq;
    _staticSchedulerPtr->minIns= minIns;
    _staticSchedulerPtr->maxIns= maxIns;
}

// Scheduler::Scheduler(SchedulingAlgorithm algo, int pid, std::string processName ){
//     this->algo = algo;
//     this->pid = pid;
//     this->processName = processName;
//     this->running = true;
// }

void Scheduler::addProcess(std::shared_ptr<Process> process){
    this->_readyQueue.push(process);
    this->_processList.push_back(process);
    this->_processMap[process->getName()] = process;
}

void Scheduler::startFCFS(float delayTime){
    while (this->running){
        for (std::shared_ptr<CPU> i: _CPUList){
            if (i->checkStatus() == CPU::READY){
                if(this->_readyQueue.size() > 0){
                    i->setProcess(this->_readyQueue.front());
                    _readyQueue.pop();
                    this->running=true;
                }
            }
        }
    }
}

void Scheduler::startRR(float delayTime, int quantumCycles){

}

void Scheduler::stop(){
    this->running = false;
}

std::shared_ptr<Process> Scheduler::findProcess(std::string processName){

    if(this->_processMap.find(processName)!= this->_processMap.end()) return this-> _processMap[processName];
    else return nullptr;
}

// std::vector<Scheduler::ProcessInfo> Scheduler::getRunningProcessInfo() const{
//     return ;
// }

void Scheduler::printStatus() {
    for(std::shared_ptr<CPU> i : _CPUList){
        if(i->checkStatus()==CPU::READY){
            std::cout <<"Idle\tCore: " << std::to_string(i->getID()) << std::endl;
        }
        else{
            std::cout << i->getID()<< std::endl;
        }
    }
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

