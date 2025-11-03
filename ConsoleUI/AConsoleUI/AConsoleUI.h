#ifndef ACONSOLEUI_H
#define ACONSOLEUI_H

#include <iostream>
#include <cstdio>
#include <thread>
#include <chrono>
#include <atomic>

// #include "../CPU/Scheduler.h"

class AConsoleUI {
    public:
        AConsoleUI(std::string );
        ~AConsoleUI() = default;

        virtual void run() =0;
        virtual void stop() = 0;

        bool isActive(){
            return this->_active;
        }
        bool removable(){
            return this->_removable;
        }
    protected:
        virtual void display() ;

        std::string _name;

        bool _active = false;
        bool _removable = false;
        
};

#endif