
#include "Scheduler.h"
#include <fstream>

int Scheduler::getRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}


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

void Scheduler::schedulerTest(){
    this->_schedulerRunning = true;   
    std::thread t(&Scheduler::schedulerRun, this);
    t.detach();
}

void Scheduler::schedulerRun() {
        int randNum = getRandomInt(1, 3);

        ProcessControlBlock pcb = ProcessControlBlock{randNum, "process_" + std::to_string(randNum)};
        // std::vector<std::shared_ptr<Instruction>> text;
    while(this->_schedulerRunning){
        std::shared_ptr<Process> p = std::make_shared<Process>(pcb );
        p->generateInstruction();
        
        this->addProcess(p);
        // std::cout << "ProcessQueue: " << this->_readyQueue.front()->getName() << std::endl;
        // std::cout << "ProcessList: ";
        // std::cout << "ProcessMap: ";

        std::this_thread::sleep_for(std::chrono::milliseconds(int(this->batchProcessFreq*1000)));
    }
}

void Scheduler::addProcess(std::shared_ptr<Process> process){
    this->_readyQueue.push(process);
    this->_processList.push_back(process);
    this->_processMap[process->getName()] = process;
    // std::cout << process->getName() + " added to _readyQueue" << std::endl;
    // std::cout << process->getName() + " added to _processList" << std::endl;
    // std::cout << process->getName() + " added to _processMap" << std::endl;


}

void Scheduler::startFCFS(float delayTime){
    std::cout <<"FCFS is running" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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
            // std::cout << i->getProcessName()+"\tCore: "<< std::to_string(i->getID())<< std::endl;
            std::cout << "List the busy processors" << std::endl;
        }
    }
}

void Scheduler::processSMI() {
    std::cout << "PROCESS SMI" << std::endl;

    // for(std::shared_ptr<CPU> i : _CPUList)
    //     std::cout << i->getProcessName() << std::endl;
    

}

void Scheduler::reportUtil() {
    std::cout << "PROCESS SMI" << std::endl;

    std::ofstream outputFile("csopesy-log.txt", std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open console_log.txt for writing." << std::endl;
        return;
    }

    for(std::shared_ptr<CPU> i : _CPUList){
        if(i->checkStatus()==CPU::READY){
            outputFile <<"Idle\tCore: " << std::to_string(i->getID()) << std::endl;
        }
        else{
            outputFile << "List the busy processors" << std::endl;
        }
    }
    std::cout << "Report generated at csopesy-log.txt successfully." << std::endl;
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

