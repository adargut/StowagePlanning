#ifndef EX2_ERROR_H
#define EX2_ERROR_H

#include "../common/Instruction.h"
#include "../common/GeneralUtility.h"

/**
 * @brief Error.h represents an error that occurred in the run of the simulation
 * 
 */
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
};


#endif //EX2_ERROR_H
