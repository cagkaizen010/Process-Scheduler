#include "Print.h"

Print::Print(std::string msg) : Instruction(PRINT){
    this->msg = msg;
}

void Print::execute() {

    std::cout << msg << std::endl;
}
