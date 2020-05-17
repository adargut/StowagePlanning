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

class Container;
class Instruction;
class Port;
class Error;
// typedef declarations
typedef typename std::vector<std::vector<std::vector<std::string>>> Plan;
// TODO should this be shared? not sure
typedef typename std::unordered_map<std::string, std::shared_ptr<Container>> PortContainers;
typedef typename std::array<int, 3> Position;
typedef typename std::unordered_map<std::string, std::pair<std::shared_ptr<Container>, Position>> ContainerMap;
typedef typename std::vector<std::shared_ptr<Container>> ContainersVector;
typedef typename std::vector<std::string> Route;
typedef typename std::vector<Port> Ports;
typedef typename std::vector<Instruction> Instructions;
typedef typename std::vector<Error> Errors;
using string = std::string;


namespace GeneralUtility
{
    //
}


#endif //EX2_GENERALUTILITY_H
