#include "AConsoleUI.h"
#include "../Threads/Threads.h"
// #include "./CPU/Scheduler.h"


AConsoleUI::AConsoleUI(std::string name){
    // std::cout<< "ConsoleUI Object created." << std::endl;
}

void AConsoleUI::run(){
    this->_active=true;


}

void AConsoleUI::stop(){
    if(this->isActive())
        this->_active = false;
}

void AConsoleUI::display(){
	printf("Display inside ConsoleUI");
}