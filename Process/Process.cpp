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
}

int Process::getID(){
    return this->pcb.pid;
}

void Process::setID(int pid){
    this->pcb.pid = pid;
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
    for( std::shared_ptr<Instruction> i : text){
        // i->execute();
        std::cout << i->getInstructionType() << std::endl;
    }
}
