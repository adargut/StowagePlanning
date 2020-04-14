//
// Created by Nir on 13/04/2020.
//

#ifndef EX1_ALGORITHMERROR_H
#define EX1_ALGORITHMERROR_H


class AlgorithmError {
public:
    enum Type { IgnoredContainer, InvalidCommand, InvalidCraneOperation };
private:
    Type type;
public:
    explicit AlgorithmError(Type _type);
};


#endif //EX1_ALGORITHMERROR_H
