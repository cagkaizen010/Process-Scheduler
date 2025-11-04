#include "AConsoleUI.h"
#include "../Threads/Threads.h"
// #include "./CPU/Scheduler.h"


AConsoleUI::AConsoleUI(std::string name){
    // std::cout<< "ConsoleUI Object created." << std::endl;
    this->_name = name;
}

void AConsoleUI::run(){
    std::cout << "Console " << this->_name << " is now running" << std::endl; 

    this->_active=true;
    // this->stop();
}

void AConsoleUI::stop(){
    if(this->isActive())
        this->_active = false;
}

void AConsoleUI::display(){
	printf("Display inside ConsoleUI");
}