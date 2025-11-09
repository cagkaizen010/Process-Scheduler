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
    // if((this->_process != nullptr) && process == nullptr){
    //     this->_process->setCPUCoreID(-1);
    // }

    this->_process = process;

    if((process != nullptr)  ) 
        process->setCPUCoreID(this->_id);


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
    static int lastCycle = 0;
    while(!this->halt){
        // this->CPUExecute();
        // if((fmod(Clock::getCycle(), 1+this->delayTime ) == float(0)) || (this->delayTime == 0)){
            // std::cout << Clock::getCycle() << std::endl;

        int currentCycle = Clock::getCycle();
        if(currentCycle > lastCycle){
            // std::unique_lock<std::mutex> lock(Clock::clockMutex);
            if((Clock::getCycle() % (1 + static_cast<int>(this->delayTime)))== 0 || (this->delayTime == 0)){

                // std::cout <<"random string" << std::endl;
                // std::unique_lock<std::mutex> lock(Clock::clockMutex);
                if (this->_process != nullptr ){

                    // If the process hasn't been assigned a CPU,
                    // assign the current process to the current CPU
                    // if(this->_process->getCPUCoreID() == -1){
                        // this->status = CPUStatus::BUSY;
                    //     this->_process->setCPUCoreID(this->getID());
                    // }


                    // if ((this->_process != nullptr) && !(this->_process->isEmpty())) {
                        // std::cout << "[Cycle " << Clock::getCycle()
                        // << "] CPU #" << this->getID()
                        // << " executing instruction #" << this->_process->getProgramCounter()
                        // << " of process " << this->_process->getName() << std::endl;
                    // }

                    // // If the process has an assigned CPU,
                    // // execute the instruction
                    // if( ((this->_process->getCPUCoreID() == this->getID()) && !(this->_process->isEmpty())) 
                    // && (!((Clock::getCycle() % this->_process->getQuantumCycles())==0) )
                    // ){
                        // std::cout << "EXECUTING [Cycle " << currentCycle << " @ CPU #" << this->getID()<<"]: "
                        // << "this->_process->getName() "+ this->_process->getName() << std::endl;
                        // this->_process->execute();
// 
                    // }

                    if(this->_process->getSchedulingType() == "rr"){
                        // if(this->_process != nullptr)
                        if(!((Clock::getCycle() % ( this->_process->getQuantumCycles() ))==0)){
                            if (((this->_process->getCPUCoreID() == this->getID()) && !(this->_process->isEmpty()))){
                                std::cout << "EXECUTING [Cycle " << currentCycle << " @ CPU #" << this->getID()<<"]: "
                                << "this->_process->getName() "+ this->_process->getName() 
                                << " this->_process->getProgramCounter() " << this->_process->getProgramCounter() <<std::endl;

                                if(this->_process != nullptr ) this->_process->execute();
                            }
                        }
                        else{
                            std::cout << "Process inside during quantum cycle: " << this->_process->getName() <<std::endl; 
                        }
                    }
                    else {
                        if (((this->_process->getCPUCoreID() == this->getID()) && !(this->_process->isEmpty()))){
                            std::cout << "EXECUTING [Cycle " << currentCycle << " @ CPU #" << this->getID()<<"]: "
                            << " this->_process->getName() "+ this->_process->getName() << std::endl;
                            this->_process->execute();
                        }

                    }
                    


                    // If process is finished,
                    // setProcess to null, and set the CPU to READY
                    if( this->_process->getState() == ProcessState::TERMINATED){
                        std::cout << "TERMINATED [Cycle " << currentCycle << " @ CPU #" << this->getID()<<"]: "
                        << "this->_process->getName() "+ this->_process->getName() << std::endl;
                        this->setProcess(nullptr);
                        this->status= CPUStatus::READY;
                    }
                    else if (this->_process->isEmpty()){
                        std::cout << "TERMINATED [Cycle " << currentCycle << " @ CPU #" << this->getID()<<"]: "
                        << "this->_process->getName() "+ this->_process->getName() << std::endl;
                        this->_process->setState(ProcessState::TERMINATED);
                        this->setProcess(nullptr);
                        this->status= CPUStatus::READY;
                    }
                }

                // if((this->_process == nullptr) )
                //     std::cout << "[Cycle " << Clock::getCycle()<< "] Empty" << std::endl;
                //     std::cout << "INSIDE Clock::getCycle(): " << Clock::getCycle() << std::endl;

                // // VERIFICATION FOR DELAY PER EXEC
                // std::cout << "[Cycle " << Clock::getCycle()<< "] Empty" << std::endl;
                // std::cout << "Conditional: "<< (Clock::getCycle() % (1 + static_cast<int>(this->delayTime)))<< std::endl;
                // std::cout << "Denominator: "<<1 + static_cast<int>(this->delayTime) << std::endl;

            }
            // if((this->_process == nullptr) )
            lastCycle = currentCycle;
            // lock.unlock();
        }
        // std::cout << "OUTSIDE Clock::getCycle(): " << Clock::getCycle() << std::endl;
        // std::unique_lock<std::mutex> lock(mtx);
        // cpuCycles = cpuCycles + 1;
        // lock.unlock();

        // CPU stops completely
    }
    std::cout << "CPU is now ready" << std::endl;
    this->status = CPUStatus::READY;
}


