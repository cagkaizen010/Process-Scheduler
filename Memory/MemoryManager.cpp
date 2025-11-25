#include "./MemoryManager.h"


// AAllocator* MemoryManager::getAllocator() {
//     return this->_allocator;
// }

MemoryManager::MemoryManager(int maxMem, int minPages, int maxPages) {
    std::cout<< "maxMem: " << maxMem << std::endl;
    std::cout<< "minPages: " << minPages << std::endl;
    std::cout<< "maxPages: " << maxPages << std::endl;

    if (minPages == 1 && maxPages ==1){
        std::cout<< "Using Flat Allocator" << std::endl;

        this->_allocator = new FlatAllocator(maxMem);
    }
    else {
        std::cout<< "Using Paging Allocator" << std::endl;
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