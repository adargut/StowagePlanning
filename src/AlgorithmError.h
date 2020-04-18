/**
    AlgorithmError.h
    An error that occurred during the run of the algorithm, output to simulation errors
*/

#ifndef EX1_ALGORITHMERROR_H
#define EX1_ALGORITHMERROR_H

#include "Utility.h"
#include "Instruction.h"

class AlgorithmError {
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
    explicit AlgorithmError(Type _type, Instruction _instruction = Instruction());
    static std::string errorToString(Type type);
    static std::string errorsToString(const AlgorithmErrors &errors);
};

#endif //EX1_ALGORITHMERROR_H
