#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Config {
private:
    int _numCpu;
    std::string _scheduler;
    int _quantumCycle;
    float _batchProcessFreq;
    int _minIns;
    int _maxIns;
    float _delaysPerExec;
    
public:
    Config() {}
    ~Config() {}
    
    void initialize();
    
    void printConfig() const {
        std::cout << "CPUs: " << _numCpu << std::endl;
        std::cout << "Scheduler: " << _scheduler << std::endl;
        std::cout << "Quantum Cycles: " << _quantumCycle << std::endl;
        std::cout << "Batch Process Frequency: " << _batchProcessFreq << std::endl;
        std::cout << "Min Instructions: " << _minIns << std::endl;
        std::cout << "Max Instructions: " << _maxIns << std::endl;
        std::cout << "Delays per Execution: " << _delaysPerExec << std::endl;
        
    }
};


void Config::initialize() {
    std::ifstream inputFile("config.txt");
    
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open config.txt file." << std::endl;
        return;
    }

    std::string line;
    std::string key;
    std::string value;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        if (!(iss >> key >> value)) {
            continue; 
        }

        // Use sequential if/else if checks instead of std::unordered_map
        if (key == "num-cpu") {
            try {
                this->_numCpu = std::stoi(value);
            } catch (...) { std::cerr << "Error parsing num-cpu." << std::endl; }
        } 
        else if (key == "scheduler") {
            if (value.length() > 2 && value.front() == '"' && value.back() == '"') {
                this->_scheduler = value.substr(1, value.length() - 2);
            } else {
                this->_scheduler = value;
            }
        } 
        else if (key == "quantum-cycles") {
            try {
                this->_quantumCycle = std::stoi(value);
            } catch (...) { std::cerr << "Error parsing quantum-cycles." << std::endl; }
        }
        else if (key == "batch-process-freq") {
            try {
                this->_batchProcessFreq = std::stof(value);
            } catch (...) { std::cerr << "Error parsing batch-process-freq." << std::endl; }
        }
        else if (key == "min-ins") {
            try {
                this->_minIns = std::stoi(value);
            } catch (...) { std::cerr << "Error parsing min-ins." << std::endl; }
        }
        else if (key == "max-ins") {
            try {
                this->_maxIns = std::stoi(value);
            } catch (...) { std::cerr << "Error parsing max-ins." << std::endl; }
        }
        else if (key == "delay-per-exec") {
            try {
                this->_delaysPerExec = std::stof(value);
            } catch (...) { std::cerr << "Error parsing delay-per-exec." << std::endl; }
        }
    }

    inputFile.close();
}

// Main function to demonstrate the usage
int main() {
    Config programConfig;
    programConfig.initialize();
    programConfig.printConfig();
    return 0;
}