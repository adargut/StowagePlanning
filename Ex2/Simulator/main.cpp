#include "../Common/InputUtility.h"
#include "../Common/AlgorithmManager.h"
#include "../Common/AlgorithmError.h"
#include "Simulation.h"
#include "../Algorithm/SimpleAlgorithm.h"

int test_run()
{
    std::unique_ptr<AbstractAlgorithm> alg = std::make_unique<SimpleAlgorithm>();
    Simulation simulation(std::move(alg), "test_algorithm", "travel_0", "../Travels_dir/travel_0", "../test_output");
    simulation.initialize();
    std::cout << simulation.run() << std::endl;
    return 0;
}

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    // TESTS TODO REMOVE
//    cout << AlgorithmError::errorCode::SinglePortTravel << "\n";
//    std::vector<string> travel_paths;
//    string algorithmDir;
//    std::vector<string> algorithmNames;
//    string output_path;
////    string travel_path = "/Travels_dir";
//    InputUtility::handleArgs(argc, argv, travel_paths, algorithmDir, algorithmNames, output_path);
//    if(!algorithmNames.empty())
//    {
//        cout << algorithmNames[0] << "\n";
//        cout << algorithmNames[1] << "\n";
//    }
//    if(!travel_paths.empty())
//    {
//        cout << travel_paths[0] << "\n";
//    }
//    AlgorithmManager::getInstance().setAlgorithmsPath(algorithmDir);
//    AlgorithmManager::getInstance().registerAlgorithm(algorithmNames[0]);
//TODO create output dir if doesn't exist
    return test_run();
}