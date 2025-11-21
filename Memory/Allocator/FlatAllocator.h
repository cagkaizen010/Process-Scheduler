#ifndef FLATALLOCATOR_H
#define FLATALLOCATOR_H

#include "./AAllocator.h"
#include "../../Process/Process.h"

#include <cstdio>
#include <memory> 
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>

class FlatAllocator : public AAllocator {
    public:
    FlatAllocator(int maxMemory);
    ~FlatAllocator() = default;

    bool allocate(std::shared_ptr<Process> process) override;
    void deallocate(std::shared_ptr<Process> process) override;


    private:
        typedef std::vector<std::pair<std::shared_ptr<Process>, std::pair<int,int>>> Memory;

        void readBackingStore(std::shared_ptr<Process> process);
        void writeBackingStore(std::shared_ptr<Process> process);
        int _maxMemory;
        Memory _memory;
};


#endif

