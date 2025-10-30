#ifndef PRINT_H
#define PRINT_H

#include <string>

#include "./Instruction.h"

class Instruction;

class Print : public Instruction {
    public:
        Print(std::string);
        ~Print() = default ;
    private:
        std::string msg;
};



#endif