#include "Sub.h"

Sub::Sub(uint16_t var, uint16_t var1, uint16_t var2) : Instruction(SUB){
    this->var = var;
    this->var1 = var1;
    this->var2 = var2;
}

void Sub::execute(int cpu) {
    this->var = this->var1 - this->var2;
}

std::string Sub::getInstructionType() {
    return "Subtract";
}