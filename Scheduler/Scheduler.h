#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
// #include <string>
#include <unordered_map>
#include <sstream>
#include <memory>
#include <thread>
#include <mutex>
#include <chrono>
#include <cmath>
#include <fstream>

#include "../Clock/Clock.h"
#include "../Process/Process.h"
#include "../CPU/CPU.h"
#include "../Memory/MemoryManager.h"
#include "./Dispatcher/Dispatcher.h"

// static float cpuCycles=0;
class Dispatcher;
class MemoryManager;
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
            int delaysPerExec,
            int maxOverallmem, 
            int memPerFrame, 
            int minMemPerProc, 
            int maxMemPerProc
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
        Scheduler(){};
        ~Scheduler() = default; 

        void schedulerTest();
        void schedulerRun();
        void schedulerStop();
        void addProcess(std::shared_ptr<Process>);

        void addToReadyQueue(std::shared_ptr<Process> p);
        std::shared_ptr<Process> retrieveFromReadyQueue();
        bool isReadyQueueEmpty();

        std::shared_ptr<Process> findProcess(std::string );
        void createProcess(std::string, int);
        std::vector<std::shared_ptr<Process>> getProcesses();

        void runFCFS( float);
        void startFCFS(float);
        void runRR(float, int);
        void startRR(float, int);

        bool isRunning(){ return _schedulerRunning;};

        void run();
        void stop(); 

        void printStatus() ;
        void reportUtil();
        void processSMI();
        void vmstat();

        std::string getName();

    protected:

        std::stringstream outputBuffer;

    private:
        std::mutex schedulerMutex;
        static Scheduler* _staticSchedulerPtr;
        MemoryManager* _memoryManager = nullptr;

        static int getRandomInt(int, int);

        typedef std::queue<std::shared_ptr<Process>> ProcessQueue;
        typedef std::vector<std::shared_ptr<Process>> ProcessList;
        typedef std::unordered_map<std::string, std::shared_ptr<Process>> ProcessMap;

        ProcessQueue _readyQueue;
        ProcessList _processList;
        ProcessMap _processMap;
        ProcessList _processListHistory;

        SchedulingAlgorithm algo;
        int pid;
        std::string processName;

        // Config settings

        std::vector<std::shared_ptr<CPU>> _CPUList;
        std::shared_ptr<Dispatcher> d;

        float delayTime;
        float batchProcessFreq;
        std::string schedulerType;
        int quantumCycle;
        int minIns;
        int maxIns;
        float cpuCycles;
        int maxOverallmem; 
        int memPerFrame; 
        int minMemPerProc; 
        int maxMemPerProc;

        bool _schedulerRunning = false;
        bool running = false;

        friend class ConsoleUI;
        friend class Dispatcher;
        friend class MemoryManager;
};

#endif