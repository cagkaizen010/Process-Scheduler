#include "CPU.h"

CPU::CPU() {
    this->status = CPUStatus::READY;
}

void CPU::changeStatus(CPUStatus status){
    this->status = status;
}

void CPU::CPUExecute(Instruction* inst){
    inst->execute();
}