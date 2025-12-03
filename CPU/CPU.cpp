#include "CPU.h"
int CPU::dynamicID = 0;


CPU::CPU() {
    if (CPU::dynamicID < 4){
        // std::cout << "CPU::dynamicID: " + std::to_string(CPU::dynamicID) << std::endl;

        this->_id=CPU::dynamicID;
        CPU::dynamicID++;
    }
    std::thread tickThread(&CPU::CPURun, this);
    tickThread.detach();
}

void CPU::setProcess(std::shared_ptr<Process> process){
    std::lock_guard<std::mutex> lock(cpuMutex);

    if((process != nullptr )  ) {
        if (process->getCPUCoreID() == -1)
            process->setCPUCoreID(this->_id);

        if (process->getCPUCoreID() == this->_id)
            this->_process = process;
    }
    else {
        this->_process= process;
    }
    
    

    this->status = (process == nullptr) ? CPU::READY : CPU::BUSY;
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

        // Safety to prevent more than one execution on a clock cycle
        int currentCycle = Clock::getCycle();
        if(currentCycle > lastCycle){

            // Check if CPU is on a delay cycle
            if((Clock::getCycle() % (1 + static_cast<int>(this->delayTime)))== 0 || (this->delayTime == 0)){

                // First check to see if assigned process is null
                if (this->_process != nullptr ){

                    // Check to see if current Scheduler is in round-robin mode
                    // else do FCFS mode and execute the current cycle
                    if(this->_process->getSchedulingType() == "rr"){

                        // Check if current cycle is on a quantum cycle
                        // If it is, do nothing.
                        // if not, call execute on current process
                        if(!((Clock::getCycle() % ( this->_process->getQuantumCycles() ))==0)){
                            if (((this->_process->getCPUCoreID() == this->getID()) && !(this->_process->isEmpty()))){

                                if(this->_process != nullptr ) {
                                    this->_process->execute();
                                }
                            }
                        }
                        else{
                            lastCycle = currentCycle;
                            continue;
                            // std::cout << "Process inside during quantum cycle: " << this->_process->getName() <<std::endl; 
                        }
                    }
                    else {
                        if (((this->_process->getCPUCoreID() == this->getID()) && !(this->_process->isEmpty()))){

                            this->_process->execute();
                        }

                    }

                    // If process is finished,
                    // setProcess to null, and set the CPU to READY
                    // if(this->_process != nullptr){
                    //     // std::cout << "CPU " << this->_id << " RUNNING" << std::endl;
                    //     if( this->_process->getState() == ProcessState::TERMINATED){

                    //         this->setProcess(nullptr);
                    //         this->status= CPUStatus::READY;
                    //     }
                    //     else if (this->_process->isEmpty()){

                    //         this->_process->setState(ProcessState::TERMINATED);
                    //         this->setProcess(nullptr);
                    //         this->status= CPUStatus::READY;
                    //     }
                    // }

                }
            }
            // if((this->_process == nullptr) )
            std::unique_lock<std::mutex> lock(Clock::clockMutex);
            lastCycle = currentCycle;
            lock.unlock();
        }
        // CPU stops completely
    }
    std::cout << "CPU is now ready" << std::endl;
    this->status = CPUStatus::READY;
}


