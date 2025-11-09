#include "Process.h"

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

// int Process::randInt() {
//     return getRandomInt(1, 100);
// }

Process::Process( ProcessControlBlock pcb)  {
    this->pcb = pcb;
    // this->text = text;
    // this->generateInstruction();
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int Process::getID(){
    return this->pcb.pid;
}

void Process::setID(int pid){
    this->pcb.pid = pid;
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
void Process::incrementProgramCounter(int progCounter){
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

void Process::generateInstruction(int minIns, int maxIns){

    int randomNumber;
    int numberOfInstructions= getRandomInt(minIns, maxIns);
    // std::cout << "Generating instructions.." << std::endl;
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
    for( std::shared_ptr<Instruction> i : text)
        std::cout << i->getInstructionType() << std::endl;
}

void Process::deleteTopInstruction(){
    this->text.erase(text.begin());
}

std::shared_ptr<Instruction> Process::getInstruction() {
    return this->text.front();}


    // YOU ARE HERE
void Process::execute() {
    static uint64_t lastCycle = 0;
    if(!this->isEmpty()){
        // std::cout << "[Cycle " << Clock::getCycle() << "]: "
        // << "this->_process->getName() "+ this->getName() << std::endl;

        // uint64_t currentCycle = Clock::getCycle();

        // if(currentCycle > lastCycle){
            this->text.at(pcb.progCounter)->execute(pcb.CPUCoreID);
            this->pcb.progCounter++;
            if (this -> isEmpty()) this->pcb.pstate =TERMINATED;
            // lastCycle = currentCycle;
            
        // }
            // std::cout << Clock::getCycle() << std::endl;

        // std::cout << "[Cycle " << Clock::getCycle()
        //   << "] CPU#" << pcb.CPUCoreID
        //   << " executing instruction #" << pcb.progCounter
        //   << " of process " << pcb.pname << std::endl;


        // system("cls");

        // std::cout << this->pcb.pname << std::endl;
        // std::cout << std::to_string(this->pcb.progCounter) + " < " + std::to_string(this->text.size())<<std::endl;
        // std::cout << "pcb.CPUCoreID: " + std::to_string(pcb.CPUCoreID) <<std::endl; 


        // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    else {
        std::cout << "PROCESS IS EMPTY" << std::endl;
        this->pcb.pstate =TERMINATED;
    }

}