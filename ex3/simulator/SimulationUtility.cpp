
#include "SimulationUtility.h"

// Handle -travel argument given by command line
bool handleTravelArg(const string& travels_folder_path, std::vector<string>& travel_paths)
{
    if (!fs::exists(travels_folder_path))
    {
        SimulationUtility::general_errors.emplace_back("Bad travel_path argument");
        return false;
    }

    // Populate travels_folder with all travel_paths
    std::error_code rc;
    for (const auto &entry : DirectoryIterator(travels_folder_path, rc))
    {
        if (entry.is_directory())
        {
            string travel_directory = entry.path();
            travel_paths.push_back(std::move(travel_directory));
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
        if(arg_map.count(argv[i])) return false; // Same argument passed twice
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