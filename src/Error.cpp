#include "Error.h"

void Error::throwErrorOpeningFile() { // TODO fill me with many errors and put them where they should be..
    std::cout << "Error: cannot open file at" << __FUNCTION__ << std::endl;
}

void Error::throwSizeError() {
    std::cout << "Error: non-matching vector sizes at" << __FUNCTION__ << std::endl;
}

void Error::throwArrayBoundsError() {
    std::cout << "Error: out of array bounds at" << __FUNCTION__ << std::endl;
}

void Error::throwErrorReadingInput() {
    std::cout << "Error: reading input failed at" << __FUNCTION__ << std::endl;
}
