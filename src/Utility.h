/**
    Utility.h
    Additional utility functions and typedef declarations
*/
#ifndef EX1_UTILITY_H
#define EX1_UTILITY_H
#define CSV_PREFIX ".csv"
#define CSV_SEPERATOR ","

#include <vector>
#include <map>
#include <array>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>

// Forward declarations
class Container;
class Instruction;
class Ship;
class Port;
class StowageAlgorithm;
class HashContainer;
class DistanceToDestinationComparator;
class AlgorithmError;
class Error;

// Typedef declarations
typedef typename std::ifstream ifstream;
typedef typename std::ofstream ofstream;
typedef typename std::vector<std::vector<std::vector<int>>> Plan;
typedef typename std::vector<Instruction> Instructions;
typedef typename std::array<int, 3> Position;
typedef typename std::unordered_map<int, std::pair<const Container* const, Position>> ContainerMap;
typedef typename std::vector<const Container*> ContainersVector;
typedef typename std::vector<std::string> Route;
typedef typename std::vector<Port> Ports;
typedef typename std::vector<AlgorithmError> AlgorithmErrors;

namespace Utility
{
    // Utility functions
    // Populates <plan> based on description in the file named <path>
    bool readShipPlan(const std::string& path, Plan& plan);
    // Populates <route> based on description in the file named <path>
    bool readShipRoute(const std::string& path, Route& route);
    // Populates <ports> with the ports in route - the name of a file describing a port is the same as the port's code
    bool readPorts(Route& route, Ports& ports); //TODO implement me
    // Save the instructions description in a file named <path>
    bool savePortInstructions(const Instructions& instructions, const std::string& algorithm_name,
            const std::string& port_code);
    bool saveSimulationResult(int result, const std::string& algorithm_name, const std::string& port_code);
    bool saveSimulationErrors(const std::string& path, const AlgorithmErrors& errors);
    bool fileAlreadyExists (std::string const& filename);
    // Sorts containers based on distance to destination
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
}

#endif //EX1_UTILITY_H
