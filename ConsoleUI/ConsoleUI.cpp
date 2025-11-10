#include "./ConsoleUI.h"

ConsoleUI* ConsoleUI::ptrConsoleUI = nullptr;

ConsoleUI* ConsoleUI::getPtr() {
    return ptrConsoleUI; 
}

void ConsoleUI::initialize() {
    ptrConsoleUI = new ConsoleUI();
}
void ConsoleUI::destroy() {
    ptrConsoleUI = nullptr;
}

ConsoleUI::ConsoleUI(){
    this->_mainMenuConsole = std::make_shared<MainMenuUI>(MainMenuUI(this));
    this->_currentConsole = this->_mainMenuConsole;
}

ConsoleUI::~ConsoleUI(){
    // Destructor
}

void ConsoleUI::start() {
    this->_currentConsole->run();
}

void ConsoleUI::createNewConsole(std::string consoleName, AConsoleUI_ console){
    if(this->_ConsoleUIMap.find(consoleName) != this->_ConsoleUIMap.end()){
        std::cout << "Process already running" << std::endl;
        return;
    }
    if(this->_scheduler->findProcess(consoleName) == nullptr){
        std::cout << "Process not found, and could not be established" <<std::endl;
        return;
    }

    bool isFound = false;
    if (console == nullptr){
        
        std::vector<std::shared_ptr<Process>> tempList;
        if(this->_scheduler != nullptr)
            tempList = this->_scheduler->_processListHistory;
        else{
            std::cout << "this->_scheduler is nullptr..." << std::endl;
            return;
        }
        // Implement scheduler first.

            // std::cout << "Listning previously running processes." << std::endl;
            // std::cout << tempList.size() << std::endl;
            // for(std::shared_ptr<Process> process: tempList){
            //     std::cout << "Process Name: "<<process->getName()<< std::endl;
            //     std::cout << "Process State: "<<process->getState()<< " = " << ProcessState::TERMINATED<< std::endl;
            // }

            // std::cout << this->_scheduler->_processList.size() << std::endl;
        for(std::shared_ptr<Process> process: tempList){
            // if ( )std::cout << i->getName() << std::endl;
            std::cout <<"consoleName: " << consoleName << std::endl;
            std::cout <<"process->getName(): " << process->getName() <<std::endl;
            if(consoleName == process->getName() && (process->getState()==ProcessState::TERMINATED)) {

                // Implement ProcessUI for this to work, type its accepting is a Process
                std::cout << "Console has been found!" << std::endl;
                console = std::make_shared<ProcessUI>(process);

                
                isFound=true;
                break;
            }
        }

        if (isFound) this->_ConsoleUIMap[consoleName] = console;

        this->switchConsole(consoleName);
    }
    else {
        this->_ConsoleUIMap[consoleName] = console;
        std::cout<<"else block" << std::endl;
    }
}

void ConsoleUI::switchConsole(std::string consoleName) {
    // Check for the console's existence, or release console if marked removable.
    if(this->_ConsoleUIMap.find(consoleName) == this->_ConsoleUIMap.end()){
        std::cout << "Process " << consoleName << " is not found" << std::endl;
        return;
    }
    else if (this->_ConsoleUIMap[consoleName]->removable()){
        this->_ConsoleUIMap.erase(consoleName);
        std::cout << "Process " << consoleName << " is not found and is removable" << std::endl;
        return;
    }


    // Actual entrance part
    this->_currentConsole->stop();   
    this->_currentConsole = this->_ConsoleUIMap[consoleName];
    this->_currentConsole->run();   


    while(this->_currentConsole->isActive()){
    }

    if(this->_currentConsole->removable())
        this->_ConsoleUIMap.erase(consoleName);

    this->_currentConsole = this->_mainMenuConsole;
    this->_currentConsole->run();   

}
void ConsoleUI::setScheduler(Scheduler* scheduler) {
     _scheduler = scheduler;
} 