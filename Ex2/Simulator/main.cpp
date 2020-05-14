#include "../Common/InputUtility.h"
#include "../Common/AlgorithmManager.h"
#include "../Common/AlgorithmError.h"

int main(int argc, char** argv)
{
    // TESTS TODO REMOVE
    cout << AlgorithmError::errorCode::SinglePortTravel << "\n";
    std::vector<string> travel_paths;
    string algorithmDir;
    std::vector<string> algorithmNames;
    string output_path;
//    string travel_path = "/Test_Travel";
    InputUtility::handleArgs(argc, argv, travel_paths, algorithmDir, algorithmNames, output_path);
    if(!algorithmNames.empty())
    {
        cout << algorithmNames[0] << "\n";
        cout << algorithmNames[1] << "\n";
    }
    if(!travel_paths.empty())
    {
        cout << travel_paths[0] << "\n";
    }
    AlgorithmManager::getInstance().setAlgorithmsPath(algorithmDir);
    AlgorithmManager::getInstance().registerAlgorithm(algorithmNames[0]);

}