#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <iostream>
#include <cstdio>
#include <atomic>

// #include "../CPU/Scheduler.h"

class ConsoleUI {
    public:
        ConsoleUI();
        void run();
    private:
        
        bool initialized;
        
};

#endif