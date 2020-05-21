#include "InputUtility.h"
#include "Container.h"

bool verifyPortSymbol(const string& line)
{
    if(line.length() != 5) return false;
    for (auto& c : line)
    {
        if (!(c <= 'Z' && c >= 'A')) return false;
    }
    return true;
}

bool verifyISO6346(const std::string& port_name)
{
    return ISO_6346::isValidId(port_name);
}

bool isPlanFileValid(const string& file_path)
{
    Plan temp_plan;
    AlgorithmError error = InputUtility::readShipPlan(file_path, temp_plan);
    InputUtility::input_errors.emplace_back(error.errorToString() + " in " + file_path);
    return !(error.getBit(AlgorithmError::BadPlanFile)
       || error.getBit(AlgorithmError::ConflictingXY));
}

bool isRouteFileValid(const string& file_path)
{
    Route temp_route;
    AlgorithmError error = InputUtility::readShipRoute(file_path, temp_route);
    InputUtility::input_errors.emplace_back(error.errorToString() + " in " + file_path);
    return !(error.getBit(AlgorithmError::BadTravelFile)
             || error.getBit(AlgorithmError::SinglePortTravel));
}

bool handleTravelArg(const string& travel_path, std::vector<string>& travel_paths) 
{
    if (!fs::exists(travel_path)) 
    {
        std::cout << "Error: could not run travel, bad travel_path argument\n";
        InputUtility::input_errors.emplace_back("Could not run travel, bad travel_path argument");
        return false;
    }

    // Check if travel path contains both route and plan files
    for (const auto &entry : DirectoryIterator(travel_path)) 
    {
        bool valid_route_file = false, valid_plan_file = false, route_file_found = false, plan_file_found = false;
        if (entry.is_directory()) {
            string travel_directory = entry.path();
            for (const auto &file : DirectoryIterator(travel_directory))
            {
                if (file.path().extension() == ROUTE_SUFFIX)
                {
                    // Check route file (check validity)
                    valid_route_file = isRouteFileValid(file.path());
                    if (route_file_found)                     // Two or more route files
                    {
                        std::cout << "Error: Two or more route files\n";
                        InputUtility::input_errors.emplace_back("Two or more route files in " + travel_path);
                        valid_route_file = false;
                        break;
                    }
                    route_file_found = true;
                }
                else if (file.path().extension() ==  PLAN_SUFFIX)
                {
                    // Check plan file (check validity)
                    valid_plan_file = isPlanFileValid(file.path());
                    if (plan_file_found)                    // Two or more plan files
                    {
                        std::cout << "Error: Two or more plan files\n";
                        InputUtility::input_errors.emplace_back("Two or more plan files in " + travel_path);
                        valid_plan_file = false;
                        break;
                    }
                    plan_file_found = true;
                }
            }
            if (valid_plan_file && valid_route_file)
            {
                // TODO Check all ports exist in route....
                travel_paths.push_back(std::move(travel_directory));
            }
        }
    }
    if(travel_paths.empty())
    {
        std::cout << "No valid travels found\n";
        InputUtility::input_errors.emplace_back("No valid travels found");
        return false;
    }
    return true;
}

bool handleAlgorithmArg(const string& algorithmDir, std::vector<string>& algorithm_paths)
{
    if (!fs::exists(algorithmDir))
    {
        std::cout << "Error: bad algorithm directory given\n";
        InputUtility::input_errors.emplace_back("Bad algorithm directory given");
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
    if (algorithm_paths.empty())
    {
        std::cout << "Error: no .so found files in algorithm directory\n";
        InputUtility::input_errors.emplace_back("No .so found files in algorithm directory");
        return false;
    }
    return true;
}

static bool handleOutputArg(string& output_path)
{
    if (!fs::exists(output_path))
    {
        fs::create_directories(output_path);
    }
    return true;
}

bool InputUtility::handleArgs(int argc, char **argv, std::vector<string>& travel_paths, string& algorithms_dir,
                         std::vector<string>& algorithm_names, string& output_path)
{
    string travel_folder;
    if(!parseArgs(argc, argv, travel_folder, algorithms_dir, output_path))
    {
        return false;
    }
    // Parse path to travel folder
    if(!handleTravelArg(travel_folder, travel_paths))
    {
        return false;
    }
    // Parse path to output folder
    handleOutputArg(output_path);
    // Parse path to algorithm folder
    handleAlgorithmArg(algorithms_dir, algorithm_names);
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
        if (number.find_first_not_of("0123456789") != string::npos) 
        {
            return false;
        }
    }
    return true;
}

