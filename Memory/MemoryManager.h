#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include "./Allocator/AAllocator.h"
#include "./Allocator/FlatAllocator.h"
#include "./Allocator/PagingAllocator.h"


class MemoryManager{
    public:
        MemoryManager(int, int, int);
        ~MemoryManager() = default;

        bool allocate(std::shared_ptr<Process> process);
        void deallocate(std::shared_ptr<Process> process);

        // void printMem();

        AAllocator* getAllocator() {
            return this->_allocator;
        };


    private:
        AAllocator* _allocator;
};

#endif