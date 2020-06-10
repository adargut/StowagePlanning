#include "../common/InputUtility.h"
#include "../common/OutputUtility.h"
#include "../common/AlgorithmManager.h"
#include "SimulationUtility.h"
#include "Simulation.h"

std::vector<Error> SimulationUtility::general_errors;

// Register the .so file
int registerAlgorithms(const string& algorithmDir, const std::vector<string>& algorithmNames)
{
    AlgorithmManager::getInstance().setAlgorithmsPath(algorithmDir);
    for (auto& algorithmName : algorithmNames)
    {
        if(!AlgorithmManager::getInstance().registerAlgorithm(algorithmName))
        {
            SimulationUtility::general_errors.emplace_back(algorithmName + " failed to register");
        }
    }
    return 0;
}

// Run all <travel, algorithm> pairs
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
    for (auto& algorithmName : algorithmNames) {
        for (auto &travel : travelPaths) {
            (void) algorithmName;
            (void) travel;
            // TODO delete this, moved to SimulationProducer...
//            string travelName = std::filesystem::path(travel).filename();
//            auto algorithm = AlgorithmManager::getInstance().getAlgorithmInstance(algorithmName);
//            if(algorithm == nullptr) continue; // algorithm didn't register
//            Simulation simulation(std::move(algorithm), algorithmName, <#initializer#>);
//            simulation.initialize();
//            if(!resultsMap.count(algorithmName)) resultsMap[algorithmName] = std::vector<string>();
//            std::cout << "\tRunning travel " << travelName << " using algorithm " << algorithmName << std::endl;
//            resultsMap[algorithmName].push_back(std::to_string(simulation.run()));
//            std::cout << "\t\tFINISHED!\n";
//        }
//    }
        }
    }
    OutputUtility::writeResults(outputPath + "/" + RESULTS_FILENAME, resultsMap, travelNames);
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
    // TODO make each thread preprocess a single travel from unprocessed travels queue, processes it, and if it's valid,
    //  it stores the data of plan/travel/cargo in a designated data structure, then wait for second function if queue is empty,
    //  else preprocess another unprocessed travel
    // TODO once all travels are processed, wake up all sleeping threads (using condition variable, condition will be counter of travels processed reaching number of travels)
    //  then let threads run a <travel, algorithm> pair from the queue: do this until the queue empties out and join them together
    runSimulations(travel_paths, algorithmNames, output_path);
    string errors_path = output_path + "/" + ERRORS_DIR;
    string general_errors_path = errors_path + "/general_errors.errors";
    OutputUtility::writeErrors(general_errors_path, SimulationUtility::general_errors);
    std::cout << "-----PROGRAM FINISHED------\n";
    std::cout << "See errors (if any) in " << errors_path << " and results in: " << output_path << std::endl;
    return EXIT_SUCCESS;
}