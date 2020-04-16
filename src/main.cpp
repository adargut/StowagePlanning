#include "Utility.h"

int main() {
    std::string travel_name;
    std::cin >> travel_name;
    if (Utility::start(travel_name)) return EXIT_SUCCESS;
    return EXIT_FAILURE;
}