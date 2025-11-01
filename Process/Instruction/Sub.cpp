#include "Sub.h"

Sub::Sub(int var, int var1, int var2) : Instruction(SUB){
    this->var = var;
    this->var1 = var1;
    this->var2 = var2;
}

void Sub::execute() {
    this->var = this->var1 - this->var2;
}

std::string Sub::getInstructionType() {
    return "Subtract";
}