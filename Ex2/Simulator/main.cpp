#include "../Common/InputUtility.h"


int main(int argc, char** argv)
{
    // TESTS TODO REMOVE
    std::vector<string> travel_paths;
    std::vector<string> algorithm_paths;
    string output_path;
//    string travel_path = "/Test_Travel";
    InputUtility::handleArgs(argc, argv, travel_paths, algorithm_paths, output_path);
    if(!algorithm_paths.empty())
    {
        cout << algorithm_paths[0] << "\n";
        cout << algorithm_paths[1] << "\n";
    }
    if(!travel_paths.empty())
    {
        cout << travel_paths[0] << "\n";
    }
}