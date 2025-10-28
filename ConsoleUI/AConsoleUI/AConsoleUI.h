#ifndef ACONSOLEUI_H
#define ACONSOLEUI_H

#include <iostream>
#include <cstdio>
#include <atomic>

// #include "../CPU/Scheduler.h"

class AConsoleUI {
    public:
        AConsoleUI(std::string );
        ~AConsoleUI() = default;
        virtual void run();
        virtual void stop();
    protected:
        virtual void display();

        std::string _name;
        
};

#endif