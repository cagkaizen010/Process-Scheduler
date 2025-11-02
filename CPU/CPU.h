#ifndef CPU_H
#define CPU_H

#include <memory>

#include "../Process/Instruction/Instruction.h"
#include "../Process/Process.h"

// Executes the instruction inside the Process

class CPU {
    public:
        enum CPUStatus{
            READY,
            BUSY
        };
        CPU();
        ~CPU() = default;

        void setProcess(std::shared_ptr<Process> process);
        CPUStatus checkStatus();

        int getID();

        void toggleStatus();
        void CPUExecute(Instruction* inst);
    private:
        CPUStatus status = CPUStatus::READY;       
        int _id;
        bool halt = false;
        static int dynamicID;

        std::shared_ptr<Process> _process = nullptr;
};



#endif