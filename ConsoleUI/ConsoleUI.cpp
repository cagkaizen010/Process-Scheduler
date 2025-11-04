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

    bool isFound = false;
    if (console == nullptr){
         
        std::vector<std::shared_ptr<Process>> tempList = this->_scheduler->_processList;
        // Implement scheduler first.

        for(std::shared_ptr<Process> i : tempList){
            if(consoleName == i->getName() && !(i->getState()==ProcessState::TERMINATED)) {

                // Implement ProcessUI for this to work, type its accepting is a Process

                console = std::make_shared<ProcessUI>(i);

                
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
        // std::cout << consoleName << " is RUNNING" <<  std::endl;
    }
    // std::cout << "break";
    // std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    if(this->_currentConsole->removable())
        this->_ConsoleUIMap.erase(consoleName);

    this->_currentConsole = this->_mainMenuConsole;
    this->_currentConsole->run();   

}
void ConsoleUI::setScheduler(Scheduler* scheduler) {
     _scheduler = scheduler;
} 