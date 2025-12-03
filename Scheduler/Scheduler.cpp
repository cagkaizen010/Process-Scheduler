#include "Scheduler.h"


int Scheduler::getRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

Scheduler* Scheduler::_staticSchedulerPtr = nullptr;
Scheduler* Scheduler::get(){
    return _staticSchedulerPtr;
}

void Scheduler::initialize(int cpuNum, std::string scheduler, 
    int quantumCycles, int batchProcessFreq, int minIns, int maxIns, int delaysPerExec,
    int maxOverallmem, int memPerFrame, int minMemPerProc, int maxMemPerProc
    ){
    _staticSchedulerPtr = new Scheduler();

    _staticSchedulerPtr->cpuCycles = 0;
    for(int i = 0; i < cpuNum; i++){

        _staticSchedulerPtr-> _CPUList.push_back(std::make_shared<CPU>());
        _staticSchedulerPtr-> _CPUList.at(i)->setDelayTime(delaysPerExec);
    }

    // Defining dispatcher
    _staticSchedulerPtr->d = std::make_shared<Dispatcher>();
    _staticSchedulerPtr->d->setScheduler(_staticSchedulerPtr);
    _staticSchedulerPtr->d->setCPUList(_staticSchedulerPtr->_CPUList);

    _staticSchedulerPtr->batchProcessFreq = batchProcessFreq;
    _staticSchedulerPtr->schedulerType = scheduler;
    _staticSchedulerPtr->quantumCycle= quantumCycles;
    _staticSchedulerPtr->minIns= minIns;
    _staticSchedulerPtr->maxIns= maxIns;
    _staticSchedulerPtr->maxOverallmem = maxOverallmem;
    _staticSchedulerPtr->memPerFrame = memPerFrame;
    _staticSchedulerPtr->minMemPerProc = minMemPerProc;
    _staticSchedulerPtr->maxMemPerProc = maxMemPerProc;
    _staticSchedulerPtr->_memoryManager= new MemoryManager(
        maxOverallmem, 
        minMemPerProc/memPerFrame, 
        maxMemPerProc/memPerFrame, 
        memPerFrame
    );

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
    static int lastCycle = 0;

    while(this->running){

        int currentCycle = Clock::getCycle();
        if(currentCycle >lastCycle ){
            if((Clock::getCycle() % static_cast<int>(this->batchProcessFreq)) == 0){


                createProcess("p_" + std::to_string(randNum), maxMemPerProc);
                randNum++;
            }
            lastCycle = currentCycle;
        }
    }
}

void Scheduler::addToReadyQueue(std::shared_ptr<Process> p){

    std::lock_guard<std::mutex> lock(schedulerMutex);
    this->_readyQueue.push(p);
}

std::shared_ptr<Process> Scheduler::retrieveFromReadyQueue() {
    std::lock_guard<std::mutex> lock(schedulerMutex);
    std::string placeholder;

    std::shared_ptr<Process> temp = this->_readyQueue.front();
    this->_readyQueue.pop();

    return temp;
}

bool Scheduler::isReadyQueueEmpty(){
    std::lock_guard<std::mutex> lock(schedulerMutex);
    return this->_readyQueue.empty();

}



void Scheduler::addProcess(std::shared_ptr<Process> process){
    std::lock_guard<std::mutex> lock(schedulerMutex);
    this->_processList.push_back(process);
    this->_processListHistory.push_back(process);
    this->_processMap[process->getName()] = process;


}

void Scheduler::runFCFS(float delayTime) {
    if(!this->running){
        this->running = true;
        std::thread t(&Scheduler::startFCFS, this,  delayTime);
        t.detach();

        std::cout <<"FCFS is running" << std::endl;
    }
}
void Scheduler::startFCFS(float delayTime){
    static int lastCycle_fcfs = 0;

    while (this->running)
    while(this->_schedulerRunning){
        int currentCycle_fcfs = Clock::getCycle();
        if(currentCycle_fcfs > lastCycle_fcfs){
            if(this->_processList.size()!=0){
                this->addToReadyQueue(this->_processList.front());
                this->_processList.erase(this->_processList.begin());
            }

        }
        lastCycle_fcfs = currentCycle_fcfs;
    }
}

void Scheduler::runRR(float delayTime, int quantumCycles){
    if(!this->running){
        this->running = true;
        std::thread t(&Scheduler::startRR, this,  delayTime, quantumCycles);
        t.detach();

        std::cout <<"RR is running" << std::endl;
    }
}
void Scheduler::startRR(float delayTime, int quantumCycles){
    static int lastCycle_fcfs = 0;

    while (this->running)
    while (this-> _schedulerRunning){
        int currentCycle_fcfs = Clock::getCycle();
        if(currentCycle_fcfs > lastCycle_fcfs){
            if(!(Clock::getCycle() % (quantumCycles) == 0)){
                if(this->_processList.size()!=0){
                    this->_readyQueue.push(this->_processList.front());
                    this->_processList.erase(this->_processList.begin());
                }

            }
            else{
                if(this->_processList.size()!=0){
                    this->_readyQueue.push(this->_processList.front());
                    this->_processList.erase(this->_processList.begin());
                }

                for(std::shared_ptr<CPU> cpu : this->_CPUList){
                    if(cpu->getProcess() != nullptr){
                        this->_readyQueue.push(cpu->getProcess());
                        cpu->setProcess(nullptr);
                    }
                }
            }
        }

        lastCycle_fcfs = currentCycle_fcfs;
    }
}


