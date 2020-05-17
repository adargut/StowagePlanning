//
// Created by nir on 15/05/2020.
//

#include "Instruction.h"

string Instruction::opToString(Operation oper)
{
    switch(oper) {
        case Load:
            return "L";
        case Unload:
            return "U";
        case Reject:
            return "R";
        case Move:
            return "M";
        case None:
            return "";
    }
    return "";
}

Instruction::Instruction(Instruction::Operation _op, const std::string& _container_id, int _floor, int _row, int _col,
                         int _new_floor, int _new_row, int _new_col) :
        op(_op), container_id(_container_id), floor(_floor), row(_row), col(_col),
        new_floor(_new_floor), new_row(_new_row), new_col(_new_col){}

Instruction::Operation Instruction::getOp() const 
{
    return op;
}

const std::string& Instruction::getContainerId() const 
{
    return container_id;
}

int Instruction::getFloor() const 
{
    return floor;
}

int Instruction::getRow() const 
{
    return row;
}

int Instruction::getCol() const 
{
    return col;
}

void Instruction::instructionToString(const Instruction &instruction, std::string &result)
{
    result.clear();
    if (instruction.getOp() == None) { // Do not print empty instructions
        return;
    }
    result.append(instruction.opToString(instruction.getOp())); // New instruction to write
    result.append(DELIMETER); // Put space to separate instructions
    result.append(instruction.getContainerId());
    result.append(DELIMETER);
    result.append(std::to_string(instruction.getFloor()));
    result.append(DELIMETER);
    result.append(std::to_string(instruction.getCol()));
    result.append(DELIMETER);
    result.append(std::to_string(instruction.getRow()));
    if(instruction.getOp() == Move)
    {
        result.append(DELIMETER);
        result.append(std::to_string(instruction.getNewFloor()));
        result.append(DELIMETER);
        result.append(std::to_string(instruction.getNewCol()));
        result.append(DELIMETER);
        result.append(std::to_string(instruction.getNewRow()));
    }
}

int Instruction::countInstructions(const Instructions &instructions)
{
    int counter = 0;
    for (auto& instruction : instructions)
    {
        if(instruction.getOp() != Instruction::Reject) counter++;
    }
    return counter;
}

int Instruction::getNewFloor() const
{
    return new_floor;
}

int Instruction::getNewRow() const
{
    return new_row;
}

int Instruction::getNewCol() const
{
    return new_col;
}
