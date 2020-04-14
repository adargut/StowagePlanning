#ifndef EX1_ALGORITHMERROR_H
#define EX1_ALGORITHMERROR_H

#include "Utility.h"

class AlgorithmError {
public:
    enum Type {
        IgnoredContainer, InvalidCommand, InvalidCraneOperation
    };
private:
    Type type;
public:
    Type getType() const;

public:
    explicit AlgorithmError(Type _type);

    static std::string errorToString(Type type);

    static std::string errorsToString(const AlgorithmErrors &errors);
};


#endif //EX1_ALGORITHMERROR_H
