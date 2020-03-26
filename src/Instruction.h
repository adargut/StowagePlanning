/**
    Instruction.h
    Implementation of a single load/unload/reject instruction
*/
#ifndef EX1_INSTRUCTION_H
#define EX1_INSTRUCTION_H


class Instruction {
public:
    enum Operation { Load, Unload, Reject };
private:
    Operation op;
    int container_id;
    int floor_idx;
    int row;
    int col;
public:
    Instruction(Operation _op, int _container_id, int _floor_idx, int _row, int _col);
    Operation getOp() const;
    int getContainerId() const;
    int getFloorIdx() const;
    int getRow() const;
    int getCol() const;
};


#endif //EX1_INSTRUCTION_H
