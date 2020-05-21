//
// Created by nir on 16/05/2020.
//

#ifndef EX2_ERROR_H
#define EX2_ERROR_H

#include "../Common/Instruction.h"
#include "../Common/GeneralUtility.h"

// Errors occurring in the run
class Error 
{
public:
private:
    string description;
    Instruction instruction;
public:
    Instruction getInstruction() const;
    explicit Error(string _description = "", Instruction _instruction = Instruction());
    std::string errorToString();
    // std::string errorsToString(const Errors &errors);
};


#endif //EX2_ERROR_H
