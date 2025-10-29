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
    
//     void printConfig() const {
//         std::cout << "CPUs: " << _numCpu << std::endl;
//         std::cout << "Scheduler: " << _scheduler << std::endl;
//         std::cout << "Quantum Cycles: " << _quantumCycle << std::endl;
//         std::cout << "Batch Process Frequency: " << _batchProcessFreq << std::endl;
//         std::cout << "Min Instructions: " << _minIns << std::endl;
//         std::cout << "Max Instructions: " << _maxIns << std::endl;
//         std::cout << "Delays per Execution: " << _delaysPerExec << std::endl;
        
//     }
};

