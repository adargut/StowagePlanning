#include "AlgorithmError.h"

AlgorithmError::AlgorithmError(AlgorithmError::Type _type, Instruction _instruction) : type(_type),
                                                                                       instruction(_instruction) {}

AlgorithmError::Type AlgorithmError::getType() const {
    return type;
}

Instruction AlgorithmError::getInstruction() const {
    return instruction;
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

std::string AlgorithmError::errorsToString(const AlgorithmErrors &errors) {
    std::string result;

    for (auto &error : errors) {
        result.append(AlgorithmError::errorToString(error.getType())); // New error to write
        result.append(" "); // Put space to separate errors
        Instruction::instructionToString(error.instruction, result); // Append erroneous instruction
        if (error.instruction.getOp() != Instruction::None) result.append(" ");
    }
    return result;
}