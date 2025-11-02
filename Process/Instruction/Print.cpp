#include "Print.h"

Print::Print(std::string msg) : Instruction(PRINT){
    this->msg = msg;
}

void Print::execute(int cpu) {

    std::cout << msg << std::endl;
}

std::string Print::getInstructionType(){
    return "Print";
}