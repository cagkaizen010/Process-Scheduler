#ifndef PROCESS_H
#define PROCESS_H

#include <cstdio>
#include <iostream>
#include <vector>

class Process {
    public:
        enum ProcessState{
            RUNNING,
            WAITING,
            READY,
            TERMINATED,
            NEW
        };
        Process(ProcessState, std::string, int);

        void updateState();

        ProcessState getState();
        int getPID();
        std::string getName();
        int getCPUCoreID();
        int getCommandCounter();
        int getLinesOfCode();
        int getRemainingTime();

        std::vector<std::string> instructions;
        std::vector<std::string> logs;


    private:
        ProcessState state;
        std::string name;
        int pid;
};

#endif