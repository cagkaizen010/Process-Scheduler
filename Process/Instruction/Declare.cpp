#include "./Declare.h"


// Declare::Declare(std::string varName = "var", int var) : Instruction(DECLARE){
// }

Declare::Declare(std::string var, int value) : Instruction(DECLARE){
    this->var = var;
    this->value = value;
}


void Declare::execute(int cpu) {
    std::cout << this->var << " = " << this->value << std::endl;
}

std::string Declare::getInstructionType() {
    return "Declare";
}