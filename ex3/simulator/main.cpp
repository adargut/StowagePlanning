#include "../common/InputUtility.h"
#include "../common/OutputUtility.h"
#include "../common/AlgorithmManager.h"
#include "PreProcessingTasksProducer.h"
#include "SimulationTasksProducer.h"
#include "SimulationUtility.h"
#include "Simulation.h"
#include "ThreadPoolExecutor.h"

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

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    std::cout << "-----PROGRAM STARTED------\n";

    // TODO make sure it creates out even with no algorithms
    std::vector<string> travel_paths;
    string algorithmDir;
    std::vector<string> algorithmNames;
    int num_threads;
    string output_path;
    SimulationUtility::handleArgs(argc, argv, travel_paths, algorithmDir, algorithmNames, output_path, num_threads);
    registerAlgorithms(algorithmDir, algorithmNames);

    // Preprocessing travel data
    TravelData::setOutputDir(output_path);
    std::vector<TravelData> travels_data(travel_paths.size());
    PreProcessingTasksProducer preprocessor(travel_paths.size(),travel_paths, travels_data);

    if(num_threads > 1)
    {
        ThreadPoolExecutor preprocessing_executor(std::move(preprocessor), num_threads);
        preprocessing_executor.start();
        preprocessing_executor.wait_till_finish();
    }
    else // main thread performs all tasks
    {
        while(auto task = preprocessor.getTask())
        {
            (*task)();
        }
    }

    // Create vector of <algorithm_name, travel_data> pairs to run simulations on
    ProcessedDataList processed_data_list;
    std::vector<string> valid_travels;

    for (auto& travel_data : travels_data)
    {
        // Report general errors
        for (auto &error : travel_data.getTravelErrors())
        {
            SimulationUtility::general_errors.push_back(error);
        }
        if (travel_data.isValid())
        {
            valid_travels.push_back(travel_data.getTravelName());
            for (auto &algorithm_name : algorithmNames)
            {
                processed_data_list.push_back(std::make_pair(algorithm_name, &travel_data));
            }
        }
        // No valid travels to run
        if (processed_data_list.empty())
        {
            SimulationUtility::general_errors.emplace_back("No valid travels found");
            return EXIT_SUCCESS;
        }
    }

    // Running simulations
    AlgorithmTravelResultsMap simulation_results;
    SimulationTasksProducer simulations_runner(processed_data_list.size(), processed_data_list, simulation_results);

    if(num_threads > 1)
    {
        ThreadPoolExecutor simulations_executor(std::move(simulations_runner), num_threads);
        simulations_executor.start();
        simulations_executor.wait_till_finish();
    }
    else // main thread performs all tasks
    {
        while(auto task = simulations_runner.getTask())
        {
            (*task)();
        }
    }

    // Flush results/errors into their files
    string errors_path = output_path + "/" + ERRORS_DIR;
    string general_errors_path = errors_path + "/general_errors.errors";
    OutputUtility::writeErrors(general_errors_path, SimulationUtility::general_errors);
    OutputUtility::writeResults(output_path + "/" + RESULTS_FILENAME, simulation_results, valid_travels);
    std::cout << "-----PROGRAM FINISHED------\n";
    std::cout << "See errors (if any) in " << errors_path << " and results in: " << output_path << std::endl;
    return EXIT_SUCCESS;
}