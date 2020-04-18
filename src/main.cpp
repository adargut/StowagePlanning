#include "Utility.h"

int main() {
    // Name of folder where Route/Plan can be found, given by command line
    std::string travel_name;

    while (true) {
        std::cout << "Please enter the path to the input folder: \n" <<
            "## Note that the folder must contain route, plan and cargo data file ##\n";
        std::cout << "If you wish you quit the program, type in quit\n";
        std::cin >> travel_name;

        if (travel_name == "quit") break;

        if (Utility::start(travel_name)) std::cout << "Simulation completed successfully, results are now available\n";
        else std::cout << "Simulation did not run successfully\n";
    }
    return EXIT_SUCCESS;
}