#include "config.h"

Config::Config(){
}

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
        else if (key == "max-overall-mem") {
            try {
                this->_maxOverallMem = std::stoi(value);
            } catch (...) { std::cerr << "Error parsing max-overall-mem." << std::endl; }
        }
        else if (key == "mem-per-frame"){
            try{
                this-> _memPerFrame= std::stoi(value);
            } catch(...) { std::cerr << "Error parsing " << std::endl;}
        }
        else if (key == "min-mem-per-proc"){
            try{
                this->_minMemPerProc= std::stoi(value);
            } catch(...) { std::cerr << "Error parsing " << std::endl;}
        }
        else if (key == "max-mem-per-proc"){
            try{
                this->_maxMemPerProc= std::stoi(value);
            } catch(...) { std::cerr << "Error parsing " << std::endl;}
        }
    }

    inputFile.close();
}