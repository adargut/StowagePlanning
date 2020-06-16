#ifndef EX2_INPUTUTILITY_H
#define EX2_INPUTUTILITY_H

#include <filesystem>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include "AlgorithmError.h"
#include "Port.h"
#include "GeneralUtility.h"
#include "Instruction.h"
#include "ISO_6346.h"
#include "../simulator/Error.h" 

// macros
#define TRAVEL_OPTION "-travel_path"
#define ALGORITHM_OPTION "-algorithm_path"
#define OUTPUT_OPTION "-output"
#define NUM_THREADS_OPTION "-num_threads"
#define ROUTE_SUFFIX ".route"
#define PLAN_SUFFIX ".ship_plan"
#define CRANE_INSTRUCTIONS_SUFFIX ".crane_instructions"
#define SO_SUFFIX ".so"
#define ILLEGAL_POS "illegal"
#define CARGO_SUFFIX ".cargo_data"
#define CWD "./"
#define COMMENT '#'

// typedef declarations
typedef std::pair<int, int> pos;

// namespace declarations
namespace fs = std::filesystem;

// using declarations
using std::cout;
using std::stoi;
using std::getline;
using DirectoryIterator = fs::directory_iterator;
using ErrorSet = std::unordered_set<AlgorithmError::errorCode>;
using string = std::string;
using ifstream = std::ifstream;

/**
 * @brief InputUtility.h provides utilities for handling input
 * 
 */
namespace InputUtility
{
    AlgorithmError readShipPlan(const std::string& full_path_and_file_name, Plan& plan);
    AlgorithmError readShipRoute(const std::string& full_path_and_file_name, Route& route);
    AlgorithmError readCargo(const std::string& full_path_and_file_name, ContainersVector &containers_to_load);
    bool readCraneInstructions(const std::string& full_path_and_file_name, Instructions& instructions);
    string getFileName(const std::string& full_path_and_file_name);
}


#endif //EX2_INPUTUTILITY_H
