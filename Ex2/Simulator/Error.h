//
// Created by nir on 16/05/2020.
//

#ifndef EX2_ERROR_H
#define EX2_ERROR_H

#include "../Common/Instruction.h"
#include "../Common/GeneralUtility.h"

// Errors detected by the simulation
class Error {
public:
    enum Type {
        IgnoredContainer, InvalidCommand, InvalidCraneOperation
    };
private:
    Type type;
    Instruction instruction;
public:
    Type getType() const;
    Instruction getInstruction() const;
    explicit Error(Type _type, Instruction _instruction = Instruction());
    static std::string errorToString(Type type);
    static std::string errorsToString(const Errors &errors);
};


#endif //EX2_ERROR_H
