#ifndef READ_H
#define READ_H

#include <cstdio>
#include "./Instruction.h"

class Instruction;
class Read : public Instruction {
    public:
        Read(std::string, std::string);
        ~Read() = default;

        void execute(int cpu) override;
        std::string getInstructionType() override;

    private:
        std::string var;      
        std::string memAddress;      
};

#endif