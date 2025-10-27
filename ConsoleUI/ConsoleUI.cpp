#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "../CPU/Scheduler.h"

#include <cstdio>
#include <memory>
#include <unordered_map>
#include <string>

typedef std::shared_ptr<ConsoleUI> ConsoleUI_;

class ConsoleUI {
    public:
        ConsoleUI();
        ~ConsoleUI() = default;


    private:
        static ConsoleUI* ptrConsoleUI;

        std::unordered_map<std::string, ConsoleUI_> _ConsoleUIMap;

        // Define Abstract Template of ConsoleUI object.
        ConsoleUI_ _currentConsole = nullptr;
        ConsoleUI_ _mainMenuConsole = nullptr;

        Scheduler* _scheduler = nullptr;
};

#endif
