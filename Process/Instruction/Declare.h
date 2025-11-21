#ifndef DECLARE_H 
#define DECLARE_H

#include <cstdio>
#include <iostream>
#include <string>
#include "./Instruction.h"

class Instruction;
class Declare: public Instruction {
    public:
        Declare(std::string, uint16_t);
        // Declare()  ;
        ~Declare() override = default;

        void execute(int cpu) override ;
        std::string getInstructionType() override;
    private:
        std::string var;
        int value;
};

#endif