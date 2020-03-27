/**
    Utility.h
    Additional utility functions and typedef declarations
*/
#ifndef EX1_UTILITY_H
#define EX1_UTILITY_H

#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include "Instruction.h"
#include "Port.h"
#include "Ship.h"
#include "StowageAlgorithm.h"

// Typedef declarations
typedef typename std::map<int, std::pair<Container, Position>> ContainerMap;
typedef typename std::vector<std::vector<std::vector<int>>> Plan;
typedef typename std::vector <Instruction> Instructions;
typedef typename std::tuple <int, int, int> Position;
typedef typename std::vector<Container> Containers;
typedef typename std::vector <std::string> Route;

// Utility functions
bool performInstructions(Ship& ship, Port& port, Instructions& instructions);
bool performSimulation(Ship& ship, Route ports, StowageAlgorithm algorithm);

#endif //EX1_UTILITY_H
