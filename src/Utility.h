/**
    Utility.h
    Additional utility functions and typedef declarations
*/
#ifndef EX1_UTILITY_H
#define EX1_UTILITY_H

#include <vector>
#include <map>
#include <array>
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
class HashContainer;
class DistanceToDestinationComparator;

// Typedef declarations
typedef typename std::ifstream ifstream;
typedef typename std::vector<std::vector<std::vector<int>>> Plan;
typedef typename std::vector<Instruction> Instructions;
typedef typename std::array<int, 3> Position;
typedef typename std::map<int, std::pair<const Container* const, Position>> ContainerMap;
typedef typename std::vector<const Container*> ContainersVector;
typedef typename std::vector<std::string> Route;

// Utility functions
bool readShipPlan(const std::string& path);
bool readShipRoute(const std::string& path);
bool performInstructions(Ship& ship, Port& port, Instructions& instructions);
//bool performSimulation(Ship& ship, Route ports, StowageAlgorithm& algorithm);

class DistanceToDestinationComparator
{
private:
    const int& current_port_idx;
    const Route& route;
    int distance_to_destination(const Container* container);
public:
    DistanceToDestinationComparator(const int& _current_port_idx, const Route& _route);
    bool operator()(const Container* c1, const Container* c2);
};

#endif //EX1_UTILITY_H
