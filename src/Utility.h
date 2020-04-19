/**
    Utility.h
    Additional utility functions, macros and typedef declarations
*/

#ifndef EX1_UTILITY_H
#define EX1_UTILITY_H

#include <climits>
#include <vector>
#include <map>
#include <array>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "Error.h"

// Macros
#define SUCCESS_INDEX -1
#define CSV_SUFFIX ".csv"
#define CARGO_SUFFIX ".cargo_data"
#define CSV_SEPERATOR ","
#define BACKSLASH "/"
#define TMP_FILE "tmp.txt"
#define SIMULATION_FILE "simulation_results.csv"
#define SIMULATION_ERRORS "simulation_errors.csv"
#define DEFAULT_ERROR "No Errors for this Travel"
#define PLAN_FILE "Plan"
#define ROUTE_FILE "/Route"
#define FREE_POS "free"
#define ILLEGAL_POS "illegal"

// Forward declarations
class Container;
class Instruction;
class Ship;
class Port;
class StowageAlgorithm;
class HashContainer;
class AlgorithmError;
class Error;

// Typedef declarations
typedef typename std::unordered_map<std::string, Container*> PortContainers;
typedef typename std::ifstream ifstream;
typedef typename std::ofstream ofstream;
typedef typename std::vector<std::vector<std::vector<std::string>>> Plan;
typedef typename std::vector<Instruction> Instructions;
typedef typename std::array<int, 3> Position;
typedef typename std::unordered_map<std::string, std::pair<Container *, Position>> ContainerMap;
typedef typename std::vector<Container *> ContainersVector;
typedef typename std::vector<std::string> Route;
typedef typename std::vector<Port> Ports;
typedef typename std::vector<AlgorithmError> AlgorithmErrors;

// General purpose functions
bool fileAlreadyExists(std::string const &filename);
std::vector<std::string> split(const std::string &s, char delim);
bool isNumber(const std::string &s);

namespace Utility {
    // Populates <plan> based on description in the file named <path>
    bool readShipPlan(const std::string &travel_name, Plan &plan);
    // Populates <route> based on description in the file named <path>
    bool readShipRoute(const std::string &travel_name, Route &route);
    // Populates <ports> with the ports in route - the name of a file describing a port is the same as the port's code
    bool readPorts(const std::string &travel_name, Route &route, Ports &ports);
    // Save the instructions description in a file named <port_code.csv>
    bool savePortInstructions(const Instructions &instructions, const std::string &algorithm_name,
                              const std::string &port_code, const std::string &travel_name);
    // Save simulations results/errors in <simulation_results.csv> or <simulation_errors.csv>
    bool saveSimulation(std::string &string_to_write, const std::string &algorithm_name,
                        const std::string &travel_name, const std::string &filename);
    // Run program
    bool start(const std::string &travel_name);

    // Sorts containers based on distance to destination
    class DistanceToDestinationComparator {
    private:
        const int &current_port_idx;
        const Route &route;
    public:
        DistanceToDestinationComparator(const int &_current_port_idx, const Route &_route);
        // Returns distance from container to destination based on current port index
        int distanceToDestination(const Container *container);
        bool operator()(const Container* c1, const Container* c2);
    };
}

#endif //EX1_UTILITY_H
