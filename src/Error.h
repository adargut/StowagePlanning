/**
    Error.h
    Throwable errors that occur during the run of the program
*/

#ifndef EX1_ERROR_H
#define EX1_ERROR_H

#include <iostream>

class Error {
public:
    static void throwErrorOpeningFile();

    static void throwErrorReadingInput();

    static void throwArrayBoundsError();

    static void throwSizeError();
};


#endif //EX1_ERROR_H
