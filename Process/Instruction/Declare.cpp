#include "./Declare.h"


Declare::Declare(int var, int value) : Instruction(DECLARE){
    this->var = var;
    this->value = value;
}

void Declare::execute() {
    this->var = this->value;   
}
