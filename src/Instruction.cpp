#include "Instruction.h"

Instruction::Instruction(Instruction::Operation _op, const std::string& _container_id, int _floor, int _row, int _col) :
op(_op), container_id(_container_id), floor(_floor), row(_row), col(_col) {}

Instruction::Operation Instruction::getOp() const {
    return op;
}

const std::string& Instruction::getContainerId() const {
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
        case None:
            return "";
    }
    return "";
}

void Instruction::instructionToString(const Instruction &instruction, std::string &result) {
    if (instruction.getOp() == None) { // Do not print empty instructions
        return;
    }
    result.append(instruction.opToString(instruction.getOp())); // New instruction to write
    result.append(" "); // Put space to separate instructions
    result.append(instruction.getContainerId());
    result.append(" ");
    result.append(std::to_string(instruction.getFloor()));
    result.append(" ");
    result.append(std::to_string(instruction.getRow()));
    result.append(" ");
    result.append(std::to_string(instruction.getCol()));
}

std::string Instruction::instructionsToString(const Instructions &instructions) {
    std::string result = CSV_SEPERATOR;

    for (size_t i = 0; i < instructions.size() - 1; i++) {
        Instruction instruction = instructions[i];
        instructionToString(instruction, result);
        result.append(" ");
    }
    Instruction last_instruction = instructions[instructions.size() - 1];
    instructionToString(last_instruction, result);
    return result;
}
