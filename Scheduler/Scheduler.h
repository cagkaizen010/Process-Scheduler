#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <sstream>
#include <memory>
#include <thread>
#include <chrono>

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

        void schedulerTest();
        void schedulerRun();
        void schedulerStop();

        void addProcess(std::shared_ptr<Process>);
        std::shared_ptr<Process> findProcess(std::string );
        void startFCFS(float);
        void runFCFS();
        void startRR(float, int);
        void runRR();

        void run();
        void stop(); 

        void printStatus() ;
        void processSMI();
        // virtual void init() = 0;
        // virtual void execute() = 0;

        // std::vector<ProcessInfo> getRunningProcessInfo() const;

        std::string getName();
        std::string getLatestMsg();

    protected:

        std::stringstream outputBuffer;

    private:
        static Scheduler* _staticSchedulerPtr ;
        static int getRandomInt(int, int);

        

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
        


        bool _schedulerRunning = false;
        bool running = false;

        friend class ConsoleUI;
};

#endif