#include "Screen.h"

BaseScreen::BaseScreen(std::shared_ptr<Process> process, std::string processName){
    this->attachedProcess = process;
}

void BaseScreen::process(){
    if(this->refreshed == false){
        this->refreshed = true;
        this->printProcessInfo();
    }
}

void BaseScreen::printProcessInfo() const {
    std::cout<<("Test");
}