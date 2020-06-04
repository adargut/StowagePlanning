#include "InputUtility.h"
#include "Container.h"

// Checks port symbol is legal
bool verifyPortSymbol(const string& line)
{
    if(line.length() != 5) return false;
    for (auto& c : line)
    {
        if (!(c <= 'Z' && c >= 'A')) return false;
    }
    return true;
}

// Checks conforming to ISO6346 
bool verifyISO6346(const std::string& port_name)
{
    return ISO_6346::isValidId(port_name);
}

// Check line of plan is valid
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

// Utility for reading ship plan
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
                errors.setBit(AlgorithmError::errorCode::BadPlanFile);
                return errors;
            }

            dim_z = stoi(split_line[0]);
            dim_x = stoi(split_line[1]);
            dim_y = stoi(split_line[2]);
            if (dim_x < 1 || dim_y < 1 || dim_z < 1)
            {
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
                    errors.setBit(AlgorithmError::errorCode::ConflictingXY);
                    return errors;
                }
                errors.setBit(AlgorithmError::errorCode::BadLineFormatOrDuplicateXY);
                continue;
            }
            // Floor is too high
            if (z > dim_z || z < 0)
            {
                errors.setBit(AlgorithmError::errorCode::ExceedingFloorValue);
                continue;
            }
            if (x >= dim_x || y >= dim_y || x < 0 || y < 0)
            {
                errors.setBit(AlgorithmError::errorCode::ExceedingXYValue);
                continue;
            }

            for (int i = 0; i < dim_z-z; i++)
            {
                plan[i][y][x] = ILLEGAL_POS;
            }
            previous_positions[new_pos] = z;
        }
    }
    if(first_line)
    {
        errors.setBit(AlgorithmError::errorCode::BadPlanFile);
    }
    return errors;
}

// Utility for reading cargo from file
AlgorithmError InputUtility::readCargo(const string &full_path_and_file_name, ContainersVector &containers_to_load)
{
    //TODO check and report same ID appearing twice
    AlgorithmError errors;
    std::unordered_set<string> seen_ids;
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
        if(!split_line.empty() && split_line[0].empty()) continue; // Empty line
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
            if(seen_ids.count(id))
            {
                errors.setBit(AlgorithmError::DuplicateContainerOnPort);
            } else
            {
                seen_ids.insert(id);
            }
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

// Get file name
string InputUtility::getFileName(const string &full_path_and_file_name)
{
    std::filesystem::path p = full_path_and_file_name;
    p = p.filename();
    p.replace_extension();
    return p.string();
}

// Utility for reading ship route
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
        if (!route.empty() && route.back().substr(0, 5) == line)
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

// Utility for reading crane instructions
bool InputUtility::readCraneInstructions(const string& full_path_and_file_name, Instructions& instructions)
{
    if (!fs::exists(full_path_and_file_name))
    {
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
        if (split_line[2].find_first_not_of("0123456789") != string::npos) return false;
        int z = stoi(split_line[2]);
        if (split_line[3].find_first_not_of("0123456789") != string::npos) return false;
        int x = stoi(split_line[3]);
        if (split_line[4].find_first_not_of("0123456789") != string::npos) return false;
        int y = stoi(split_line[4]);
        if (split_line[0] == "L")
        {
            instructions.emplace_back(Instruction::Load, container_id, z, y, x);
            continue;
        }
        if (split_line[0] == "U")
        {
            instructions.emplace_back(Instruction::Unload, container_id, z, y, x);
            continue;
        }
        if (split_line[0] == "M")
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


