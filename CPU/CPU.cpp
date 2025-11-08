#include "CPU.h"
int CPU::dynamicID = 0;
std::atomic<float> CPU::cpuCycles(0);
std::mutex CPU::mtx;

CPU::CPU() {
    if (CPU::dynamicID < 4){
        std::cout << "CPU::dynamicID: " + std::to_string(CPU::dynamicID) << std::endl;

        this->_id=CPU::dynamicID;
        CPU::dynamicID++;
    }
    // else CPU::dynamicID = 0;
    

    std::thread tickThread(&CPU::CPURun, this);
    tickThread.detach();
}

void CPU::setProcess(std::shared_ptr<Process> process){
    this->_process = process;

    // bool tempCPUStatus = (process == nullptr) ? CPU::READY : CPU::BUSY;
    // std::cout << "Setting CPU Process to: " << std::to_string(tempCPUStatus) << std::endl;
    // this->status = (process == nullptr) ? CPU::READY : CPU::BUSY;
    // std::cout << "CPU Status: " << this->status << std::endl;
}
std::shared_ptr<Process> CPU::getProcess(){
    return this->_process;
}


std::string CPU::getProcessName() {
    return this->_process->getName();
}

CPU::CPUStatus CPU::checkStatus(){
    return this->status;
}

int CPU::getID() {
    return _id;
}

void CPU::toggleStatus(){
    if(this->status == CPUStatus::BUSY)
        this->status = CPUStatus::READY;
    else if(this->status == CPUStatus::READY)
        this->status = CPUStatus::BUSY;
}

void CPU::executeCPUCycle(){
    cpuCycles = cpuCycles+1;
}

void CPU::CPURun(){
    this->halt = false;
    while(!this->halt){
        // this->CPUExecute();
        if((fmod(cpuCycles, 1+this->delayTime ) == float(0)) || (this->delayTime == 0)){
            // std::cout << "this->cpuCycles: " << cpuCycles<< std::endl;
            if (this->_process != nullptr ){

                // If the process hasn't been assigned a CPU,
                // assign the current process to the current CPU
                if(this->_process->getCPUCoreID() == -1)
                    this->_process->setCPUCoreID(this->getID());

                // If the process has an assigned CPU,
                // execute the process
                if(this->_process->getCPUCoreID() == this->getID()){
                    this->_process->execute();
                    this->status = CPUStatus::BUSY;
                }
                // If process is finished,
                // setProcess to null, and set the CPU to READY
                if( this->_process->getState() == ProcessState::TERMINATED){
                    this->setProcess(nullptr);
                    this->status= CPUStatus::READY;
                }
                
            }
            
        // CPU detects if its time to execute
        }
        // std::unique_lock<std::mutex> lock(mtx);
        // cpuCycles = cpuCycles + 1;
        // lock.unlock();

        // CPU stops completely
    }
    std::cout << "CPU is now ready" << std::endl;
    this->status = CPUStatus::READY;
}


