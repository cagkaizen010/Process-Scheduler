#ifndef CPU_H
#define CPU_H

#include "../Process/Instruction/Instruction.h"

// Executes the instruction inside the Process

class CPU {
    public:

        enum CPUStatus{
            READY,
            BUSY
        };
        CPU();
        ~CPU() = default;

        void changeStatus(CPUStatus status);
        void CPUExecute(Instruction* inst);
    private:
        CPUStatus status;       

};



#endif