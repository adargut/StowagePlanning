#include "InputUtility.h"
#include "Container.h"
// TODO handle mid line spaces

bool verifyPortSymbol(const string& line)
{
    (void)(line);
    return true;
}

bool verifyISO6346(const std::string& port_name)
{
    // TODO implement me
    if (!port_name.empty())
    {
        return true;
    }
    return false;
}

bool handleTravelArg(const string& travel_path, std::vector<string>& travel_paths) {
    if (!fs::exists(travel_path)) {
        // TODO return fatal error and make sure travel stops
        return false;
    }

    // Check if travel path contains both route and plan files
    for (const auto &entry : DirectoryIterator(travel_path)) {
        bool valid_route_file = false, valid_plan_file = false;
        if (entry.is_directory()) {
            string travel_directory = entry.path();
            for (const auto &file : DirectoryIterator(travel_directory)) {
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
//    for (const auto& entry : DirectoryIterator(travel_path))
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

    for (const auto& entry : DirectoryIterator(algorithmDir))
    {
        std::filesystem::path p = entry.path();
        if (p.extension() == SO_SUFFIX)
        {
            p = p.filename();
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
InputUtility::handleArgs(int argc, char **argv, std::vector<string> &travel_paths, string algorithms_dir,
                         std::vector<string> &algorithm_names, string &output_path)
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
        algorithms_dir = vm[ALGORITHM_OPTION].as<string>();
        handleAlgorithmArg(algorithms_dir, algorithm_names);
    }
    else
    {
        algorithms_dir = CWD;
        handleAlgorithmArg(algorithms_dir, algorithm_names);
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

bool verifyPlanLineFormat(const std::vector<string>& line)
{
    // Check if line has number of arguments != 3
    if (line.size() != 3)
    {
        return false;
    }

    // Check if line has a non-number string
    for (auto &number : line)
    {
        // Check if first line has a non-number string
        if (number.find_first_not_of("0123456789") != string::npos) {
            return false;
        }
    }
    return true;
}

ErrorSet InputUtility::readShipPlan(const std::string& full_path_and_file_name, Plan &plan)
{
    // Store accumulated errors
    ErrorSet errors;
    // Store previous positions found for error checking
    std::map<pos, int> previous_positions{};

    if (!fs::exists(full_path_and_file_name))
    {
        errors.insert(AlgorithmError::errorCode::BadPlanFile);
        return errors;
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
        // Split line by ", " delimeter
        boost::algorithm::split(split_line, line, boost::is_any_of(DELIMETER));
        // Treat first line differently
        if (first_line)
        {
            first_line = false;
            // First line MUST have correct format
            if (!verifyPlanLineFormat(split_line))
            {
                errors.insert(AlgorithmError::errorCode::BadPlanFile);
                return errors;
            }

            dim_z = stoi(split_line[0]);
            dim_x = stoi(split_line[1]);
            dim_y = stoi(split_line[2]);
        }
        // Not first line
        else
        {
            // Line has bad format, we ignore it
            if (!verifyPlanLineFormat(split_line))
            {
                errors.insert(AlgorithmError::errorCode::BadLineFormatOrDuplicateXY);
                continue;
            }
            x = stoi(split_line[0]);
            y = stoi(split_line[1]);
            z = stoi(split_line[2]);

            // Error handling
            pos new_pos = std::make_pair(x, y);
            if (previous_positions.count(new_pos) > 0)
            {
                if (previous_positions[new_pos] != z)
                {
                    // Conflicting redefinition of X,Y so we quit
                    errors.insert(AlgorithmError::errorCode::ConflictingXY);
                    return errors;
                }
                // Non-conflicting redefinition of X,Y so we ignore
                errors.insert(AlgorithmError::errorCode::BadLineFormatOrDuplicateXY);
                continue;
            }
            // Floor is too high
            if (z >= dim_z)
            {
                errors.insert(AlgorithmError::errorCode::ExceedingFloorValue);
                continue;
            }
            // X,Y dimensions are incorrect
            if (x > dim_x || y > dim_y || x < 0 || y < 0)
            {
                errors.insert(AlgorithmError::errorCode::ExceedingXYValue);
                continue;
            }

            for (int i = 0; i < z; i++)
            {
                plan[i][y][x] = ILLEGAL_POS;
            }
        }
    }
    return errors;
}

ErrorSet InputUtility::readCargo(const string &full_path_and_file_name, ContainersVector &containers_to_load)
{
    ErrorSet errors;
    if (!fs::exists(full_path_and_file_name))
    {
        errors.insert(AlgorithmError::errorCode::BadCargoFile);
        return errors;
    }
    ifstream in(full_path_and_file_name);
    string line;
    while (getline(in, line))
    {
        if (boost::trim_left_copy(line)[0] == COMMENT) continue;
        std::vector<string> split_line;
        boost::algorithm::split(split_line, line, boost::is_any_of(DELIMETER));
        int bound = std::min<int>(2, split_line.size());
        auto container = std::make_shared<Container>();
        // ID
        if (bound > 0)
        {
            string& id = split_line[0];
            if (!verifyISO6346((id)))
            {
                errors.insert(AlgorithmError::errorCode::BadPortID);
                continue;
            }
            container->setId(id);
        }
        // Weight
        if (bound > 1)
        {
            if (!(split_line[1].empty() || split_line[1].find_first_not_of("0123456789") != string::npos))
            {
                int weight = stoi(split_line[1]);
                if (weight >= 0)
                {
                    container->setWeight(weight);
                }
            }
        }
        // Destination
        if (bound > 2)
        {
            container->setPortCode(split_line[2]);
        }
        containers_to_load.push_back(container);
    }
    return ErrorSet();
}

string InputUtility::getFileName(const string &full_path_and_file_name)
{
    std::filesystem::path p = full_path_and_file_name;
    p = p.filename();
    p.replace_extension();
    return p.string();
}

ErrorSet InputUtility::readShipRoute(const std::string& full_path_and_file_name, Route& route)
{
    std::unordered_map<string, int> port_map;
    // Store accumulated errors
    ErrorSet errors;

    if (!fs::exists(full_path_and_file_name))
    {
        errors.insert(AlgorithmError::errorCode::BadTravelFile);
        return errors;
    }
    ifstream in(full_path_and_file_name);
    std::string line;

    while (getline(in, line))
    {
        // Same port appearing twice in a row
        if (!route.empty() && route.back() == line)
        {
            errors.insert(AlgorithmError::errorCode::SamePortConsecutively);
            continue;
        }
        // Incorrect port symbol formatting
        if (!verifyPortSymbol(line))
        {
            errors.insert(AlgorithmError::errorCode::BadPortSymbol);
            continue;
        }
        if (port_map.count(line))
        {
            int curr_idx = port_map[line];
            line.append(UNDERSCORE + std::to_string(curr_idx+1));
            port_map[line] += 1;
        } else
        {
            port_map[line] = 1;
            line.append(UNDERSCORE + std::to_string(1));
        }
        route.push_back(line);
    }
    // Route must have length > 1
    if (route.size() == 1)
    {
        errors.insert(AlgorithmError::errorCode::SinglePortTravel);
    }
    // Route cannot be empty
    if (route.size() == 0)
    {
        errors.insert(AlgorithmError::errorCode::BadTravelFile);
    }
    return errors;
}