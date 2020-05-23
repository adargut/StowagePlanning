#include "Error.h"

void Error::throwErrorOpeningFile(const char *str) {
    std::cout << "Error: cannot open file at " << str << std::endl;
}

void Error::throwSizeError(const char *str) {
    std::cout << "Error: bad sizes at " << str << std::endl;
}

void Error::throwArrayBoundsError(const char *str) {
    std::cout << "Error: out of array bounds at " << str << std::endl;
}

void Error::throwErrorReadingInput(const char *str) {
    std::cout << "Error: reading input failed at " << str << std::endl;
}

void Error::throwIncorrectFormatError(const char *str) {
    std::cout << "Error: bad format given at " << str << std::endl;
}
