/**
    Instruction.h
    Implementation of a single load/unload/reject instruction
*/
#ifndef EX1_INSTRUCTION_H
#define EX1_INSTRUCTION_H

#include "Utility.h"

class Instruction {
public:
    enum Operation { Load, Unload, Reject };
private:
    const Operation op;
    const int container_id;
    const int floor;
    const int row;
    const int col;
public:
    Instruction(Operation _op, int _container_id, int _floor, int _row, int _col);
    int getContainerId() const;
    Operation getOp() const;
    int getFloor() const;
    int getRow() const;
    int getCol() const;
};

#endif //EX1_INSTRUCTION_H
