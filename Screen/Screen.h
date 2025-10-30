#ifndef SCREEN_H
#define SCREEN_H

#include <cstdio>
#include <iostream>
#include <string>
#include <memory>
#include "../Process/Process.h"

class BaseScreen{
    public:
        BaseScreen(std::shared_ptr<Process>, std::string processName);
        void process();
        void onEnabled();
        void display();
    private:
        void printProcessInfo() const;
        std::shared_ptr<Process> attachedProcess;
        bool refreshed = false;
};

#endif 