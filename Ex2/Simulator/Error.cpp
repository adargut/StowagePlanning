//
// Created by nir on 16/05/2020.
//

#include "Error.h"

Error::Error(Error::Type _type, Instruction _instruction) : type(_type),
                                                            instruction(_instruction) {}

Error::Type Error::getType() const {
    return type;
}

Instruction Error::getInstruction() const {
    return instruction;
}

std::string Error::errorToString(Error::Type type) {
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

std::string Error::errorsToString(const Errors &errors) {
    std::string result;

    for (auto &error : errors) {
        result.append(Error::errorToString(error.getType())); // New error to write
        result.append(" "); // Put space to separate errors
        Instruction::instructionToString(error.instruction, result); // Append erroneous instruction
        if (error.instruction.getOp() != Instruction::None) result.append(" ");
    }
    return result;
}
