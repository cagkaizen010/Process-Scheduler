#ifndef SUB_H
#define SUB_H

#include "./Instruction.h"

class Instruction;

class Sub : public Instruction {
    public:
        Sub(uint16_t, uint16_t, uint16_t);
        ~Sub() override= default;

        void execute(int cpu) override;
        std::string getInstructionType() override;
    private:
        int var;
        int var1;
        int var2;
};



#endif