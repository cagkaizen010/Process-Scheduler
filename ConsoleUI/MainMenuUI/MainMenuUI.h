#ifndef MAINMENUUI_H
#define MAINMENUUI_H


#include "../AConsoleUI/AConsoleUI.h"
#include "../ConsoleUI.h"
#include "../../Config/config.h"
#include "../../Process/Process.h"
#include "../../Process/Instruction/Declare.h"
#include "../../CPU/CPU.h"
#include "../../Clock/Clock.h"
#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <thread>
#include <chrono>
// #include <iostream>

class ConsoleUI;
typedef const std::vector<std::string>& _Argument;

class MainMenuUI : public AConsoleUI {
    public:
        MainMenuUI(ConsoleUI* consoleUI);
        ~MainMenuUI() = default;
        void run() override;
        void stop() override;
    private:
        void display() override ;
        // void InputHandler(ConsoleUI* consoleUI);

        std::unordered_map<std::string, std::function<void(_Argument)>> _commandMap;


        bool _initialized = false;
        void openingMessage();
        ConsoleUI* _consoleUI = nullptr;
};

#endif