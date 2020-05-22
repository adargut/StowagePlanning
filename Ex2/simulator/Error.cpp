//
// Created by nir on 16/05/2020.
//

#include "Error.h"

Error::Error(string _description, Instruction _instruction) : description(_description), instruction(_instruction) {}

Instruction Error::getInstruction() const 
{
    return instruction;
}

std::string Error::errorToString() 
{
    string ans = "";
    string inst = "";
    Instruction::instructionToString(instruction, inst);
    return ans + " " + inst + " " + description ;
}
