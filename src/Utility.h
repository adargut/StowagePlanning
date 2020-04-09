/**
    Utility.h
    Additional utility functions and typedef declarations
*/
#ifndef EX1_UTILITY_H
#define EX1_UTILITY_H

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>

// Forward declarations
class Container;
class Instruction;
class Ship;
class Port;
class StowageAlgorithm;
class hashContainer;

// Typedef declarations
typedef typename std::ifstream ifstream;
typedef typename std::vector<std::vector<std::vector<int>>> Plan;
typedef typename std::vector<Instruction> Instructions;
typedef typename std::tuple<int, int, int> Position;
typedef typename std::map<int, std::pair<const Container* const, Position>> ContainerMap;
typedef typename std::vector<const Container*> ContainersVector;
typedef typename std::vector<std::string> Route;

// Utility functions
bool readShipPlan(const std::string& path);
bool readShipRoute(const std::string& path);
bool performInstructions(Ship& ship, Port& port, Instructions& instructions);
//bool performSimulation(Ship& ship, Route ports, StowageAlgorithm& algorithm);

#endif //EX1_UTILITY_H
