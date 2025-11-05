
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

    for(int i = 0; i < cpuNum; i++)
        _staticSchedulerPtr-> _CPUList.push_back(std::make_shared<CPU>());

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
        // std::vector<std::shared_ptr<Instruction>> text;
        int randNum =0;
        cpuCycles = 0;
        while(this->running){


            if(fmod(cpuCycles,this->batchProcessFreq) ==float(0)){
                ProcessControlBlock pcb = ProcessControlBlock{randNum, "p_" + std::to_string(randNum),-1};
                std::shared_ptr<Process> p = std::make_shared<Process>(pcb );
        
                p->generateInstruction();
                // std::cout << p->getName()<< std::endl;
                this->addProcess(p);


                randNum++;
            }
            // std::cout << "INSIDE SCHEDULER: " << this->_processList.size() << std::endl;
            cpuCycles++;
        }
        std::cout << "Finished generating processes!" << std::endl;


}

void Scheduler::addProcess(std::shared_ptr<Process> process){
    // this->_readyQueue.push(process);
    this->_processList.push_back(process);
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
    for(std::shared_ptr<CPU> i : _CPUList){
        if(i->checkStatus()==CPU::READY){
            std::cout <<"Idle\t\t\tCore: " << std::to_string(i->getID()) << std::endl;
        }
        else{
            std::cout << i->getProcessName()+"\t\tCore: "<< std::to_string(i->getID())<< std::endl;
            // std::cout << "List the busy processors" << std::endl;
        }
    }
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

