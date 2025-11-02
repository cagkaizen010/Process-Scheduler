#include "CPU.h"
int CPU::dynamicID = 0;

CPU::CPU() {
    this->_id=CPU::dynamicID;
    CPU::dynamicID++;
}

void CPU::setProcess(std::shared_ptr<Process> process){
    if(this->_process!= nullptr) this->_process->setCPUCoreID(-1);

    
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

void CPU::CPUExecute(Instruction* inst){
    this->status = CPUStatus::BUSY;
    inst->execute(0);
}



