#ifndef INSTRUCTION_H
#define INSTRUCTION_H

enum InstructionType{
    DECLARE, ADD, SUB, PRINT
};

class Instruction {
    public:
        virtual void execute() =0;
        Instruction(InstructionType inst_type);
    
    private:
        InstructionType instructionType;
};


#endif