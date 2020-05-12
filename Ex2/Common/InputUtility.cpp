#include "InputUtility.h"


bool handleTravelArg(const string& travel_path, std::vector<string>& travel_paths) {
    if (!fs::exists(travel_path)) {
        // TODO return fatal error and make sure travel stops
        return false;
    }

    // Check if travel path contains both route and plan files
    for (const auto &entry : directory_iterator(travel_path)) {
        bool valid_route_file = false, valid_plan_file = false;
        if (entry.is_directory()) {
            string travel_directory = entry.path();
            for (const auto &file : directory_iterator(travel_directory)) {
                string file_path = file.path();
                if (boost::algorithm::ends_with(file_path, ROUTE_SUFFIX)) {
                    //TODO parse route file
                    //route_file = file_path;
                    if (valid_route_file)                     // Two or more route files
                    {
                        valid_route_file = false;
                        break;
                    }
                    valid_route_file = true;
                } else if (boost::algorithm::ends_with(file_path, PLAN_SUFFIX)) {
                    //TODO parse plan file
                    //plan_file = file_path;
                    if (valid_plan_file)                    // Two or more plan files
                    {
                        valid_plan_file = false;
                        break;
                    }
                    valid_plan_file = true;
                }
            }
            if (valid_plan_file && valid_route_file) {
                travel_paths.push_back(std::move(travel_directory));
            }
        }
    }
    return !travel_paths.empty();
    // TODO remove this?
//    for (const auto& entry : directory_iterator(travel_path))
//    {
//        string file_path = entry.path();
//        if (boost::algorithm::ends_with(file_path, CARGO_SUFFIX))
//        {
//            // TODO handle cargo found
//        }
//    }
}


bool handleAlgorithmArg(std::vector<string>& algorithm_paths)
{
    // Iterate over current working directory
    for (const auto& entry : directory_iterator(CWD))
    {
        string file_path = entry.path();
        if (boost::algorithm::ends_with(file_path, SO_SUFFIX))
        {
            algorithm_paths.push_back(std::move(file_path));
        }
    }
    return true;
}

bool handleAlgorithmArg(const string& algorithm_path, std::vector<string>& algorithm_paths)
{
    // TODO implement me
    if (!fs::exists(algorithm_path))
    {
        // TODO error and ask what to do?
        return false;
    }

    for (const auto& entry : directory_iterator(algorithm_path))
    {
        string file_path = entry.path();
        if (boost::algorithm::ends_with(file_path, SO_SUFFIX))
        {
            algorithm_paths.push_back(std::move(file_path));
        }
    }
    return true;
}

bool handleOutputArg(const string& path, string& output_path)
{
    if (!fs::exists(path))
    {
        fs::create_directory(path); // TODO maybe check if permissions work?
    }
    output_path = path;
    return true;
}

bool handleOutputArg(string& output_path)
{
    output_path = CWD;
    return true;
}

bool
InputUtility::handleArgs(int argc, char **argv, std::vector<string> &travel_paths, std::vector<string> &algorithm_paths,
                         string &output_path)
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
        handleTravelArg(vm[TRAVEL_OPTION].as<string>(), travel_paths);
    }
    else
    {
        // TODO return fatal error because no travel supplied and stop travel
        return false;
    }
    // Parse path to algorithm folder
    if (vm.count(ALGORITHM_OPTION))
    {
        handleAlgorithmArg(vm[ALGORITHM_OPTION].as<string>(), algorithm_paths);
    }
    else
    {
        handleAlgorithmArg(algorithm_paths);
    }
    // Parse path to output folder
    if (vm.count(OUTPUT_OPTION))
    {
        handleOutputArg(vm[OUTPUT_OPTION].as<string>(), output_path);
    }
    else
    {
        handleOutputArg(output_path);
    }
    return true;
}