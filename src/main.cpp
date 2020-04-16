#include "Utility.h"

int main() {
    const std::string &travel_name = "my_test_travel"; // TODO where to get name from? command line?
    if (Utility::start(travel_name)) return EXIT_SUCCESS;
    return EXIT_FAILURE;
}