#ifndef PRINT_H
#define PRINT_H

#include <cstdio>
#include <iostream>
#include <string>

#include "./Instruction.h"

class Instruction;

class Print : public Instruction {
    public:
        Print(std::string);
        ~Print() override = default ;

        void execute() override;
        std::string getInstructionType() override;
    private:
        std::string msg;
};



#endif