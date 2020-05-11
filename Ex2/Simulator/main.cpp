#include "../Common/InputUtility.h"


int main(int argc, char** argv)
{
    // TESTS TODO REMOVE
    string route;
    string plan;
    std::vector<string> algorithm_paths;
    string output_path;
//    string travel_path = "/Test_Travel";
    InputUtility::handleArgs(argc, argv, route, plan, algorithm_paths, output_path);
    cout << route << "\n";
    cout << plan << "\n";
}