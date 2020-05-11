#include "InputUtility.h"


bool handleTravelArg(const string& travel_path)
{
    if (!fs::exists(travel_path))
    {
        // TODO return fatal error and make sure travel stops
        return false;
    }

    // Check if travel path contains both route and plan files
    string route_file, plan_file;
    for (const auto& entry : directory_iterator(travel_path))
    {
        string file_path = entry.path();
        if (boost::algorithm::ends_with(file_path, ROUTE_SUFFIX))
        {
            //TODO parse route file
            route_file = file_path;
        }
        else if (boost::algorithm::ends_with(file_path, PLAN_SUFFIX))
        {
            //TODO parse plan file
            plan_file = file_path;
        }
    }
    if (plan_file.empty() || plan_file.empty())
    {
        //TODO fatal error
        return false;
    }

    for (const auto& entry : directory_iterator(travel_path))
    {
        string file_path = entry.path();
        if (boost::algorithm::ends_with(file_path, CARGO_SUFFIX))
        {
            // TODO handle cargo found
        }

    }

    return true;
}

bool handleAlgorithmArg(const string& algorithm_path)
{
    return true;
}

bool handleAlgorithmArg()
{
    return true;
}

bool handleOutputArg(const string& algorithm_path)
{
    return true;
}


bool handleArgs(int argc, char** argv)
{
    // Declare the supported options
    po::options_description desc("Allowed options");
    desc.add_options()
            (TRAVEL_OPTION, po::value<string>(), TRAVEL_DESC)
            (OUTPUT_OPTION, po::value<string>(), OUTPUT_DESC)
            (ALGORITHM_OPTION, po::value<string>(), ALGORITHM_DESC);

    // Store the command line arguments in a variable map
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv)
                      .options(desc)
                      .style(po::command_line_style::unix_style | po::command_line_style::allow_long_disguise)
                      .run(), vm);
    po::notify(vm);

    // Parse path to travel folder
    if (vm.count(TRAVEL_OPTION))
    {
        handleTravelArg(vm[TRAVEL_OPTION].as<string>());
    }
    else
    {
        // TODO return fatal error because no travel supplied and stop travel
        return false;
    }

    // Parse path to algorithm folder
    if (vm.count(ALGORITHM_OPTION))
    {
        handleAlgorithmArg(vm[ALGORITHM_OPTION].as<string>());
    }
    else
    {
        handleAlgorithmArg();
    }

    // Parse path to output folder
    if (vm.count(OUTPUT_OPTION))
    {
        handleOutputArg(vm[OUTPUT_OPTION].as<string>());
    }
    else
    {
        handleAlgorithmArg();
    }

    return true;
}