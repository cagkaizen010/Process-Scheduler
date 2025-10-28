#include "./ConsoleUI.h"

ConsoleUI* ConsoleUI::ptrConsoleUI = nullptr;

ConsoleUI* ConsoleUI::getPtr() {
    return ConsoleUI::ptrConsoleUI; 
}

void ConsoleUI::initialize() {
    ptrConsoleUI = new ConsoleUI();
}

ConsoleUI::ConsoleUI(){
    this->_mainMenuConsole = std::make_shared<MainMenuUI>(MainMenuUI(this));
    this->_currentConsole = this->_mainMenuConsole;
}

ConsoleUI::~ConsoleUI(){
    // Destructor
}