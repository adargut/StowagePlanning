//
// Created by adargut on 5/12/20.
//

#ifndef EX2_GENERALUTILITY_H
#define EX2_GENERALUTILITY_H

#define BAD_WEIGHT -1
#define BAD_DESTINATION ""
#define FREE_POS "free"
#define ILLEGAL_POS "illegal"
#define CSV_SEPERATOR ","
#define UNDERSCORE "_"

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

// Forward declarations
class Container;
class Instruction;
class Port;
class Error;
class AlgorithmError;

using string = std::string;

// Typedef declarations
typedef typename std::vector<std::vector<std::vector<std::string>>> Plan;
typedef typename std::array<const string&, 2> AlgorithmResults;
typedef typename std::vector<std::vector<AlgorithmError>> AlgorithmErrors;
typedef typename std::unordered_map<const string&, std::vector<AlgorithmResults>> AlgorithmTravelResults; 
typedef typename std::unordered_map<const string&, AlgorithmErrors> AlgorithmTravelErrors;
// TODO should this be shared? not sure
typedef typename std::unordered_map<std::string, std::shared_ptr<Container>> PortContainers;
typedef typename std::array<int, 3> Position;
typedef typename std::unordered_map<std::string, std::pair<std::shared_ptr<Container>, Position>> ContainerMap;
typedef typename std::vector<std::shared_ptr<Container>> ContainersVector;
typedef typename std::vector<std::string> Route;
typedef typename std::vector<Port> Ports;
typedef typename std::vector<Instruction> Instructions;
typedef typename std::vector<Error> Errors;


namespace GeneralUtility
{
    //
}


#endif //EX2_GENERALUTILITY_H
