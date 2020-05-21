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

// std::string Error::errorsToString(const Errors &errors) 
// {
//     std::string result;

//     for (auto &error : errors) {
//         result.append(Error::errorToString(error.getType())); // New error to write
//         result.append(" "); // Put space to separate errors
//         Instruction::instructionToString(error.instruction, result); // Append erroneous instruction
//         if (error.instruction.getOp() != Instruction::None) result.append(" ");
//     }
//     return result;
// }
