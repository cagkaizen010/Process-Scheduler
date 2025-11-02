#ifndef PROCESS_UI_H
#define PROCESS_UI_H

#include "../AConsoleUI/AConsoleUI.h"
#include "../../Process/Process.h"

class ProcessUI : public AConsoleUI {
    public:

        ProcessUI(std::shared_ptr<Process>);
        ~ProcessUI() = default;
        void run() override ;
        void stop() override ;
    private:
        void display() override;
        std::string _pastDisplays;

        std::shared_ptr<Process> _process;

};

#endif