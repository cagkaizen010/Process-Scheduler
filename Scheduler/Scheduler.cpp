#include "Scheduler.h"



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

    _staticSchedulerPtr->cpuCycles = 0;
    for(int i = 0; i < cpuNum; i++){

        _staticSchedulerPtr-> _CPUList.push_back(std::make_shared<CPU>());
        _staticSchedulerPtr-> _CPUList.at(i)->setDelayTime(delaysPerExec);
        // _staticSchedulerPtr-> _CPUList.at(i)->setCPUCycles(_staticSchedulerPtr->cpuCycles);
    }

    // Defining dispatcher
    _staticSchedulerPtr->d = std::make_shared<Dispatcher>();
    _staticSchedulerPtr->d->setScheduler(_staticSchedulerPtr);
    _staticSchedulerPtr->d->setCPUList(_staticSchedulerPtr->_CPUList);

    _staticSchedulerPtr->batchProcessFreq = batchProcessFreq;
    _staticSchedulerPtr->minIns= minIns;
    _staticSchedulerPtr->maxIns= maxIns;
}


void Scheduler::schedulerTest(){
    this->running = true;
    this->d->startDispatcher();
    std::thread t(&Scheduler::schedulerRun, this);
    t.detach();
    this->_schedulerRunning = true;   
}

void Scheduler::schedulerRun() {
        int randNum =0;

        // Root of all timing
        while(this->running){
            std::unique_lock<std::mutex> lock(CPU::mtx);

            if(fmod(CPU::cpuCycles,this->batchProcessFreq) ==float(0)){
                ProcessControlBlock pcb = ProcessControlBlock{randNum, "p_" + std::to_string(randNum),-1};
                std::shared_ptr<Process> p = std::make_shared<Process>(pcb );
        
                p->generateInstruction(this->minIns, this->maxIns);
                // std::cout << p->getName()<< std::endl;
                this->addProcess(p);


                randNum++;
            }
            // std::cout << "INSIDE SCHEDULER: " << this->_processList.size() << std::endl;
            // cpuCycles++;
            // CPU::cpuCycles = cpuCycles;
            // std::string garbage;
            // CPU::cpuCycles++;
            // std::getline(std::cin,garbage);
            std::cout <<CPU::cpuCycles << std::endl;
            // std::cout << CPU::cpuCycles<<std::endl;
            lock.unlock();

            // std::this_thread::sleep_for(std::chrono::milliseconds(100));
            // std::cout << "cpuCycles:\t" << cpuCycles<< std::endl;
            // std::cout << "CPU::cpuCycles:\t" << CPU::cpuCycles<<std::endl;
        }
        std::cout << "Finished generating processes!" << std::endl;


}

void Scheduler::addProcess(std::shared_ptr<Process> process){
    // this->_readyQueue.push(process);
    this->_processList.push_back(process);
    this->_processListHistory.push_back(this->_processList.front());
    this->_processMap[process->getName()] = process;


}

void Scheduler::runFCFS(float delayTime) {
    if(!this->running){
        this->running = true;
        // Dispatcher d(_CPUList, this);
        std::thread t(&Scheduler::startFCFS, this,  delayTime);
        t.detach();

        std::cout <<"FCFS is running" << std::endl;
    }
}
void Scheduler::startFCFS(float delayTime){

    while (this->running){
        while(this->_schedulerRunning){
            if(this->_processList.size()!=0){
                this->_readyQueue.push(this->_processList.front());
                this->_processList.erase(this->_processList.begin());
            }
            
            // std::this_thread::sleep_for(std::chrono::milliseconds(int(delayTime)));

        }
    }
}

void Scheduler::runRR(float delayTime, int quantumCycles){
    if(!this->running){
        this->running = true;
        // Dispatcher d(_CPUList, this);
        std::thread t(&Scheduler::startRR, this,  delayTime, quantumCycles);
        t.detach();

        std::cout <<"RR is running" << std::endl;
    }
}
void Scheduler::startRR(float delayTime, int quantumCycles){
    if(!this-> running){

    }
}

// Does not work properly
void Scheduler::stop(){
    this->_schedulerRunning =false;
    this->running = false;
    this->d->stopDispatcher();
}

std::shared_ptr<Process> Scheduler::findProcess(std::string processName){

    if(this->_processMap.find(processName)!= this->_processMap.end()) return this-> _processMap[processName];
    else return nullptr;
}

// std::vector<Scheduler::ProcessInfo> Scheduler::getRunningProcessInfo() const{
//     return ;
// }

void Scheduler::printStatus() {
    int cpuReadyCount = 0;
    for (std::shared_ptr<CPU> cpu : this->_CPUList) 
        if (cpu->checkStatus() == CPU::READY) cpuReadyCount++;
    
    float CPUUtil = 100.0 * (this->_CPUList.size() - cpuReadyCount)/(this->_CPUList.size());
    
    std::cout <<
        "CPU utilization: " + std::to_string(CPUUtil) + "\n" +
        "Cores used: " + std::to_string(this->_CPUList.size() - cpuReadyCount) + "\n" +
        "Cores available: " + std::to_string(cpuReadyCount) <<
    std::endl;
    
    std::cout <<
        "-------------------------" << "\n"  <<
        "Running Processes:"<<
    std::endl;
// 
    for(std::shared_ptr<CPU> i : _CPUList){
        if(i->checkStatus()==CPU::READY){
            std::cout <<"Idle\t\t\tCore: " << std::to_string(i->getID()) << std::endl;
        }
        else{
            std::cout << i->getProcessName()+"\t\tCore: "<< std::to_string(i->getID())<< 
            "\t\t" << std::to_string(i->getProcess()->getProgramCounter()) << " / " << std::to_string(i->getProcess()->getInstructionSetSize())<<std::endl;
            // std::cout << "List the busy processors" << std::endl;
        }
    }


    // std::cout <<
    //     "\n-------------------------" << "\n"  <<
    //     "Finished Processes:"<<
    // std::endl;
    // for(std::shared_ptr<Process> pastProcess : _processListHistory){
    //         if(pastProcess->getState() == ProcessState::TERMINATED){
    //             std::cout << pastProcess->getName()+"\t\tFinished" << 
    //             "\t\t" << std::to_string(pastProcess->getProgramCounter()) << " / " << std::to_string(pastProcess->getInstructionSetSize())<<std::endl;
    //             // std::cout << "List the busy processors" << std::endl;

    //         } 
    // }
}

void Scheduler::processSMI() {
    std::cout << "PROCESS SMI" << std::endl;

    // for(std::shared_ptr<CPU> i : _CPUList)
    //     std::cout << i->getProcessName() << std::endl;
    

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

