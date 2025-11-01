#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <string>

enum InstructionType{
    DECLARE, ADD, SUB, PRINT
};

class Instruction {
    public:
        virtual void execute() ;
        virtual std::string getInstructionType() ;
        // Instruction();
        Instruction(InstructionType inst_type);
        ~Instruction() = default;
    private:
        InstructionType instructionType;
};


#endif