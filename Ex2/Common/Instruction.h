//
// Created by nir on 15/05/2020.
//

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
public:
    explicit Instruction(Operation _op = None, const std::string& _container_id = "", int _floor = -1,
                         int _row = -1, int _col = -1);
    const std::string& getContainerId() const;
    Operation getOp() const;
    int getFloor() const;
    int getRow() const;
    int getCol() const;
    // TODO Utility functions to convert instructions to string
   static std::string opToString(Operation oper);
   static void instructionToString(const Instruction &instruction, std::string &result);
   static std::string instructionsToString(const Instructions& instructions);
};


#endif //EX2_INSTRUCTION_H