AlgorithmError InputUtility::readShipPlan(const std::string& full_path_and_file_name, Plan &plan)
{
    // Store accumulated errors
    AlgorithmError errors;
    // Store previous positions found for error checking
    std::map<pos, int> previous_positions{};

    if (!fs::exists(full_path_and_file_name))
    {
        errors.setBit(AlgorithmError::errorCode::BadPlanFile);
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
        split_line.clear();
        // Ignore lines starting with #
        if (line.empty() || line[0] == COMMENT) continue;
        // Split line by "," delimeter
        GeneralUtility::split(split_line, line, DELIMETER);
        GeneralUtility::removeLeadingAndTrailingSpaces(split_line);
        // Treat first line differently
        if (first_line)
        {
            first_line = false;
            // First line MUST have correct format
            if (!verifyPlanLineFormat(split_line))
            {
                std::cout << "Error: Badly formatted first line in plan file\n";
                errors.setBit(AlgorithmError::errorCode::BadPlanFile);
                return errors;
            }

            dim_z = stoi(split_line[0]);
            dim_x = stoi(split_line[1]);
            dim_y = stoi(split_line[2]);
            if (dim_x < 1 || dim_y < 1 || dim_z < 1)
            {
                std::cout << "Error: Badly formatted first line in plan file\n";
                errors.setBit(AlgorithmError::errorCode::BadPlanFile);
                return errors;
            }
            plan = std::vector<std::vector<std::vector<std::string>>>
                    (dim_z, std::vector<std::vector<std::string>>
                            (dim_y, std::vector<std::string>(dim_x, FREE_POS)));
        }
        // Not first line
        else
        {
            // Line has bad format, we ignore it
            if (!verifyPlanLineFormat(split_line))
            {
                std::cout << "Ignored badly formatted line in plan file\n";
                errors.setBit(AlgorithmError::errorCode::BadLineFormatOrDuplicateXY);
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
                    std::cout << "Error: Conflicting redefinition of X,Y\n";
                    errors.setBit(AlgorithmError::errorCode::ConflictingXY);
                    return errors;
                }
                std::cout << "Error: Non-conflicting redefinition of X,Y\n";
                errors.setBit(AlgorithmError::errorCode::BadLineFormatOrDuplicateXY);
                continue;
            }
            // Floor is too high
            if (z > dim_z)
            {
                std::cout << "Error: Floor value exceeding ship's dimensions\n";
                errors.setBit(AlgorithmError::errorCode::ExceedingFloorValue);
                continue;
            }
            if (x >= dim_x || y >= dim_y || x < 0 || y < 0)
            {
                std::cout << "Error: X, Y values exceeding ship's dimensions\n";
                errors.setBit(AlgorithmError::errorCode::ExceedingXYValue);
                continue;
            }

            for (int i = 0; i < z; i++)
            {
                plan[i][y][x] = ILLEGAL_POS;
            }
        }
    }
    if(first_line)
    {
        std::cout << "Error: Empty plan file\n";
        errors.setBit(AlgorithmError::errorCode::BadPlanFile);
    }
    return errors;
}

