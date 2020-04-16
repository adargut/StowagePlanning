#include "Instruction.h"

Instruction::Instruction(Instruction::Operation _op, int _container_id, int _floor, int _row, int _col) :
op(_op), container_id(_container_id), floor(_floor), row(_row), col(_col) {};

Instruction::Operation Instruction::getOp() const {
    return op;
}

int Instruction::getContainerId() const {
    return container_id;
}

int Instruction::getFloor() const {
    return floor;
}

int Instruction::getRow() const {
    return row;
}

int Instruction::getCol() const {
    return col;
}

std::string Instruction::opToString(Instruction::Operation op) {
    switch(op) {
        case Load:
            return "Load";
        case Unload:
            return "Unload";
        case Reject:
            return "Reject";
    }
    return "";
}

std::string Instruction::instructionsToString(const Instructions &instructions) {
    std::string result = CSV_SEPERATOR;

    for (size_t i = 0; i < instructions.size() - 1; i++) {
        Instruction instruction = instructions[i];
        result.append(instruction.opToString(instruction.getOp())); // New instruction to write
        result.append(" "); // Put space to separate instructions
    }
    Instruction last_instruction = instructions[instructions.size() - 1];
    result.append(last_instruction.opToString(last_instruction.getOp()));
    return result;
}
