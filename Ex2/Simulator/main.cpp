#include "../Common/InputUtility.h"

#define TRAVEL_OPTION "-travel_path"


int main(int argc, char *argv[]) {
    if (!InputUtility::cmdOptionExists(argv, argv+argc, TRAVEL_OPTION)) {
        // TODO return fatal error and make sure travel stops
    }
    std::string travel_path = InputUtility::getCmdOption(argv, argv+argc, TRAVEL_OPTION);

}