/**
    Error.h
    Throwable errors that occur during the run of the program
*/

#ifndef EX1_ERROR_H
#define EX1_ERROR_H

#include <iostream>

class Error {
public:
    static void throwErrorOpeningFile(const char *str = __builtin_FUNCTION());

    static void throwErrorReadingInput(const char *str = __builtin_FUNCTION());

    static void throwArrayBoundsError(const char *str = __builtin_FUNCTION());

    static void throwIncorrectFormatError(const char *str = __builtin_FUNCTION());

    static void throwSizeError(const char *str = __builtin_FUNCTION());
};


#endif //EX1_ERROR_H
