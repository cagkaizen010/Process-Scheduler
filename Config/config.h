#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Config {
private:
    int _numCpu;                // CPU
    std::string _scheduler;     // Scheduler
    int _quantumCycle;          // Scheduler
    float _batchProcessFreq;    // CPU
    int _minIns;                // Process
    int _maxIns;                // Process
    float _delaysPerExec;       // CPU
    
public:
    Config(); 
    ~Config() = default; 

    int get_numCpu(){return _numCpu;}
    std::string get_scheduler(){return _scheduler;}
    int get_quantumCycle(){return _quantumCycle;} 
    float get_batchProcessFreq(){return _batchProcessFreq;}
    int get_minIns(){return _minIns;}
    int get_maxIns(){return _maxIns;}
    float get_delaysPerExec(){return _delaysPerExec;}
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

#endif