#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#include "../Process/Process.h"

class Scheduler{
    public:
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
        Scheduler(SchedulingAlgorithm, int, std::string); 

        void addProcess(std::shared_ptr<Process>);
        void run();

        std::vector<ProcessInfo> getRunningProcessInfo() const;
        // std::vector<ProcessInfo> get

        std::string getName();

    protected:
        typedef std::queue<std::shared_ptr<Process>> ProcessQueue;
        typedef std::vector<std::shared_ptr<Process>> ProcessList;
        typedef std::unordered_map<std::string, std::shared_ptr<Process>> ProcessMap;
        ProcessQueue readyQueue;
        ProcessList processList;
        ProcessMap processMap;


    private:
        SchedulingAlgorithm algo;
        int pid;
        std::string processName;

        bool running = true;
};