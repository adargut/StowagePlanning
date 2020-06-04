#include "Instruction.h"

// Converts load/unload/reject/move operation to string
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

// Constructor
Instruction::Instruction(Instruction::Operation _op, const std::string& _container_id, int _floor, int _row, int _col,
                         int _new_floor, int _new_row, int _new_col) :
        op(_op), container_id(_container_id), floor(_floor), row(_row), col(_col),
        new_floor(_new_floor), new_row(_new_row), new_col(_new_col){}

// Getter for operation
Instruction::Operation Instruction::getOp() const 
{
    return op;
}

// Getter for ID
const std::string& Instruction::getContainerId() const 
{
    return container_id;
}

// Getter for floor
int Instruction::getFloor() const 
{
    return floor;
}

// Getter for row
int Instruction::getRow() const 
{
    return row;
}

// Getter for col
int Instruction::getCol() const 
{
    return col;
}

// Converts instruction to string
void Instruction::instructionToString(const Instruction &instruction, std::string &result)
{
    result.clear();
    // Do not print empty instructions
    if (instruction.getOp() == None) 
    { 
        return;
    }
    result.append(instruction.opToString(instruction.getOp())); // New instruction to write
    result.append(DELIMETER_STR); // Put space to separate instructions
    result.append(instruction.getContainerId());
    result.append(DELIMETER_STR);
    result.append(std::to_string(instruction.getFloor()));
    result.append(DELIMETER_STR);
    result.append(std::to_string(instruction.getCol()));
    result.append(DELIMETER_STR);
    result.append(std::to_string(instruction.getRow()));
    if(instruction.getOp() == Move)
    {
        result.append(DELIMETER_STR);
        result.append(std::to_string(instruction.getNewFloor()));
        result.append(DELIMETER_STR);
        result.append(std::to_string(instruction.getNewCol()));
        result.append(DELIMETER_STR);
        result.append(std::to_string(instruction.getNewRow()));
    }
}

// Count how many load/unload instructions are inside a vector of instructions
// TODO change score formula: load/unload=5, move=3, reject=0
int Instruction::countInstructions(const Instructions &instructions)
{
    int counter = 0;
    for (auto& instruction : instructions)
    {
        if(instruction.getOp() != Instruction::Reject) counter++;
    }
    return counter;
}

// New floor for move instructions
int Instruction::getNewFloor() const
{
    return new_floor;
}

// New row for move instructions
int Instruction::getNewRow() const
{
    return new_row;
}

// New column for move instructions
int Instruction::getNewCol() const
{
    return new_col;
}
