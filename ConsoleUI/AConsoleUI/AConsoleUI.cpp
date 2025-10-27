#include "AConsoleUI.h"
#include "../Threads/Threads.h"
// #include "./CPU/Scheduler.h"


AConsoleUI::AConsoleUI(){
    // std::cout<< "ConsoleUI Object created." << std::endl;
}

void AConsoleUI::run(){
    std::cout <<"Inside AConsoleUI" << std::endl;
    printf("yes");


}

void AConsoleUI::stop(){

}

void AConsoleUI::display(){
	printf("Display inside ConsoleUI");
}