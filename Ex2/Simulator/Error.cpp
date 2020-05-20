//
// Created by nir on 16/05/2020.
//

#include "Error.h"

Error::Error(Error::Type _type, Instruction _instruction, string _description) : type(_type),
             instruction(_instruction), description(_description) {}

Error::Type Error::getType() const 
{
    return type;
}

Instruction Error::getInstruction() const 
{
    return instruction;
}

std::string Error::errorToString() 
{
    string ans = "";
    string inst = "";
    Instruction::instructionToString(instruction, inst);

    switch (type) 
    {
        case IgnoredContainer:
            ans = "Ignored Container";
            break;
        case InvalidCommand:
            ans = "Invalid Command";
            break;
        case InvalidCraneOperation:
            ans = "Invalid Crane Operation";
            break;
    };
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
