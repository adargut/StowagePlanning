#include "AlgorithmError.h"

AlgorithmError::AlgorithmError(AlgorithmError::Type _type) : type(_type) {}

AlgorithmError::Type AlgorithmError::getType() const {
    return type;
}

std::string AlgorithmError::errorToString(AlgorithmError::Type type) {
    switch (type) {
        case IgnoredContainer:
            return "Ignored Container";
        case InvalidCommand:
            return "Invalid Command";
        case InvalidCraneOperation:
            return "Invalid Crane Operation";
    }
    return "";
}

std::string errorsToString(const AlgorithmErrors &errors) {
    std::string result;

    for (auto &error : errors) {
        result.append(AlgorithmError::errorToString(error.getType())); // New error to write
        result.append(" "); // Put space to separate errors
    }
    return result;
}
