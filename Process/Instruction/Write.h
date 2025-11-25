#ifndef WRITE_H 
#define WRITE_H

#include <cstdio>
#include "./Instruction.h"

class Instruction;
class Write : public Instruction {
    public:
        Write(std::string, std::string);
        ~Write() = default;

        void execute(int cpu) override;
        std::string getInstructionType() override;

    private:
        std::string var;      
        std::string memAddress;      
};

#endif