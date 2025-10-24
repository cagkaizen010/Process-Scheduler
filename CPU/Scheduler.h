#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <sstream>

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
            int remainingTime;

        };
        Scheduler(SchedulingAlgorithm, int, std::string); 

        void addProcess(std::shared_ptr<Process>);
        std::shared_ptr<Process> findProcess(std::string );
        void run();
        void stop(); 

        virtual void init() = 0;
        virtual void execute() = 0;

        std::vector<ProcessInfo> getRunningProcessInfo() const;

        std::string getName();
        std::string getLatestMsg();

    protected:
        typedef std::queue<std::shared_ptr<Process>> ProcessQueue;
        typedef std::vector<std::shared_ptr<Process>> ProcessList;
        typedef std::unordered_map<std::string, std::shared_ptr<Process>> ProcessMap;
        ProcessQueue readyQueue;
        ProcessList processList;
        ProcessMap processMap;

        std::stringstream outputBuffer;

    private:
        SchedulingAlgorithm algo;
        int pid;
        std::string processName;

        bool running = true;
};