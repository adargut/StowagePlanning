//
// Created by Adar on 25/03/2020.
//

#include "Instruction.h"

Instruction::Operation Instruction::getOp() const {
    return op;
}

int Instruction::getContainerId() const {
    return container_id;
}

int Instruction::getFloorIdx() const {
    return floor_idx;
}

int Instruction::getRow() const {
    return row;
}

int Instruction::getCol() const {
    return col;
}
