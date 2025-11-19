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
        std::cout << "Console for process already running" << std::endl;
        return;
    }
    if(this->_scheduler->findProcess(consoleName) == nullptr){
        std::cout << "Process not found, and could not be established" <<std::endl;
        return;
    }

    bool isFound = false;
    if (console == nullptr){
        
        std::vector<std::shared_ptr<Process>> tempList;
        if(this->_scheduler != nullptr){
            tempList = this->_scheduler->_processListHistory;              // _processList

        }

        else{
            std::cout << "this->_scheduler is nullptr..." << std::endl;
            return;
        }
        // Implement scheduler first.

        // First see if the process exists
        for(std::shared_ptr<Process> process: tempList){
            if(consoleName == process->getName() ) {

                console = std::make_shared<ProcessUI>(process);
                
                isFound=true;
                break;
            }
        }

        if (isFound){
            
            this->_ConsoleUIMap[consoleName] = console;
            this->switchConsole(consoleName);
        }
        else {
            std::cout << "Process cannot be found or has finished, cannot initialize screen for process..." << std::endl;
            return;
        }

    }
    
}

void ConsoleUI::switchConsole(std::string consoleName) {
    // Check for the console's existence, or release console if marked removable.
    
    if((this->_ConsoleUIMap.find(consoleName) == this->_ConsoleUIMap.end()) ){ // && (this->_ConsoleUIMap[consoleName] == nullptr)){
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