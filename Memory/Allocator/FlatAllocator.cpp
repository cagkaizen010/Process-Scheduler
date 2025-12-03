#include "FlatAllocator.h"


FlatAllocator::FlatAllocator(int maxMemory) : _maxMemory(maxMemory){

    // Load backing store file
    std::ofstream file("csopesy-backing-store.txt", std::ios::trunc);
    file.close();
}

bool FlatAllocator::allocate(std::shared_ptr<Process> process){
    // std::cout << "Allocating " << process->getName() << std::endl;
    int reqMem = process->getRequiredMemory();
    this->readBackingStore(process);
    if (this->_memory.size() == 0){
        //                                      process      start address -> end address 
        this->_memory.push_back(std::make_pair(process, std::make_pair(0, reqMem)));

        std::cout << "Allocation success. Empty flat memory, pushed in "<< process->getName() <<std::endl;
        return true;
    }
    else {
        // std::cout << "_memory.size(): " << _memory.size() << std::endl;
        for (std::pair<std::shared_ptr<Process>, std::pair<int, int>> mem : _memory){
            // std::cout << "Process key: " << mem.first->getName()<<std::endl;
            // std::cout << "Process value, first: " << mem.second.first <<std::endl;
            // std::cout << "Process value, second: " << mem.second.second <<std::endl;
            if(mem.first->getName() == process->getName()){
                std::cout << process->getName() << " found in memory." << std::endl;
                return true;
            }
        }

        // If the first memory instance in the vector >= required memory of the new process,
        // Rewrite into that region with the new process
        // std::cout << "this->_memory.at(0).second.first: " << this->_memory.at(0).second.first << std::endl;
        // std::cout << "reqMem: " << reqMem << std::endl;
        if (this->_memory.at(0).second.first >= reqMem){
            this->_memory.insert(this->_memory.begin(), std::make_pair(process, std::make_pair(0, reqMem)));


            std::cout << "Allocation Success. Rewriting into beginning of memory." << std::endl;
            return true;
        }

        for(int retryLimit = 0; retryLimit < 5; retryLimit++){
            int counter= 0;
            // std::cout << "this->_memory.size(): " << this->_memory.size() << std::endl;
            for (int i = 0; i < this->_memory.size(); i++ ){

                if (i == this->_memory.size()-1)
                    counter = this->_maxMemory - this->_memory.at(i).second.second;
                else counter = this->_memory.at(i+1).second.first - this->_memory.at(i).second.second;

                if (counter >= reqMem){
                    this->_memory.insert(this->_memory.begin() +i +1, 
                        std::make_pair(process, 
                                std::make_pair(this->_memory.at(i).second.second, 
                                    this->_memory.at(i).second.second + reqMem)));

                    // std::cout << "Allocation success. Inserting into Address: " << i+1 << std::endl;
                    return true;
                }
            }
            if (this->_memory.size() > 0){
                int i = rand() % this->_memory.size();

                    // std::cout << "Writing into backing store.." << std::endl;
                    this->writeBackingStore(this->_memory.at(i).first);
                    this->_memory.erase(this->_memory.begin() + i);
                // }
            }
        }
    }
    // std::cout << "Unable to allocate " << process->getName() << " currently assigned to CPU # " << process->getCPUCoreID()  <<std::endl;
    return false;
}

void FlatAllocator::deallocate(std::shared_ptr<Process> process){
    this->readBackingStore(process);

    for (int i = 0; i < this->_memory.size(); i++)
        if (this->_memory.at(i).first->getName() == process->getName())
        {
            // std::cout << "Deallocating " << process->getName() << std::endl;
            this->_memory.erase(this->_memory.begin() +1);
        }
}

// Parsing backing store file
void FlatAllocator::readBackingStore(std::shared_ptr<Process> process) {
    std::ifstream file("csopesy-backing-store.txt");

    if(!file.is_open()){
        std::cerr << "Backing store file could not be loaded." << std::endl;
        return;
    }

    std::unordered_map<std::string, std::pair<int, int>> backingStore;
    std::string line, key, counter, mem;

    while(std::getline(file, line)){
        std::istringstream iss(line);
        iss >>key >>counter >>mem;
        // std::cout << "Inside backing store: " << key <<counter << mem << std::endl;
        backingStore[key] = std::make_pair(std::stoi(counter), std::stoi(mem));
    }
    file.close();

    if (backingStore.find(process->getName()) != backingStore.end())
        backingStore.erase(backingStore.find(process->getName()));
    std::ofstream save("csopesy-backing-store.txt", std::ios::trunc);
    
    if(save.is_open()) {
        for(const auto& out : backingStore)
            save << out.first << ' ' << out.second.first << ' ' << out.second.second << '\n';
        save.close();
    }
}

void FlatAllocator::writeBackingStore(std::shared_ptr<Process> process){
    std::ifstream file("csopesy-backing-store.txt");

    if (!file.is_open()){
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }
    std::unordered_map<std::string, std::pair<int, int>> backingStore;
    std::string line, key, counter, mem;

    while(std::getline(file, line)){
        std::istringstream iss(line);
        iss >>key >>counter >> mem;
        backingStore[key] = std::make_pair(std::stoi(counter), std::stoi(mem));
    }
    file.close();

    if(backingStore.find(process->getName()) == backingStore.end()) {
        backingStore[process->getName()] = std::make_pair(process->getProgramCounter(),
            process->getRequiredMemory());
        std::ofstream save("csopesy-backing-store.txt", std::ios::trunc);

        if (save.is_open()){
            for (const auto& out : backingStore)
                save <<out.first << ' ' << out.second.first<< ' ' << out.second.second << '\n';
            save.close();
        }
    }
}

void FlatAllocator::printMem() {
    std::cout <<"Needs implemented" << std::endl;

}
void FlatAllocator::printProcesses() {
    std::vector<std::string> processNameListOutputStrings;
    int total = 0;

    for (std::pair<std::shared_ptr<Process>, std::pair<int,int>> key : this->_memory){
        processNameListOutputStrings.push_back(key.first->getName() + 
            " " + std::to_string(key.second.second- key.second.first));

        total += key.second.second - key.second.first;
        std::cout << key.first->getName();
        std::cout << "key: " << key.first;
    }

    std::cout << "-------------" << std::endl;
    std::cout << "Memory Usage: " << total*1024 << " / " << this->_maxMemory*1024<< std::endl;
    std::cout << "Memory Util: " << ((float)total*1024 / (this->_maxMemory*1024)) * 100 << "%" << std::endl;
    
    std::cout << "Processes and memory usage" <<std::endl;

    for(std::string out : processNameListOutputStrings)
        std::cout << out << std::endl;


    
}
void FlatAllocator::vmstat() {
    // int usedMemory = 0;
    int activeMemory = 0;
    // if (_memory.size() >0)
    //     usedMemory = _memory[_memory.size()-1].second.second - _memory[0].second.first;

    for ( std::pair<std::shared_ptr<Process>, std::pair<int, int>> key : this->_memory)
        activeMemory += key.second.second - key.second.first;
    
    std::cout << _maxMemory * 1024 << " bytes " << "total memory" << std::endl;
    std::cout <<  activeMemory* 1024 << " bytes " << "used memory" << std::endl;
    std::cout << (_maxMemory-activeMemory) *1024 << " bytes " << "free memory" << std::endl;


}