#ifndef EX2_INPUTUTILITY_H
#define EX2_INPUTUTILITY_H

#include <boost/algorithm/string/predicate.hpp>
#include <boost/program_options.hpp>
#include <filesystem>
#include <iostream>
#include <vector>

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

namespace po = boost::program_options;
namespace fs = std::filesystem;
using directory_iterator = fs::directory_iterator;
using string = std::string;
using std::cout;


namespace InputUtility
{
//    bool handleTravelArg(const string& travel_path, string& route_file, string& plan_file);
//    bool handleAlgorithmArg(const string& algorithm_path, std::vector<string>& algorithm_paths);
//    bool handleAlgorithmArg(std::vector<string>& algorithm_paths);
//    bool handleOutputArg(const string& path, string& output_path);
//    bool handleOutputArg(const string& output_path);
    bool handleArgs(int argc, char **argv, std::vector<string> &travel_paths, string algorithmsDir,
                    std::vector<string> &algorithmNames, string &outputPath);
}


#endif //EX2_INPUTUTILITY_H
