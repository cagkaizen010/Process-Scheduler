#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <string>
#include <cstdint>

enum InstructionType{
    DECLARE, ADD, SUB, PRINT, READ, WRITE
};

class Instruction {
    public:
        virtual void execute(int cpu) =0;
        virtual std::string getInstructionType() =0; 
        // Instruction();
        Instruction(InstructionType inst_type);
        virtual ~Instruction() = default;
    private:
        InstructionType instructionType;
};


#endif