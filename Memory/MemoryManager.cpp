#include "./MemoryManager.h"

MemoryManager::MemoryManager(int maxMem, int minPages, int maxPages, int memPerFrame) {

    if (minPages == 1 && maxPages ==1){
        std::cout<< "Using Flat Allocator" << std::endl;
        this->_allocator = new FlatAllocator(maxMem);
    }
    else {
        std::cout<< "Using Paging Allocator" << std::endl;
        Process::setRequiredPages(minPages, maxPages);
        this->_allocator = new PagingAllocator(maxMem, memPerFrame);
    }
}

bool MemoryManager::allocate(std::shared_ptr<Process> process){
    return this->_allocator->allocate(process);
}

void MemoryManager::deallocate(std::shared_ptr<Process> process){
    this->_allocator->deallocate(process);
}