#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <string>

enum InstructionType{
    DECLARE, ADD, SUB, PRINT
};

class Instruction {
    public:
        virtual void execute() =0;
        virtual std::string getInstructionType() =0; 
        // Instruction();
        Instruction(InstructionType inst_type);
        virtual ~Instruction() = default;
    private:
        InstructionType instructionType;
};


#endif