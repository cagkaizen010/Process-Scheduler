#ifndef SUB_H
#define SUB_H

#include "./Instruction.h"

class Instruction;

class Sub : public Instruction {
    public:
        Sub(int, int, int);
        ~Sub() override= default;

        void execute() override;
        std::string getInstructionType() override;
    private:
        int var;
        int var1;
        int var2;
};



#endif