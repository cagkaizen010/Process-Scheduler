#include "./ConsoleUI.h"

ConsoleUI* ConsoleUI::ptrConsoleUI = nullptr;

ConsoleUI* ConsoleUI::getPtr() {
    return ConsoleUI::ptrConsoleUI; 
}

void ConsoleUI::initialize() {
    ptrConsoleUI = new ConsoleUI();
}

ConsoleUI::ConsoleUI(){
    MainMenuUI temp(this);
    this->_mainMenuConsole = std::make_shared<MainMenuUI>(temp);
    this->_currentConsole = this->_mainMenuConsole;
}

ConsoleUI::~ConsoleUI(){
    // Destructor
}