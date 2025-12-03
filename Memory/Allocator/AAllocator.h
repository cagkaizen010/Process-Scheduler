// #pragma once
#ifndef AALLOCATOR_H
#define AALLOCATOR_H

#include "../../Process/Process.h"

#include <memory>
#include <chrono>
#include <thread>

enum AllocatorType{
    Flat, Paging
};

class AAllocator {
    public:
        // AAllocator(AllocatorType);
        // ~AAllocator() = default;

        virtual bool allocate(std::shared_ptr<Process> process) = 0;
        virtual void deallocate(std::shared_ptr<Process> process) = 0;
        virtual void printMem() = 0;
        virtual void printProcesses() = 0;
        virtual void vmstat() = 0;
    private:
    AllocatorType allocatorType;
};

#endif