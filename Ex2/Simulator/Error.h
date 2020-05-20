//
// Created by nir on 16/05/2020.
//

#ifndef EX2_ERROR_H
#define EX2_ERROR_H

#include "../Common/Instruction.h"
#include "../Common/GeneralUtility.h"

// Errors detected by the simulation
class Error 
{
public:
    enum Type 
    {
        IgnoredContainer, InvalidCommand, InvalidCraneOperation
    };
private:
    Type type;
    Instruction instruction;
    string description;
public:
    Type getType() const;
    Instruction getInstruction() const;
    explicit Error(Type _type, Instruction _instruction = Instruction(), string _description = "");
    std::string errorToString();
    // std::string errorsToString(const Errors &errors);
};


#endif //EX2_ERROR_H