// Does not work properly
void Scheduler::stop(){
    this->_schedulerRunning =false;
    this->running = false;
    this->d->stopDispatcher();
    Clock::stop();
}

std::shared_ptr<Process> Scheduler::findProcess(std::string processName){

    if(this->_processMap.find(processName)!= this->_processMap.end()) return this-> _processMap[processName];
    else return nullptr;
}

void Scheduler::createProcess(std::string processName, int allocatedMemory){
    // this  a random 


    int randomPID= getRandomInt(1000, 999999);

    ProcessControlBlock pcb = ProcessControlBlock{randomPID, processName,-1, this->schedulerType, this->quantumCycle};

    std::shared_ptr<Process> p = std::make_shared<Process>(pcb, allocatedMemory, allocatedMemory/this->memPerFrame);

    p->generateInstruction(this->minIns, this->maxIns);

    this->addProcess(p);

}
std::vector<std::shared_ptr<Process>> Scheduler::getProcesses(){
    return _processListHistory;
}

void Scheduler::printStatus() {
    int cpuReadyCount = 0;
    for (std::shared_ptr<CPU> cpu : this->_CPUList) 
        if (cpu->checkStatus() == CPU::READY) {
            cpuReadyCount++;
        }
        else {
            std::cout << "CPU #" << cpu->getID() << " is still running" << std::endl;
        }
    
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
        if(i->checkStatus()==CPU::READY || (i->getProcess() == nullptr)){
            std::cout <<"Idle\t\t\tCore: " << std::to_string(i->getID()) << std::endl;
        }
        else{
            if (i->getProcess() != nullptr){
                std::cout << i->getProcessName()+"\t\tCore: "<< std::to_string(i->getID())<< 
                "\t\t" << std::to_string(i->getProcess()->getProgramCounter()) << " / " << std::to_string(i->getProcess()->getInstructionSetSize())<< 
                "\t" << "Core #:" + std::to_string(i->getProcess()->getCPUCoreID()) <<std::endl;
            }
        }
    }

    std::cout <<
        "\n-------------------------" << "\n"  <<
        "Finished Processes:"<<
    std::endl;
    for(std::shared_ptr<Process> pastProcess : _processListHistory){
            if(pastProcess->getState() == ProcessState::TERMINATED){
                std::cout << pastProcess->getName()+"\t\tFinished" << 
                "\t\t" << std::to_string(pastProcess->getProgramCounter()) << " / " << std::to_string(pastProcess->getInstructionSetSize())<<
                 "\t" << "Core #:" + std::to_string(pastProcess->getCPUCoreID()) <<std::endl;

            } 
    }
}


void Scheduler::reportUtil() {

    std::ofstream outputFile("csopesy-log.txt", std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open console_log.txt for writing." << std::endl;
        return;
    }


    int cpuReadyCount = 0;
    for (std::shared_ptr<CPU> cpu : this->_CPUList) 
        if (cpu->checkStatus() == CPU::READY) cpuReadyCount++;
    
    float CPUUtil = 100.0 * (this->_CPUList.size() - cpuReadyCount)/(this->_CPUList.size());
    
    outputFile<<
        "CPU utilization: " + std::to_string(CPUUtil) + "\n" +
        "Cores used: " + std::to_string(this->_CPUList.size() - cpuReadyCount) + "\n" +
        "Cores available: " + std::to_string(cpuReadyCount) <<
    std::endl;
    
    outputFile<<
        "-------------------------" << "\n"  <<
        "Running Processes:"<<
    std::endl;
// 
    for(std::shared_ptr<CPU> i : _CPUList){
        if(i->checkStatus()==CPU::READY){
            outputFile <<"Idle\t\t\tCore: " << std::to_string(i->getID()) << std::endl;
        }
        else{
            outputFile << i->getProcessName()+"\t\tCore: "<< std::to_string(i->getID())<< 
            "\t\t" << std::to_string(i->getProcess()->getProgramCounter()) << " / " << std::to_string(i->getProcess()->getInstructionSetSize())<< 
            "\t" << "Core #:" + std::to_string(i->getProcess()->getCPUCoreID()) <<std::endl;
            // std::cout << "List the busy processors" << std::endl;
        }
    }


    outputFile<<
        "\n-------------------------" << "\n"  <<
        "Finished Processes:"<<
    std::endl;
    for(std::shared_ptr<Process> pastProcess : _processListHistory){
            if(pastProcess->getState() == ProcessState::TERMINATED){
                outputFile << pastProcess->getName()+"\t\tFinished" << 
                "\t\t" << std::to_string(pastProcess->getProgramCounter()) << " / " << std::to_string(pastProcess->getInstructionSetSize())<<
                 "\t" << "Core #:" + std::to_string(pastProcess->getCPUCoreID()) <<std::endl;

            } 
    }

}


void Scheduler::processSMI(){
    this->_memoryManager->getAllocator()->printProcesses();
}
void Scheduler::vmstat(){
    this->_memoryManager->getAllocator()->vmstat();
}

std::string Scheduler::getName() {
    return this->processName;
}

