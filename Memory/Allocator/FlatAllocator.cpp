#include "FlatAllocator.h"


FlatAllocator::FlatAllocator(int maxMemory) : _maxMemory(maxMemory){

    // Load backing store file
    std::ofstream file("csopesy-backing-store.txt", std::ios::trunc);
    file.close();
}

bool FlatAllocator::allocate(std::shared_ptr<Process> process){
    int reqMem = process->getRequiredMemory();
    this->readBackingStore(process);
    if (this->_memory.size() == 0){
        this->_memory.push_back(std::make_pair(process, std::make_pair(0, reqMem)));
        return true;
    }
    else {
        for (std::pair<std::shared_ptr<Process>, std::pair<int, int>> mem : _memory){
            if(mem.first->getName() == process->getName())
                return true;
        }
        if (this->_memory.at(0).second.first >= reqMem){
            this->_memory.insert(this->_memory.begin(), std::make_pair(process, std::make_pair(0, reqMem)));
            return true;
        }

        for(int retryLimit = 0; retryLimit < 5; retryLimit++){
            int counter= 0;
            int index = -1;
            for (int i = 0; i < this->_memory.size()-1; i++ ){

                if (i == this->_memory.size()-1)
                    counter = this->_maxMemory - this->_memory.at(i).second.second;
                else counter = this->_memory.at(i+1).second.first - this->_memory.at(i).second.second;

                if (counter >= reqMem){
                    this->_memory.insert(this->_memory.begin() +i +1, std::make_pair(process, std::make_pair(this->_memory.at(i).second.second, this->_memory.at(i).second.second + reqMem)));
                    return true;
                }
            }
            if (this->_memory.size() > 0){
                int i = rand() % this->_memory.size();
                if (this->_memory.at(i).first->getCPUCoreID() == -1){
                    this->writeBackingStore(this->_memory.at(i).first);
                    this->_memory.erase(this->_memory.begin() + i);
                }
            }
        }
    }
    return false;
}

void FlatAllocator::deallocate(std::shared_ptr<Process> process){
    this->readBackingStore(process);

    for (int i = 0; i < this->_memory.size(); i++)
        if (this->_memory.at(i).first->getName() == process->getName())
            this->_memory.erase(this->_memory.begin() +1);
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

}
void FlatAllocator::printProcesses() {

}
void FlatAllocator::vmstat() {

}