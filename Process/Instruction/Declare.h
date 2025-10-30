#ifndef DECLARE_H 
#define DECLARE_H

#include "./Instruction.h"

class Instruction;
class Declare: public Instruction {
    public:
        Declare(int, int );
        ~Declare() = default;

        void execute() override;
    private:
        int var;
        int value;
};

#endif