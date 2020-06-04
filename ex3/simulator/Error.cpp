
#include "Error.h"

// Constructor
Error::Error(string _description, Instruction _instruction) : description(_description), instruction(_instruction) {}

// Getter for instruction
Instruction Error::getInstruction() const 
{
    return instruction;
}

// Converts error to string
string Error::errorToString() 
{
    string ans = "";
    string inst = "";
    Instruction::instructionToString(instruction, inst);

    return ans + " " + inst + " " + description ;
}
