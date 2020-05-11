#ifndef EX2_INPUTUTILITY_H
#define EX2_INPUTUTILITY_H

#include <boost/algorithm/string/predicate.hpp>
#include <boost/program_options.hpp>
#include <filesystem>
#include <iostream>

#define TRAVEL_OPTION "travel_path"
#define TRAVEL_DESC "path to travel"
#define ALGORITHM_OPTION "-algorithm_path"
#define ALGORITHM_DESC "path to algorithm"
#define OUTPUT_OPTION "-output_path"
#define OUTPUT_DESC "path to output"
#define ROUTE_SUFFIX ".route"
#define PLAN_SUFFIX ".ship_plan"
#define CARGO_SUFFIX ".cargo_data"

namespace fs = std::filesystem;
namespace po = boost::program_options;
using string = std::string;
using std::cout;
using directory_iterator = fs::directory_iterator;


namespace InputUtility
{
    bool handleTravelArg(const string& travel_path);

    bool handleAlgorithmArg(const string& algorithm_path);

    bool handleAlgorithmArg();

    bool handleOutputArg(const string& algorithm_path);

    bool handleOutputArg();

    bool handleArgs(int argc, char** argv);
}


#endif //EX2_INPUTUTILITY_H
