#ifndef ADD_H
#define ADD_H

#include <cstdio>
#include <iostream>
#include "./Instruction.h"


// COnvert all to uint16_t for memory portion
class Instruction;
class Add : public Instruction {
    public:
        Add(uint16_t, uint16_t, uint16_t);
        ~Add() override = default;

        void execute(int cpu) override ;
        std::string getInstructionType() override ;

    private:
        uint16_t var;
        uint16_t var1=0;
        uint16_t var2=0;
};

#endif