#include "Process.h"

int Process::requiredPages = -1;
int Process::currentMemory = -1;

int Process::getRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

static std::string getRandomString(size_t length) {
    static const std::string chars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, chars.size() - 1);

    std::string result;
    result.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        result += chars[distrib(gen)];
    }

    return result;
}

Process::Process( ProcessControlBlock pcb, int memAllocation, int pageAllocation)  {
    this->pcb = pcb;

    if(Process::currentMemory== -1){
        int base2Memory = 1;
        while(base2Memory < memAllocation)
            base2Memory *=2;
        this->_requiredMemory = base2Memory;

    }
    else this->_requiredMemory = Process::currentMemory;

    if(Process::requiredPages == -1){
        int base2Pages = 1;

        while(base2Pages < pageAllocation)
            base2Pages*=2;
        Process::requiredPages = base2Pages;
    }
}

int Process::setRequiredPages( int minPage, int maxPage){
    int randomPageDistribution = getRandomInt(minPage, maxPage);

    if(Process::requiredPages == -1){
        int base2Pages = 1;

        while(base2Pages < randomPageDistribution)
            base2Pages*=2;
        Process::requiredPages = base2Pages;
    }
    else std::cout <<"Required pages already set" << std::endl;
    return Process::requiredPages;

}

int Process::setRequiredMemory(int minMem, int maxMem){
    int randomMemDistribution = getRandomInt(minMem, maxMem);


    if(Process::currentMemory== -1){
        int base2Memory = 1;
        while(base2Memory < randomMemDistribution)
            base2Memory *=2;
        Process::currentMemory= base2Memory;

    }
    else std::cout <<"Required Memory already set" << std::endl;
    return Process::currentMemory;
}

int Process::getRequiredPages(){
    return Process::requiredPages;
}

int Process::getRequiredMemory(){
    // return Process::currentMemory;
    return _requiredMemory;
}

void Process::generateInstruction(int minIns, int maxIns){

    int randomNumber;
    int numberOfInstructions= getRandomInt(minIns, maxIns);

    for (int i = 0; i < numberOfInstructions; i++){
        randomNumber = getRandomInt(1, 4);

        if(randomNumber == 1) 
            this->text.emplace_back(std::make_unique<Declare>(getRandomString(2), getRandomInt(1, 100)));
        
        if(randomNumber== 2)
            this->text.emplace_back(std::make_unique<Add>(getRandomInt(1,100), getRandomInt(1,100), getRandomInt(1, 100)));

        if(randomNumber== 3)
            this->text.emplace_back(std::make_unique<Sub>(getRandomInt(1,100),getRandomInt(1,100), getRandomInt(1, 100)));

        if(randomNumber == 4)
            this->text.emplace_back(std::make_unique<Print>(getRandomString(10)));
    }
}


void Process::listInstructions() {
    if(text.size() > 15) {
        for (int i = 0; i < 15; i++){
            std::cout << text[i]->getInstructionType() << std::endl;
        }
        std::cout <<".\n.\n.\n"<< std::endl;
    } else for( std::shared_ptr<Instruction> i : text)
        std::cout << i->getInstructionType() << std::endl;
}

void Process::execute() {
    // std::lock_guard<std::mutex> lock(processMutex);
    if(!this->isEmpty()){
 
        this->text.at(pcb.progCounter)->execute(pcb.CPUCoreID);
        this->incrementProgramCounter();
        if (this -> isEmpty()) this->pcb.pstate =TERMINATED;

    }
    else {
        std::cout << "PROCESS IS EMPTY" << std::endl;
        this->pcb.pstate =TERMINATED;
    }

}


bool Process::isEmpty(){
    // if (this->text.size() == 0) return true;
    // else return false;

    if (this->text.size() == this->pcb.progCounter )
        return true;
    else return false; 

}


std::string Process::getName(){
    return this->pcb.pname;
}
void Process::setName(std::string name){
    this->pcb.pname = name;
}

int Process::getProgramCounter(){
    return this->pcb.progCounter;
}
void Process::incrementProgramCounter(){
    this->pcb.progCounter = this->getProgramCounter()+1;
}

ProcessState Process::getState() {
    return this->pcb.pstate;
}

void Process::setState(ProcessState state) {
    this->pcb.pstate = state;
}

void Process::setCPUCoreID(int coreID){
    this->pcb.CPUCoreID = coreID;
}
int Process::getCPUCoreID(){
    return this->pcb.CPUCoreID;
}

std::string Process::getSchedulingType() {
    return this->pcb.schedulingType;
}

int Process::getQuantumCycles(){
    return this->pcb.quantumCycles;
}

int Process::getInstructionSetSize() {
    return this->text.size();
}

int Process::getID(){
    return this->pcb.pid;
}

void Process::setID(int pid){
    this->pcb.pid = pid;
}

void Process::deleteTopInstruction(){
    this->text.erase(text.begin());
}

std::shared_ptr<Instruction> Process::getInstruction() {
    return this->text.front();
}



