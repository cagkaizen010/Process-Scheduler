#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "../CPU/Scheduler.h"
#include "./MainMenuUI/MainMenuUI.h"
#include "./AConsoleUI/AConsoleUI.h"

#include <cstdio>
#include <memory>
#include <unordered_map>
#include <string>

typedef std::shared_ptr<AConsoleUI> AConsoleUI_;

class ConsoleUI {
    public:
        static ConsoleUI* getPtr();
        static void initialize();
        static void destroy();

        ConsoleUI();
        ~ConsoleUI() ;

        void start();


    private:
        static ConsoleUI* ptrConsoleUI;

        std::unordered_map<std::string, AConsoleUI_> _ConsoleUIMap;

        // Define Abstract Template of ConsoleUI object.
        AConsoleUI_ _currentConsole = nullptr;
        AConsoleUI_ _mainMenuConsole = nullptr;

        Scheduler* _scheduler = nullptr;
        friend class MainMenuUI;
};

#endif
