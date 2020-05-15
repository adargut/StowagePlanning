//
// Created by nir on 15/05/2020.
//

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