#include "./MemoryManager.h"


AAllocator* MemoryManager::getAllocator() {
    return this->_allocator;
}

MemoryManager::MemoryManager(int maxMem, int minPages, int maxPages) {
    if (minPages == 1 && maxPages ==1)
        this->_allocator = new FlatAllocator(maxMem);
    else {
        Process::setRequiredPages(minPages, maxPages);
        this->_allocator = new PagingAllocator(maxMem);
    }
}

bool MemoryManager::allocate(std::shared_ptr<Process> process){
    return this->_allocator->allocate(process);
}

void MemoryManager::deallocate(std::shared_ptr<Process> process){
    this->_allocator->deallocate(process);
}