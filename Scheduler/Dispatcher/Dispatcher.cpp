#include "Dispatcher.h"

Dispatcher::Dispatcher(){

}



void Dispatcher::setScheduler(Scheduler* s){
    this->_scheduler = s;
}
void Dispatcher::setCPUList(std::vector<std::shared_ptr<CPU>> _CPUList){
    this->_CPUList = _CPUList;
}

void Dispatcher::startDispatcher() {
    std::cout <<"Dispatcher started"<< std::endl;
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    this->_dispatcherRunningFlag = true;
    std::thread dispatcherThread(&Dispatcher::run, this );
    dispatcherThread.detach();

}

void Dispatcher::run(){
    static int lastCycle = 0;

    while(this->_dispatcherRunningFlag){

        int currentCycle = Clock::getCycle();

        if(currentCycle > lastCycle){
            if(this->_scheduler == nullptr){
                std::cout << "ERROR! _scheduler is nullptr!"<< std::endl;
                break;
            }
            if(this->_CPUList.empty()){
                std::cout << "ERROR! _CPUList is empty!"<< std::endl;
                break;
            }
            
            // if(!_scheduler->_readyQueue.empty())
            // Scan through CPU list to check which is available
            // If CPU is READY, assign it a process: (setProcess(Process))
            
                // std::unique_lock<std::mutex> lock(Clock::clockMutex);
                for( std::shared_ptr<CPU> cpu: _CPUList){
                    if((cpu->checkStatus() == CPU::READY) ){
                        // std::cout << "flag status: " << _scheduler->isReadyQueueEmpty()<< std::endl;
                        if(_scheduler->isReadyQueueEmpty() == 0){
                            // cpu->setProcess(_scheduler->_readyQueue.front());
                            cpu->setProcess(_scheduler->retrieveFromReadyQueue());
                            // std::cout << "CPU #" + cpu->getID() << "got Process " << cpu->getProcess() << std::endl;


                            // std::cout << "Set into CPU #" << cpu->getProcess()->getCPUCoreID()<<std::endl;
                        }

                    }else
                    {
                        if (cpu->checkStatus() == CPU::BUSY){
                            // std::cout << "CPU #" << cpu->getID() << " is still running, " << cpu->getProcessName()<< std::endl;
                        }
                    }
                }
            lastCycle=currentCycle;
        }
    }
}

void Dispatcher::stopDispatcher() {
    std::cout << "dispatcher thread stopped";
    this->_dispatcherRunningFlag = false;
}