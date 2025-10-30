#include "./Declare.h"


Declare::Declare(int var, int value) : Instruction(DECLARE){
    this->var = var;
    this->value = value;
}

