#ifndef PROCESS_H
#define PROCESS_H

#include <random>
#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>
#include <string>

#include "./Instruction/Instruction.h"
#include "./Instruction/Declare.h"
#include "./Instruction/Add.h"
#include "./Instruction/Sub.h"
#include "./Instruction/Print.h"

enum ProcessState{
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

struct ProcessControlBlock{
    int pid;
    std::string pname;
    int progCounter=0;
    ProcessState pstate=NEW;
};

typedef std::vector<std::shared_ptr<Instruction>> InstructionSet;

class Process {
    public:
        
        Process(ProcessControlBlock, InstructionSet );

        // void print(std::string msg);
        ProcessState getStatus();
        int getID();
        void setID(int pid);

        void generateInstruction();
        void listInstructions();
        
    private:
        ProcessControlBlock pcb;
        InstructionSet text; 
};

#endif