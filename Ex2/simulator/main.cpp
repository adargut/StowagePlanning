#include "../common/InputUtility.h"
#include "../common/OutputUtility.h"
#include "../common/AlgorithmManager.h"
#include "SimulationUtility.h"
#include "Simulation.h"

std::vector<Error> SimulationUtility::general_errors;

int registerAlgorithms(const string& algorithmDir, const std::vector<string>& algorithmNames)
{
    AlgorithmManager::getInstance().setAlgorithmsPath(algorithmDir);
    for (auto& algorithmName : algorithmNames)
    {
        if(!AlgorithmManager::getInstance().registerAlgorithm(algorithmName))
        {
            std::cout << algorithmName << " failed to register\n";
            SimulationUtility::general_errors.emplace_back(algorithmName + " failed to register");
        }
    }
    return 0;
}

int runSimulations(std::vector<string>& travelPaths, std::vector<string>& algorithmNames, string& outputPath)
{
    std::vector<string> travelNames;
    // Initialize vector of travel names
    for (auto& travel : travelPaths)
    {
        string travelName = std::filesystem::path(travel).filename();
        travelNames.push_back(std::move(travelName));
    }
    AlgorithmTravelResultsMap resultsMap;
    for (auto& algorithmName : algorithmNames)
    {
        for (auto& travel : travelPaths)
        {
            string travelName = std::filesystem::path(travel).filename();
            auto algorithm = AlgorithmManager::getInstance().getAlgorithmInstance(algorithmName);
            if(algorithm == nullptr) continue; // algorithm didn't register
            Simulation simulation(std::move(algorithm), algorithmName, travelName, travel, outputPath);
            simulation.initialize();
            if(!resultsMap.count(algorithmName)) resultsMap[algorithmName] = std::vector<string>();
            resultsMap[algorithmName].push_back(std::to_string(simulation.run()));
        }
    }
    OutputUtility::writeResults(outputPath + "/" + RESULTS_FILENAME, resultsMap, travelNames);
    return 0;
}

int test_run()
{
//    std::unique_ptr<AbstractAlgorithm> alg = std::make_unique<RandomAlgorithm>();
//    Simulation simulation(std::move(alg), "test_algorithm", "travel_0", "../Travels_dir/travel_0", "../test_output");
//    simulation.initialize();
//    AlgorithmTravelResultsMap resultsMap;
//    std::vector<string> travelNames = {"travel_0"};
//    resultsMap["test_algorithm"] = std::vector<string>();
//    resultsMap["test_algorithm"].push_back(std::to_string(simulation.run()));
//    //OutputUtility::writeResults("./test_output", resultsMap, travelNames);
    return 0;
}

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    std::cout << "-----PROGRAM STARTED------\n";
    std::vector<string> travel_paths;
    string algorithmDir;
    std::vector<string> algorithmNames;
    string output_path;
    SimulationUtility::handleArgs(argc, argv, travel_paths, algorithmDir, algorithmNames, output_path);
    registerAlgorithms(algorithmDir, algorithmNames);
    runSimulations(travel_paths, algorithmNames, output_path);
    string errors_path = output_path + "/" + ERRORS_DIR;
    string general_errors_path = errors_path + "/general_errors.errors";
    //TODO https://moodle.tau.ac.il/mod/forum/discuss.php?d=98197
    OutputUtility::writeErrors(general_errors_path, SimulationUtility::general_errors);
    std::cout << "-----PROGRAM FINISHED------\n";
    std::cout << "See errors (if any) in " << errors_path << " and results in: " << output_path << std::endl;
    return 0;
}