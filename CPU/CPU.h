#ifndef CPU_H
#define CPU_H

#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include "../Process/Instruction/Instruction.h"
#include "../Process/Process.h"
#include "../Config/config.h"
#include "../Clock/Clock.h"
#include "../Scheduler/Scheduler.h"

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
        void setDelayTime(float delayTime) {this->delayTime=delayTime;};
        std::shared_ptr<Process> getProcess();
        std::string getProcessName();


        CPUStatus checkStatus();

        int getID();

        void toggleStatus();
    private:
        CPUStatus status = CPUStatus::READY;       
        void CPURun();
        int _id;
        float delayTime;


        bool halt = false;
        static int dynamicID;

        std::shared_ptr<Process> _process = nullptr;

        friend class Scheduler;
};
#endif