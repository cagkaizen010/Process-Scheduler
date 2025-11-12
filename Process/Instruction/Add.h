#ifndef ADD_H
#define ADD_H

#include <cstdio>
#include <iostream>
#include "./Instruction.h"

class Instruction;
class Add : public Instruction {
    public:
        Add(int, int, int);
        ~Add() override = default;


        void execute(int cpu) override ;
        std::string getInstructionType() override ;

    private:
        int var;
        int var1=0;
        int var2=0;
};

#endif