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

bool handleAlgorithmArg(const string& algorithmDir, std::vector<string>& algorithm_paths)
{
    // TODO implement me
    if (!fs::exists(algorithmDir))
    {
        // TODO error and ask what to do?
        return false;
    }

    for (const auto& entry : directory_iterator(algorithmDir))
    {
        std::filesystem::path p = entry.path();
        if (p.extension() == SO_SUFFIX)
        {
            p.filename();
            p.replace_extension();
            algorithm_paths.push_back(std::move(p));
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
InputUtility::handleArgs(int argc, char **argv, std::vector<string> &travel_paths, string algorithmsDir,
                         std::vector<string> &algorithmNames, string &outputPath)
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
        algorithmsDir = vm[ALGORITHM_OPTION].as<string>();
        handleAlgorithmArg(algorithmsDir, algorithmNames);
    }
    else
    {
        algorithmsDir = CWD;
        handleAlgorithmArg(algorithmsDir, algorithmNames);
    }
    // Parse path to output folder
    if (vm.count(OUTPUT_OPTION))
    {
        handleOutputArg(vm[OUTPUT_OPTION].as<string>(), outputPath);
    }
    else
    {
        handleOutputArg(outputPath);
    }
    return true;
}

AlgorithmError::errorCode InputUtility::readShipPlan(const std::string& full_path_and_file_name, Plan &plan)
{
    if (!fs::exists(full_path_and_file_name))
    {
        return AlgorithmError::errorCode::BadPlanFile;
    }
    ifstream in(full_path_and_file_name);
    std::string line;
    bool first_line = true;
    int dim_x = 0, dim_y = 0, dim_z = 0;
    std::vector<string> split_line;
    int x, y, z;

    while (getline(in, line))
    {
        // Ignore lines starting with #
        if (boost::trim_left_copy(line)[0] == COMMENT) continue;
        // Treat first line differently
        if (first_line)
        {
            first_line = false;
            boost::algorithm::split(split_line, line, boost::is_any_of(DELIMETER));
            // Check if first line has number of arguments != 3
            if (split_line.size() != 3) return AlgorithmError::errorCode::BadPlanFile;

            for (auto &number : split_line)
            {
                // Check if first line has a non-number string
                if (number.find_first_not_of("0123456789") != string::npos)
                    return AlgorithmError::errorCode::BadPlanFile;
            }
            dim_z = stoi(split_line[0]);
            dim_x = stoi(split_line[1]);
            dim_y = stoi(split_line[2]);
        }
        // Not first line
        else
        {

        }
    }
}