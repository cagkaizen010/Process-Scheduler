#ifndef MAINMENUUI_H
#define MAINMENUUI_H
#include "../AConsoleUI/AConsoleUI.h"
#include "../ConsoleUI.h"

class MainMenuUI : AConsoleUI {
    public:
        MainMenuUI(ConsoleUI* consoleUI );
        ~MainMenuUI() = default;
        void run() override;
        void stop() override;
    private:
        ConsoleUI* _consoleUI = nullptr;
};

#endif