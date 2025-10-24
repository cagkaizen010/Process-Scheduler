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


        // Basic Process Instructions
        void PRINT(std::string msg = "Hello from Process " );
        void DECLARE(int var, int value = 0);
        void ADD(int var, int var2 = 0, int var3 = 0);
        void SUBTRACT(int var, int var2 = 0, int var3 = 0);
    private:
        ProcessState state;
        std::string name;
        int pid;
};