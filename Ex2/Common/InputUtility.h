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
#include "../Common/AlgorithmError.h"
#include "GeneralUtility.h"

#define TRAVEL_OPTION "travel_path"
#define ALGORITHM_OPTION "algorithm_path"
#define OUTPUT_OPTION "output_path"
#define TRAVEL_DESC "path to travel"
#define ALGORITHM_DESC "path to algorithm"
#define OUTPUT_DESC "path to output"
#define ROUTE_SUFFIX ".route"
#define PLAN_SUFFIX ".ship_plan"
#define SO_SUFFIX ".so"
#define CARGO_SUFFIX ".cargo_data"
#define CWD "./"
#define COMMENT '#'
#define DELIMETER ", "

namespace po = boost::program_options;
namespace fs = std::filesystem;
using directory_iterator = fs::directory_iterator;
using string = std::string;
using std::cout;
using stoi = std::stoi;
using ifstream = std::ifstream;
using getline = std::getline;


namespace InputUtility
{
//    bool handleTravelArg(const string& travel_path, string& route_file, string& plan_file);
//    bool handleAlgorithmArg(const string& algorithm_path, std::vector<string>& algorithm_paths);
//    bool handleAlgorithmArg(std::vector<string>& algorithm_paths);
//    bool handleOutputArg(const string& path, string& output_path);
//    bool handleOutputArg(const string& output_path);
    bool handleArgs(int argc, char **argv, std::vector<string> &travel_paths, std::vector<string> &algorithm_paths,
                    string &output_path);
    AlgorithmError::errorCode readShipPlan(const std::string& full_path_and_file_name, Plan& plan);
}


#endif //EX2_INPUTUTILITY_H
