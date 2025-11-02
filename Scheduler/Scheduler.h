#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <sstream>
#include <memory>

#include "../Process/Process.h"
#include "../CPU/CPU.h"

class Scheduler{
    public:
        static Scheduler* get();
        static void initialize(
            int cpuNum,
            std::string scheduler,
            int quantumCycles,
            int batchProcessFreq,
            int minIns,
            int maxIns,
            int delaysPerExec
        );

        enum SchedulingAlgorithm{
            FCFS,
            ROUND_ROBIN
        };
        struct ProcessInfo{
            std::string name;
            int pid;
            int cpuID;
            int lineCounter;
            int linesOfCode;

        };
        // Scheduler(SchedulingAlgorithm, int, std::string); 
        Scheduler();
        ~Scheduler() = default; 

        void addProcess(std::shared_ptr<Process>);
        std::shared_ptr<Process> findProcess(std::string );
        void startFCFS(float);
        void startRR(float, int);

        void run();
        void stop(); 

        void printStatus() ;
        // virtual void init() = 0;
        // virtual void execute() = 0;

        // std::vector<ProcessInfo> getRunningProcessInfo() const;

        std::string getName();
        std::string getLatestMsg();

    protected:

        std::stringstream outputBuffer;

    private:
        static Scheduler* _staticSchedulerPtr ;

        

        typedef std::queue<std::shared_ptr<Process>> ProcessQueue;
        typedef std::vector<std::shared_ptr<Process>> ProcessList;
        typedef std::unordered_map<std::string, std::shared_ptr<Process>> ProcessMap;
        ProcessQueue _readyQueue;
        ProcessList _processList;
        ProcessMap _processMap;


        SchedulingAlgorithm algo;
        int pid;
        std::string processName;

        // Config settings

        std::vector<std::shared_ptr<CPU>> _CPUList;
        float batchProcessFreq;
        int minIns;
        int maxIns;
        


        bool running = true;

        friend class ConsoleUI;
};

#endif