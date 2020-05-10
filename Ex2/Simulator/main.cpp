#include "../Common/InputUtility.h"
#include <filesystem>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/program_options.hpp>

#define TRAVEL_OPTION "travel_path"
#define ALGORITHM_OPTION "-algorithm_path"
#define OUTPUT_OPTION "-output_path"
#define ROUTE_SUFFIX ".route"
#define PLAN_SUFFIX ".ship_plan"
#define CARGO_SUFFIX ".cargo_data"

namespace fs = std::filesystem;
using string = std::string;
using std::cout;
using directory_iterator = fs::directory_iterator;



bool handleArgs(int argc, char** argv)
{
    namespace po = boost::program_options;
    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
            (TRAVEL_OPTION, po::value<string>(), "travel path")
            (OUTPUT_OPTION, po::value<string>(), "set compression level")
            ;

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv)
            .options(desc)
            .style(
                po::command_line_style::unix_style
                    | po::command_line_style::allow_long_disguise)
                    .run(),
                vm);
    po::notify(vm);

    if (vm.count(TRAVEL_OPTION)) {
        cout << vm[TRAVEL_OPTION].as<string>() << "\n";
    }
    else {
        cout << "No travel option supplied.\n";
    }
    return true;
}


int main(int argc, char *argv[]) {
    handleArgs(argc, argv);
//    if (!InputUtility::cmdOptionExists(argv, argv+argc, TRAVEL_OPTION))
//    {
//        // TODO return fatal error and make sure travel stops
//    }
//
//    string travel_path = InputUtility::getCmdOption(argv, argv+argc, TRAVEL_OPTION);
//    if (!fs::exists(travel_path))
//    {
//        // TODO return fatal error and make sure travel stops
//    }
//    string route_file, plan_file;
//    for (const auto& entry : directory_iterator(travel_path))
//    {
//        string file_path = entry.path();
//        if (boost::algorithm::ends_with(file_path, ROUTE_SUFFIX))
//        {
//            //TODO parse route file
//            route_file = file_path;
//        }
//        else if (boost::algorithm::ends_with(file_path, PLAN_SUFFIX))
//        {
//            //TODO parse plan file
//            plan_file = file_path;
//        }
//    }
//    if (plan_file.empty() || plan_file.empty())
//    {
//        //TODO fatal error
//    }



}