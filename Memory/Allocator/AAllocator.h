#ifndef AALLOCATOR_H
#define AALLOCATOR_H

#include "../../Process/Process.h"
#include <memory>

class AAllocator {
    public:
        virtual bool allocate(std::shared_ptr<Process> process) = 0;
        virtual void deallocate(std::shared_ptr<Process> process) = 0;
        virtual void printMem() = 0;
        virtual void printProcesses() = 0;
        virtual void vmstat() = 0;
};

#endif