#ifndef ACONSOLEUI_H
#define ACONSOLEUI_H

#include <iostream>
#include <cstdio>
#include <atomic>

// #include "../CPU/Scheduler.h"

class AConsoleUI {
    public:
        AConsoleUI();
        ~AConsoleUI() = default;
        virtual void run();
        virtual void stop();
    private:
        virtual void display();
        
};

#endif