#ifndef MAINMENUUI_H
#define MAINMENUUI_H


#include "../AConsoleUI/AConsoleUI.h"
// #include "../ConsoleUI.h"
#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
#include <sstream>

class ConsoleUI;
typedef const std::vector<std::string>& _Argument;

class MainMenuUI : public AConsoleUI {
    public:
        MainMenuUI(ConsoleUI* consoleUI);
        ~MainMenuUI() = default;
        void run() override;
        void stop() override;
    private:
        // void InputHandler(ConsoleUI* consoleUI);

        std::unordered_map<std::string, std::function<void(_Argument)>> _commandMap;

        void openingMessage();
        ConsoleUI* _consoleUI = nullptr;
};

#endif