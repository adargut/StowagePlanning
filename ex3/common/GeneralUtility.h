#ifndef EX2_GENERALUTILITY_H
#define EX2_GENERALUTILITY_H

#define BAD_WEIGHT -1
#define BAD_DESTINATION ""
#define FREE_POS "free"
#define ILLEGAL_POS "illegal"
#define CSV_SEPERATOR ","
#define UNDERSCORE '_'
#define DELIMETER ','
#define DELIMETER_STR ","

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <sstream>
#include <regex>
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <optional>
#include <functional>

// Forward declarations
class Container;
class TravelData;
class Instruction;
class Port;
class Error;
class AlgorithmError;

using string = std::string;

// Typedef declarations
typedef typename std::vector<std::vector<std::vector<std::string>>> Plan;
typedef typename std::vector<std::vector<AlgorithmError>> AlgorithmErrors;
typedef typename std::pair<string, const TravelData&> ProcessedDataSingleton;
typedef typename std::vector<ProcessedDataSingleton> ProcessedDataList;
// Map algorithm name to vector of results & travel names for all travels
typedef typename std::unordered_map<string, std::unordered_map<string, string>> AlgorithmTravelResultsMap;
typedef typename std::unordered_map<std::string, std::shared_ptr<Container>> PortContainers;
typedef typename std::array<int, 3> Position;
typedef typename std::unordered_map<std::string, std::pair<std::shared_ptr<Container>, Position>> ContainerMap;
typedef typename std::vector<std::shared_ptr<Container>> ContainersVector;
typedef typename std::vector<std::string> Route;
typedef typename std::vector<Port> Ports; //TODO shouldn't be here since not in use by the algorithms
typedef typename std::vector<Instruction> Instructions;
typedef typename std::vector<Error> Errors;

/**
 * @brief GeneralUtility.h provides declarations and general use utility functions
 * 
 */
namespace GeneralUtility
{
    void split(std::vector<string>& result, const std::string &s, char delim);
    void trim(std::string& s, const string t = " \t\n\r\f\v");
    void removeLeadingAndTrailingSpaces(std::vector<string> &split_line);
}


#endif //EX2_GENERALUTILITY_H
