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
                    // std::cout << "Thread #" << std::this_thread::get_id() << " " ;
                    // std::cout << "Status CPU #" << cpu->getID() << ": " << cpu->checkStatus() << std::endl;

                    if((cpu->checkStatus() == CPU::READY) ){
                            // std::cout << "CPU #" << cpu->getID() << " is ready" << std::endl;
                        // std::cout << "flag status: " << _scheduler->isReadyQueueEmpty()<< std::endl;
                        if(_scheduler->isReadyQueueEmpty() == 0){
                            // std::cout << "ready queue is not empty " << std::endl;
                            // cpu->setProcess(_scheduler->_readyQueue.front());
                            // std::cout << "process->isEmpty() " << process->isEmpty()<<std::endl;
                            // std::cout << "process->getCPuCoreID() " << process->getCPUCoreID()<<std::endl;
                            std::shared_ptr<Process> processTemp = _scheduler->_readyQueue.front();
                            

                            if (!processTemp->isEmpty() && processTemp->getCPUCoreID() == -1){
                                // std::cout << "Attempting to allocate.." << std::endl;
                                // std::cout << "processTemp->getCPUCoreID(): " << processTemp->getCPUCoreID() << std::endl;
                                if (_scheduler->_memoryManager->allocate(processTemp) ){
                                    std::shared_ptr<Process> process = _scheduler->retrieveFromReadyQueue();
                                    // _scheduler->retrieveFromReadyQueue();

                                    // std::cout << "Allocation successful, setting " + process->getName() + " to CPU #" << cpu->getID()  << std::endl;
                                    // std::cout << "current _readyQueue.front(): " << _scheduler->_readyQueue.front()->getName() << std::endl;
                                    cpu->setProcess(process);
                                }
                            }
                            // std::cout << "CPU #" + cpu->getID() << "got Process " << cpu->getProcess() << std::endl;
                                // else {
                                //     std::cout << "unable to allocate " << processTemp->getName();
                                //     std::cout << " into CPU #" << cpu->getID() << std::endl;
                                // }

                            // std::cout << "current _readyQueue.front(): " << _scheduler->_readyQueue.front()->getName() << std::endl;

                        }

                    }else
                    {
                        if (cpu->checkStatus() == CPU::BUSY){
                            // std::cout << "CPU #" << cpu->getID() << " is still running, " << std::endl;
                            // std::cout << "CPU #" << cpu->getID() << " is running " <<cpu->getProcessName()  << std::endl;
                            // std::cout << "cpu->getProcess(): " << cpu->getProcess() << std::endl;
                            // std::cout << "cpu->getProcess()->isEmpty(): " << cpu->getProcess()->isEmpty() << std::endl;
                            if(cpu->getProcess() != nullptr && cpu->getProcess()->isEmpty()){
                                // std::cout << "Deallocating process " << cpu->getProcess()->getName()<< std::endl;
                                cpu->getProcess()->setState(ProcessState::TERMINATED);
                                _scheduler->_memoryManager->deallocate(cpu->getProcess());
                                cpu->setProcess(nullptr);
                                // cpu->toggleStatus(); // breaks code
                            }   
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