
#include "SimulationUtility.h"

//TODO basically moved all of this to PreProcessingTasksProducer

// Checks if plan file is valid
//static bool isPlanFileValid(const string& file_path)
//{
//    Plan temp_plan;
//    AlgorithmError error = InputUtility::readShipPlan(file_path, temp_plan);
//    if(error) SimulationUtility::general_errors.emplace_back(error.errorToString() + " in " + file_path);
//    return !(error.getBit(AlgorithmError::BadPlanFile)
//             || error.getBit(AlgorithmError::ConflictingXY));
//}
//
//// Checks if route file is valid
//static bool isRouteFileValid(const string& file_path)
//{
//    Route temp_route;
//    AlgorithmError error = InputUtility::readShipRoute(file_path, temp_route);
//    if(error) SimulationUtility::general_errors.emplace_back(error.errorToString() + " in " + file_path);
//    return !(error.getBit(AlgorithmError::BadTravelFile)
//             || error.getBit(AlgorithmError::SinglePortTravel));
//}

// Checks if cargo errors occurred
//static bool reportCargoDataErrors(const string& travel_path, const string& route_file)
//{
//    std::vector<string> route;
//    InputUtility::readShipRoute(route_file, route);
//    const string& last_port = route.back();
//    std::unordered_set<string> ports_set(route.begin(), route.end());
//    std::error_code rc;
//    for (const auto &file : DirectoryIterator(travel_path, rc))
//    {
//        auto& cargo_data_file = file.path();
//        if (cargo_data_file.extension() == CARGO_SUFFIX)
//        {
//            if(!ports_set.count(cargo_data_file.filename().replace_extension("")))
//            {
//                SimulationUtility::general_errors.emplace_back(
//                        cargo_data_file.string() + " is not a part of the travel " + travel_path);
//            }
//            else
//            {
//                ports_set.erase(cargo_data_file.filename().replace_extension(""));
//                ContainersVector temp;
//                AlgorithmError error = InputUtility::readCargo(cargo_data_file, temp);
//                if (error) SimulationUtility::general_errors.emplace_back(
//                            error.errorToString() + " in " + cargo_data_file.string());
//                if(last_port == cargo_data_file.filename().replace_extension(""))
//                {
//                    if(!temp.empty()) SimulationUtility::general_errors.emplace_back(
//                                cargo_data_file.string() + " has cargo data even though it's the last port");
//                }
//            }
//        }
//    }
//    if(!ports_set.empty())
//    {
//        for (auto& port : ports_set)
//        {
//            SimulationUtility::general_errors.emplace_back(travel_path + ": Missing cargo file for " + port);
//        }
//    }
//    return true;
//}

// Handle -travel argument given by command line
// TODO mostly moved to Preprocessing, we may just need this to populate the list of paths
bool handleTravelArg(const string& travels_folder_path, std::vector<string>& travel_paths)
{
    if (!fs::exists(travels_folder_path))
    {
        SimulationUtility::general_errors.emplace_back("Bad travel_path argument");
        return false;
    }

    // Check if travel path contains both route and plan files
    std::error_code rc;
    for (const auto &entry : DirectoryIterator(travels_folder_path, rc))
    {
        bool valid_route_file = false, valid_plan_file = false, route_file_found = false, plan_file_found = false;
        if (entry.is_directory()) {
            string travel_directory = entry.path();
            string route_file;
            std::error_code rc;
            for (const auto &file : DirectoryIterator(travel_directory, rc))
            {
                if (file.path().extension() == ROUTE_SUFFIX)
                {
                    // Check route file (check validity)
                    valid_route_file = isRouteFileValid(file.path());
                    if (route_file_found)                     // Two or more route files
                    {
                        SimulationUtility::general_errors.emplace_back("Two or more route files in " + travel_directory);
                        valid_route_file = false;
                        break;
                    }
                    route_file_found = true;
                    route_file = file.path();
                }
                else if (file.path().extension() ==  PLAN_SUFFIX)
                {
                    // Check plan file (check validity)
                    valid_plan_file = isPlanFileValid(file.path());
                    if (plan_file_found)                    // Two or more plan files
                    {
                        SimulationUtility::general_errors.emplace_back("Two or more plan files in " + travel_directory);
                        valid_plan_file = false;
                        break;
                    }
                    plan_file_found = true;
                }
            }
            if (valid_plan_file && valid_route_file)
            {
                reportCargoDataErrors(travel_directory, route_file);
                travel_paths.push_back(std::move(travel_directory));
            }
        }
    }
    if(travel_paths.empty())
    {
        SimulationUtility::general_errors.emplace_back("No valid travels found");
        return false;
    }
    return true;
}

// Handles -algorithm argument given by command line
bool handleAlgorithmArg(const string& algorithmDir, std::vector<string>& algorithm_paths)
{
    if (!fs::exists(algorithmDir))
    {
        SimulationUtility::general_errors.emplace_back("Bad algorithm directory given");
        return false;
    }

    std::error_code rc;
    for (const auto& entry : DirectoryIterator(algorithmDir, rc))
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
        SimulationUtility::general_errors.emplace_back("No .so files found in algorithm directory");
        return false;
    }
    return true;
}

// Handle -output arg given by command line
static bool handleOutputArg(string& output_path)
{
    if (!fs::exists(output_path))
    {
        fs::create_directories(output_path);
    }
    return true;
}

// Handle all command line args
bool SimulationUtility::handleArgs(int argc, char **argv, std::vector<string>& travel_paths, string& algorithms_dir,
                                   std::vector<string>& algorithm_names, string& output_path)
{
    string travel_folder;
    if(!parseArgs(argc, argv, travel_folder, algorithms_dir, output_path))
    {
        return false;
    }
    // Parse path to travel folder
    // TODO make each thread call this
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

// Parse command line arg
bool SimulationUtility::parseArgs(int argc, char** argv, string& travelFolder, string& algorithmFolder, string& outputFolder)
{
    outputFolder = CWD; // temporarily set as CWD
    if(argc != 3 && argc != 5 && argc != 7)
    {
        SimulationUtility::general_errors.emplace_back("Wrong number of arguments");
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
        SimulationUtility::general_errors.emplace_back("No travel_path argument supplied");
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