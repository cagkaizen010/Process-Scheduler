#include "Dispatcher.h"

Dispatcher::Dispatcher(){

    // std::thread dispatcherThread(&Dispatcher::run, this );
    // dispatcherThread.detach();
}

// Dispatcher::Dispatcher(std::vector<std::shared_ptr<CPU>> _CPUList, Scheduler* scheduler){
//     this->_CPUList = _CPUList;
//     this->_scheduler = scheduler;
//     std::thread dispatcherThread(&Dispatcher::run, this );
//     dispatcherThread.detach();

//     this->startDispatcher();
// }

// void Dispatcher::initialize(std::vector<std::shared_ptr<CPU>> _CPUList, Scheduler* scheduler){
//     this->_CPUList = _CPUList; 
// }

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
    while(this->_dispatcherRunningFlag){
        if(this->_scheduler == nullptr){
            std::cout << "ERROR! _scheduler is nullptr!"<< std::endl;
            break;
        }
        if(this->_CPUList.empty()){
            std::cout << "ERROR! _CPUList is empty!"<< std::endl;
            break;
        }

        // Scan through CPU list to check which is available
        // If CPU is READY, assign it a process: (setProcess(Process))
        for( std::shared_ptr<CPU> cpu: _CPUList){
            if((cpu->checkStatus() == CPU::READY) ){
                if(!_scheduler->_readyQueue.empty()){
                    cpu->setProcess(_scheduler->_readyQueue.front());
                    _scheduler->_readyQueue.pop();
                }
            }
        }

    }


}

void Dispatcher::stopDispatcher() {
    std::cout << "dispatcher thread stopped";
    this->_dispatcherRunningFlag = false;
}