AlgorithmError InputUtility::readCargo(const string &full_path_and_file_name, ContainersVector &containers_to_load)
{
    AlgorithmError errors;
    if (!fs::exists(full_path_and_file_name))
    {
        errors.setBit(AlgorithmError::errorCode::BadCargoFile);
        return errors;
    }
    ifstream in(full_path_and_file_name);
    string line;
    while (getline(in, line))
    {
        if (line[0] == COMMENT) continue;
        std::vector<string> split_line;
        GeneralUtility::split(split_line, line, DELIMETER);
        GeneralUtility::removeLeadingAndTrailingSpaces(split_line);
        int bound = split_line.size();
        auto container = std::make_shared<Container>();
        // ID
        if (bound > 0)
        {
            string& id = split_line[0];
            if (!verifyISO6346((id)))
            {
                errors.setBit(AlgorithmError::BadContainerID);
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
    return errors;
}

string InputUtility::getFileName(const string &full_path_and_file_name)
{
    std::filesystem::path p = full_path_and_file_name;
    p = p.filename();
    p.replace_extension();
    return p.string();
}

AlgorithmError InputUtility::readShipRoute(const std::string& full_path_and_file_name, Route& route)
{
    std::unordered_map<string, int> port_map;
    // Store accumulated errors
    AlgorithmError errors;

    if (!fs::exists(full_path_and_file_name))
    {
        errors.setBit(AlgorithmError::errorCode::BadTravelFile);
        return errors;
    }
    ifstream in(full_path_and_file_name);
    std::string line;

    while (getline(in, line))
    {
        GeneralUtility::trim(line);
        if (line.empty() || line[0] == COMMENT) continue;
        // Same port appearing twice in a row
        if (!route.empty() && route.back() == line)
        {
            errors.setBit(AlgorithmError::errorCode::SamePortConsecutively);
            continue;
        }
        // Incorrect port symbol formatting
        if (!verifyPortSymbol(line))
        {
            errors.setBit(AlgorithmError::errorCode::BadPortSymbol);
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
        errors.setBit(AlgorithmError::errorCode::SinglePortTravel);
    }
    // Route cannot be empty
    if (route.size() == 0)
    {
        errors.setBit(AlgorithmError::errorCode::BadTravelFile);
    }
    return errors;
}

bool InputUtility::readCraneInstructions(const string& full_path_and_file_name, Instructions& instructions)
{
    if (!fs::exists(full_path_and_file_name))
    {
        std::cout << "Failed reading crane instructions" << std::endl;
        return false;
    }

    ifstream in(full_path_and_file_name);
    std::string line;

    while (getline(in, line))
    {
        if ((line)[0] == COMMENT) continue;
        std::vector<string> split_line;
        GeneralUtility::split(split_line, line, DELIMETER);
        GeneralUtility::removeLeadingAndTrailingSpaces(split_line);
        if(split_line.size() < 2) return false;
        string& container_id = split_line[1];
        if(split_line[0] == "R")
        {
            instructions.emplace_back(Instruction::Reject, container_id);
            continue;
        }
        else if (split_line.size() < 5) return false;
        if(split_line[2].find_first_not_of("0123456789") != string::npos) return false;
        int z = stoi(split_line[2]);
        if(split_line[3].find_first_not_of("0123456789") != string::npos) return false;
        int x = stoi(split_line[3]);
        if(split_line[4].find_first_not_of("0123456789") != string::npos) return false;
        int y = stoi(split_line[4]);
        if(split_line[0] == "L")
        {
            instructions.emplace_back(Instruction::Load, container_id, z, y, x);
            continue;
        }
        if(split_line[0] == "U")
        {
            instructions.emplace_back(Instruction::Unload, container_id, z, y, x);
            continue;
        }
        if(split_line[0] == "M")
        {
            if(split_line.size() < 8) return false;
            if(split_line[5].find_first_not_of("0123456789") != string::npos) return false;
            int new_z = stoi(split_line[5]);
            if(split_line[6].find_first_not_of("0123456789") != string::npos) return false;
            int new_x = stoi(split_line[6]);
            if(split_line[7].find_first_not_of("0123456789") != string::npos) return false;
            int new_y = stoi(split_line[7]);
            instructions.emplace_back(Instruction::Move, container_id, z, y, x, new_z, new_y, new_x);
            continue;
        }
        return false;
    }
    return true;
}

bool InputUtility::parseArgs(int argc, char** argv, string& travelFolder, string& algorithmFolder, string& outputFolder)
{
    outputFolder = CWD; // temporarily set as CWD
    if(argc != 3 && argc != 5 && argc != 7)
    {
        std::cout << "Wrong number of arguments\n";
        input_errors.emplace_back("Wrong number of arguments");
        return false;
    }
    std::unordered_map<string, string> arg_map;
    for (int i = 1; i < argc; i+=2)
    {
        if(arg_map.count(argv[i])) return false; // Same argument passed twice, TODO check if correct behaviour
        arg_map[argv[i]] = argv[i+1];
    }

    if(arg_map.count(TRAVEL_OPTION))
    {
        travelFolder = arg_map[TRAVEL_OPTION];
    } else
    {
        std::cout << "No travel_path argument supplied\n";
        input_errors.emplace_back("No travel_path argument supplied");
        return false;
    }
    if(arg_map.count(ALGORITHM_OPTION))
    {
        algorithmFolder = arg_map[ALGORITHM_OPTION];
    }
    else
    {
        algorithmFolder = CWD;
    }
    if(arg_map.count(OUTPUT_OPTION))
    {
        outputFolder = arg_map[OUTPUT_OPTION];
    }
    else
    {
        outputFolder = CWD;
    }
    return true;
}
