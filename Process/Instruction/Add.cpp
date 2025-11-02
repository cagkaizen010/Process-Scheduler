#include "./Add.h"

Add::Add(int var, int var1, int var2) : Instruction(ADD){
    this->var=var;
    this->var1=var1;
    this->var2=var2;
}

void Add::execute(int cpu) {
    this->var = this->var1 + this->var2;   
}


std::string Add::getInstructionType() {
    return "Add";
}
