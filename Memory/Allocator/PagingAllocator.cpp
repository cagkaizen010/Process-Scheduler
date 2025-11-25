#include "PagingAllocator.h"

PagingAllocator::PagingAllocator(int memMax){
    std::ofstream file("csopesy-backing-store.txt", std::ios::trunc);
    file.close();
    int requiredMem = Process::setRequiredMemory(-1, 1);


    std::cout << memMax << std::endl;
    // std::cout << requiredMem << std::endl;
    std::cout << requiredMem << std::endl;
    std::cout << Process::getRequiredPages()<< std::endl;

    // std::cout << Process::getRequiredPages()<< std::endl;
    // std::cout << "Division: "<< ((float)requiredMem/(float)Process::getRequiredPages()) << std::endl;


    for (int i = 0; i < memMax/((float)requiredMem/(float)Process::getRequiredPages()); i++)
        _freeFrameQueue.push(i);
    
}

bool PagingAllocator::allocate(std::shared_ptr<Process> process){
    int requiredMem = Process::setRequiredMemory(0,0);
    //  Process::getRequiredMemory();
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
    int reqMem = Process::setRequiredMemory(0,0);


    int total;

    // for (std::pair<std::shared_ptr<Process>, std::pair<int,int>> key : this->_memory){
    //     processNameListOutputStrings.push_back(key.first->getName() + 
    //         " " + std::to_string(key.second.second- key.second.first));

    //     total += key.second.second - key.second.first;
    //     std::cout << key.first->getName();
    // }


    std::cout << "-------------" << std::endl;
    std::cout << "Memory Usage: " << total << " / " << this->_maxMemory*1024<< std::endl;
    std::cout << "Memory Util: " << ((float)total / (this->_maxMemory*1024)) * 100 << "%" << std::endl;
    
    std::cout << "Processes and memory usage" <<std::endl;

    for(std::string out : processNameListOutputStrings)
        std::cout << out << std::endl;



}
void PagingAllocator::vmstat() {
    std::cout <<"Needs implemented" << std::endl;

}