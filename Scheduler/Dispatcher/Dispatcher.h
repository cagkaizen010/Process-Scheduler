#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <vector>
#include <memory>
#include <string>
#include <thread>
#include "../../CPU/CPU.h"
#include "../Scheduler.h"
// #include "../../Clock/Clock.h"

class Scheduler;
class Dispatcher {
    public:

        // Dispatcher(std::vector<std::shared_ptr<CPU>>, Scheduler*);
        Dispatcher();
        // void initialize(std::vector<std::shared_ptr<CPU>>, Scheduler*);

        ~Dispatcher() = default;

        void setScheduler(Scheduler* );
        void setCPUList(std::vector<std::shared_ptr<CPU>>);
        bool isRunning(){ return _dispatcherRunningFlag;};

        void run();
        void stopDispatcher();
        void startDispatcher();

        // void createDispatcherThread();
    private:

        std::vector<std::shared_ptr<CPU>> _CPUList;
        Scheduler* _scheduler = nullptr;
        
        bool _dispatcherRunningFlag = false;
};

#endif 