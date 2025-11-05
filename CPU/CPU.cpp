#include "CPU.h"
int CPU::dynamicID = 0;

CPU::CPU() {
    if (CPU::dynamicID < 4){
        std::cout << "CPU::dynamicID: " + std::to_string(CPU::dynamicID) << std::endl;

        this->_id=CPU::dynamicID;
        CPU::dynamicID++;
    }
    // else CPU::dynamicID = 0;
    

    std::thread tickThread(&CPU::CPURun, this);
    tickThread.detach();
}

void CPU::setProcess(std::shared_ptr<Process> process){
    this->_process = process;

    // bool tempCPUStatus = (process == nullptr) ? CPU::READY : CPU::BUSY;
    // std::cout << "Setting CPU Process to: " << std::to_string(tempCPUStatus) << std::endl;
    this->status = (process == nullptr) ? CPU::READY : CPU::BUSY;
    // std::cout << "CPU Status: " << this->status << std::endl;
}
std::shared_ptr<Process> CPU::getProcess(){
    return this->_process;
}


std::string CPU::getProcessName() {
    return this->_process->getName();
}

CPU::CPUStatus CPU::checkStatus(){
    return this->status;
}

int CPU::getID() {
    return _id;
}

void CPU::toggleStatus(){
    if(this->status == CPUStatus::BUSY)
        this->status = CPUStatus::READY;
    else if(this->status == CPUStatus::READY)
        this->status = CPUStatus::BUSY;
}


void CPU::CPURun(){
    this->halt = false;
    while(!this->halt){
        // this->CPUExecute();
        if (this->_process != nullptr ){
            // std::cout << "CPU " <<this->getID()<< " is processing"<< std::endl;

            if(this->_process->getCPUCoreID() == -1)
                this->_process->setCPUCoreID(this->getID());
            if(this->_process->getCPUCoreID() == this->getID()){
                this->_process->execute();
                if( this->_process->getState() == ProcessState::TERMINATED){
                    this->setProcess(nullptr);
                    this->status= CPUStatus::READY;
                }
                // std::cout <<"Executing.."<< std::endl;
            }

            
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << "CPU is now ready" << std::endl;
    this->status = CPUStatus::READY;
}

// void CPU::CPUExecute(){
    // this->status = CPUStatus::BUSY;
// }



