//
// Created by nir on 15/05/2020.
//
/* A class to represent crane instructions provided by the algorithm */

#ifndef EX2_INSTRUCTION_H
#define EX2_INSTRUCTION_H

#include "GeneralUtility.h"

class Instruction {
public:
    enum Operation { Load, Unload, Move, Reject, None };
private:
    const Operation op;
    const std::string container_id;
    const int floor;
    const int row;
    const int col;
    const int new_floor;
    const int new_row;
    const int new_col;

public:
    explicit Instruction(Operation _op = None, const std::string& _container_id = "", int _floor = -1,
                         int _row = -1, int _col = -1, int _new_floor = -1, int _new_row = -1, int _new_col = -1);
    const std::string& getContainerId() const;
    Operation getOp() const;
    int getFloor() const;
    int getRow() const;
    int getCol() const;
    int getNewFloor() const;
    int getNewRow() const;
    int getNewCol() const;
    // Utility functions to convert instructions to string
    static string opToString(Operation oper);
    static void instructionToString(const Instruction &instruction, std::string &result);
    static int countInstructions(const Instructions& instructions);
};


#endif //EX2_INSTRUCTION_H
