#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "../Scheduler/Scheduler.h"
#include "./MainMenuUI/MainMenuUI.h"
#include "./AConsoleUI/AConsoleUI.h"
#include "./ProcessUI/ProcessUI.h"

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
        void createNewConsole(std::string consoleName, AConsoleUI_ console = nullptr);
        void switchConsole(std::string consoleName);


        void setScheduler(Scheduler* );  
    private:
        static ConsoleUI* ptrConsoleUI;

        // Current running consoles?
        std::unordered_map<std::string, AConsoleUI_> _ConsoleUIMap;

        // Define Abstract Template of ConsoleUI object.
        AConsoleUI_ _currentConsole = nullptr;
        AConsoleUI_ _mainMenuConsole = nullptr;

        Scheduler* _scheduler = nullptr;
        friend class MainMenuUI;
};

#endif
