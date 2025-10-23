#include <cstdio>
#include <iostream>


class Process {
    public:
        enum ProcessState{
            RUNNING,
            WAITING,
            READY,
            TERMINATED,
            NEW
        };
        Process(ProcessState);

        void updateState();
        ProcessState getState();

    private:
        ProcessState state;
};