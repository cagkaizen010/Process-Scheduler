#ifndef PROCESS_UI_H
#define PROCESS_UI_H

#include "../AConsoleUI/AConsoleUI.h"

class ProcessUI : AConsoleUI {
    public:
        void run() override;
        void stop() override;
    private:
        void display() override;
};

#endif