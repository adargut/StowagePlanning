/**
    Utility.h
    Additional utility functions and typedef declarations
*/
#ifndef EX1_UTILITY_H
#define EX1_UTILITY_H

#include <vector>
#include <string>
#include "Instruction.h"
#include "Port.h"
#include "CargoShip.h"
#include "StowageAlgorithm.h"


// Typedef declarations
typedef typename std::vector <Instruction> Instructions;
typedef typename std::vector <std::string> Ports;
typedef typename std::vector <Container> Containers; // TODO maybe use dict instead of vector?
typedef typename std::vector<std::vector<bool>> BoolMatrix;

// Utility functions
bool performInstructions(Ship& ship, Port& port, Instructions& instructions);
bool performSimulation(Ship& ship, Ports ports, StowageAlgorithm algorithm);

#endif //EX1_UTILITY_H
