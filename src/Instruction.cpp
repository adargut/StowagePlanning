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
