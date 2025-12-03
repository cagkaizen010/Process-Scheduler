#include "PagingAllocator.h"

PagingAllocator::PagingAllocator(int memMax, int memPerFrame){
    std::ofstream file("csopesy-backing-store.txt", std::ios::trunc);
    file.close();
    this->_memPerFrame = memPerFrame;
    int requiredMem = memPerFrame;

    this->_maxMemory = memMax;



    
    for (int i = 0; i < memMax/((float)requiredMem/(float)Process::getRequiredPages()); i++)
        _freeFrameQueue.push(i);
    
}

bool PagingAllocator::allocate(std::shared_ptr<Process> process){
    int requiredMem = this->_memPerFrame;

    int requiredPages = Process::getRequiredPages();
    int pageSize = requiredMem/requiredPages;
    if (_pageTable.find(process->getName()) != _pageTable.end()){
        for(int i = 0; i < _pageTable[process->getName()].size(); i++)
            if (_pageTable[process->getName()].at(i) < 0){
                int nextFrame = _freeFrameQueue.front();
                _freeFrameQueue.pop();
                _pageTable[process->getName()].at(i) = nextFrame;
            }
        
        return true;
    }

    if (_freeFrameQueue.size() >= requiredPages){
        for(int i = 0; i < requiredPages; i++){
            int next= _freeFrameQueue.front();
            _freeFrameQueue.pop();
            _pageTable[process->getName()].push_back(next);
            _pagesIn++;
        }
        return true;
    }
    return false;
}


void PagingAllocator::deallocate(std::shared_ptr<Process> process){
    if (_pageTable.find(process->getName()) != _pageTable.end()){
        for (int i = 0; i < _pageTable[process->getName()].size(); i++){
            _freeFrameQueue.push(_pageTable[process->getName()].at(i));
            _pagesOut++;
        }
        _pageTable.erase(_pageTable.find(process->getName()));
    }
}

void PagingAllocator::printMem() {
    std::cout <<"Needs implemented" << std::endl;
}
void PagingAllocator::printProcesses() {
    std::vector<std::string> processNameListOutputStrings;
    int reqMem = this->_memPerFrame;
    int reqPages = Process::getRequiredPages();
    int pageSize = reqMem/reqPages;


    int total;



    std::cout << "-------------" << std::endl;

    std::cout << "this->_pageTable.size(): " << this->_pageTable.size() << std::endl;
    std::cout << "reqMem: " << reqMem << std::endl;
    std::cout << "Memory Usage: " << this->_pageTable.size() * reqMem << " / " << this->_maxMemory<< std::endl;
    std::cout << "Memory Util: " << ((float)(this->_pageTable.size() * reqMem) / (this->_maxMemory))/ this->_maxMemory * 100 << "%" << std::endl;
    
    std::cout << "Processes and memory usage" <<std::endl;

    for(std::string out : processNameListOutputStrings)
        std::cout << out << std::endl;



}
void PagingAllocator::vmstat() {
    int reqMem = this->_memPerFrame;
    int requiredPages = Process::getRequiredPages();
    int pageSize = reqMem/requiredPages;

    int activeMemory = 0;


    if (_pageTable.size() >0) {
        int top = _maxMemory;
        int bot = 0;

        for (auto page  = _pageTable.begin(); page != _pageTable.end(); page++){
            std::string procName = page->first;

                for (int i = 0; i < page->second.size(); i++){
                    if (page->second.at(i) != -1){
                        if(page->second[i] * pageSize < top)
                            top = page->second[i] * pageSize;
                        if((page->second[i] + 1) * pageSize > bot )
                            bot = (page->second[i] + 1) * pageSize;
                        activeMemory += pageSize;
                    }
                }
        }

    }

    std::cout << _maxMemory * 1024 << " bytes " << "total memory" << std::endl;
    std::cout <<  activeMemory* 1024 << " bytes " << "used memory" << std::endl;
    std::cout << (_maxMemory-activeMemory) *1024 << " bytes " << "free memory" << std::endl;


}