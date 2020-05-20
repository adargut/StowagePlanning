#include "../Common/InputUtility.h"
#include "../Common/OutputUtility.h"
#include "../Common/AlgorithmManager.h"
#include "../Common/AlgorithmError.h"
#include "../Common/GeneralUtility.h"
#include "Simulation.h"

int registerAlgorithms(const string& algorithmDir, const std::vector<string>& algorithmNames)
{
    AlgorithmManager::getInstance().setAlgorithmsPath(algorithmDir);
    for (auto& algorithmName : algorithmNames)
    {
        if(!AlgorithmManager::getInstance().registerAlgorithm(algorithmName))
        {
            // TODO maybe handle?
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
            if(!simulation.initialize())
            {
                // TODO handle
            }
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
    std::vector<string> travel_paths;
    string algorithmDir;
    std::vector<string> algorithmNames;
    string output_path;
    InputUtility::handleArgs(argc, argv, travel_paths, algorithmDir, algorithmNames, output_path);
    registerAlgorithms(algorithmDir, algorithmNames);
    runSimulations(travel_paths, algorithmNames, output_path);
    return 0;
}