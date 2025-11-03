#include "CPU.h"
int CPU::dynamicID = 0;

CPU::CPU() {
    this->_id=CPU::dynamicID;
    CPU::dynamicID++;
    std::thread tickThread(&CPU::CPURun, this);
    tickThread.detach();
}

void CPU::setProcess(std::shared_ptr<Process> process){
    this->_process = process;
    this->status = (process == nullptr) ? CPU::READY : CPU::BUSY;
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


void CPU::CPURun(){
    this->halt = false;
    this->status = CPUStatus::BUSY;
    while(!this->halt){
        // this->CPUExecute();
        if (this->_process != nullptr ){
            std::cout << "CPU " <<this->getID()<< " is processing"<< std::endl;
            this->_process->setCPUCoreID(this->_id);
            this->_process->execute();
            if(this->_process->getState() == ProcessState::TERMINATED){
                this->setProcess(nullptr);
                // this->status= CPUStatus::READY;
                this->halt = true;
            }
        }
        // else std::cout << "CPU "<< this->getID() << " free"<< std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    this->status = CPUStatus::READY;
}

// void CPU::CPUExecute(){
    // this->status = CPUStatus::BUSY;
// }



