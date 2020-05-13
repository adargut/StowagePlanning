#ifndef EX2_INPUTUTILITY_H
#define EX2_INPUTUTILITY_H

#include <boost/algorithm/string/predicate.hpp>
#include <boost/program_options.hpp>
#include <filesystem>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <string>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <unordered_set>
#include "../Common/AlgorithmError.h"
#include "GeneralUtility.h"

// macros
#define TRAVEL_OPTION "travel_path"
#define ALGORITHM_OPTION "algorithm_path"
#define OUTPUT_OPTION "output_path"
#define TRAVEL_DESC "path to travel"
#define ALGORITHM_DESC "path to algorithm"
#define OUTPUT_DESC "path to output"
#define ROUTE_SUFFIX ".route"
#define PLAN_SUFFIX ".ship_plan"
#define SO_SUFFIX ".so"
#define ILLEGAL_POS "illegal"
#define CARGO_SUFFIX ".cargo_data"
#define CWD "./"
#define COMMENT '#'
#define DELIMETER ", "

// typedef declarations
typedef std::pair<int, int> pos;
typedef typename std::vector<std::string> Route;

// namespace declarations
namespace po = boost::program_options;
namespace fs = std::filesystem;

// using declarations
using std::cout;
using std::stoi;
using std::getline;
using DirectoryIterator = fs::directory_iterator;
using ErrorSet = std::unordered_set<AlgorithmError::errorCode>;
using string = std::string;
using ifstream = std::ifstream;


namespace InputUtility
{
    // Populates plan (if possible), returns set of errors that occurred in the procedure
    ErrorSet readShipPlan(const std::string& full_path_and_file_name, Plan& plan);
    // Populates route (if possible), returns set of errors that occurred in the procedure
    ErrorSet readShipRoute(const std::string& full_path_and_file_name, Route& route);
    // Parses command line arguments: stores results in travel_paths, algorithms_dir, algorithm_names & output_path
    bool handleArgs(int argc, char **argv, std::vector<string> &travel_paths, string algorithms_dir,
                    std::vector<string> &algorithm_names, string &output_path);
}


#endif //EX2_INPUTUTILITY_H
