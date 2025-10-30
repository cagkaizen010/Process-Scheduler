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
        ~Print() = default ;

        void execute() override;
    private:
        std::string msg;
};



#endif