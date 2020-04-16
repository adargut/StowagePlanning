#include "Utility.h"

int main() {
    // Name of folder where Route/Plan can be found, given by command line
    std::string travel_name;
    std::cin >> travel_name;

    if (Utility::start(travel_name)) return EXIT_SUCCESS;
    return EXIT_FAILURE;
}