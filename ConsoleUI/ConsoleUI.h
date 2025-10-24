#include <iostream>
#include <cstdio>

#include "../CPU/Scheduler.h"

class ConsoleUI {
    public:
        ConsoleUI();
        void run();
    private:
        Scheduler s;
};