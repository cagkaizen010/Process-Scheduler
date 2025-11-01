#ifndef DECLARE_H 
#define DECLARE_H

#include <cstdio>
#include <iostream>
#include <string>
#include "./Instruction.h"

class Instruction;
class Declare: public Instruction {
    public:
        Declare(std::string, int);
        // Declare()  ;
        ~Declare() override = default;

        void execute() override ;
        std::string getInstructionType() override;
    private:
        std::string var;
        int value;
};

#endif