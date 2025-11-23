#ifndef PROCESS_H
#define PROCESS_H

#include <random>
#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

#include "./Instruction/Instruction.h"
#include "./Instruction/Declare.h"
#include "./Instruction/Add.h"
#include "./Instruction/Sub.h"
#include "./Instruction/Print.h"
#include "../Clock/Clock.h"


enum ProcessState{
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};


// Eventually, implement progCounter functionality
struct ProcessControlBlock{
    int pid;
    std::string pname;
    int CPUCoreID;
    std::string schedulingType;
    int quantumCycles;
    int progCounter=0;
    ProcessState pstate=NEW;
};

typedef std::vector<std::shared_ptr<Instruction>> InstructionSet;

class Process {
    public:
        std::mutex mutex;
        Process(ProcessControlBlock, int, int );

        std::string randStr();

        int getID();
        void setID(int pid);
        bool isEmpty();

        std::string getName();
        void setName(std::string);

        int getProgramCounter();
        void incrementProgramCounter();

        ProcessState getState();
        void setState(ProcessState );

        void setCPUCoreID(int coreID);
        int getCPUCoreID();

        std::string getSchedulingType();
        int getQuantumCycles();
        int getInstructionSetSize();
        void generateInstruction(int, int);
        void listInstructions();
        // void listCurrentlyRunningInstructions();
        void deleteTopInstruction();
        std::shared_ptr<Instruction> getInstruction();

        void execute();
        static int getRandomInt(int, int);

        static int setRequiredPages(int, int);
        static int setRequiredMemory(int, int);
        static int getRequiredPages();
        int getRequiredMemory();
    private:
        std::mutex processMutex;
        ProcessControlBlock pcb;

        InstructionSet text; 

        // Should not change throughout any process instance
        int _requiredMemory  ;
        static int requiredPages;
        static int currentMemory;

};

#endif