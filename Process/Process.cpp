#include "Process.h"

static int getRandomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
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

Process::Process( ProcessControlBlock pcb, InstructionSet text)  {
    this->pcb = pcb;
    this->text = text;
    this->generateInstruction();
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

    if (this->text.size() <= this->pcb.progCounter )
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

int Process::getInstructionSetSize() {
    return this->text.size();
}

void Process::generateInstruction(){

    int randomNumber;

    for (int i = 0; i < 10; i++){
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

void Process::execute() {
    if(!this->isEmpty()){
        this->text.at(pcb.progCounter)->execute(pcb.CPUCoreID);
        this->pcb.progCounter++;
    }
}