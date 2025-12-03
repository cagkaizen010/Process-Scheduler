#ifndef PAGINGALLOCATOR_H
#define PAGINGALLOCATOR_H

#include "./AAllocator.h"
#include "../../Process/Process.h"
#include <cstdio>
#include <cstdlib>
// #include <chrono>
// #include <thread>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <queue>

class AAllocator;
class PagingAllocator : public AAllocator{
    public:
        PagingAllocator(int, int);
        ~PagingAllocator() = default;

        bool allocate(std::shared_ptr<Process> ) override;
        void deallocate(std::shared_ptr<Process> ) override;
        void printMem() override;
        void printProcesses() override;
        void vmstat() override;
    private:
        int _maxMemory;
        int _memPerFrame;
        std::queue<int> _freeFrameQueue;
        std::unordered_map<std::string, std::vector<int>> _pageTable;
        int _pagesIn = 0;
        int _pagesOut = 0;
};
#endif