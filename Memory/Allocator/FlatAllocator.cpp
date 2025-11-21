#include "FlatAllocator.h"


FlatAllocator::FlatAllocator(int maxMemory) : _maxMemory(maxMemory){

    // Load backing store file
    std::ofstream file("csopesy-backing-store.txt", std::ios::trunc);
    file.close();
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