
#ifndef EX2_SIMULATIONUTILITY_H
#define EX2_SIMULATIONUTILITY_H
#include "../common/GeneralUtility.h"
#include "../common/InputUtility.h"

/**
 * @brief SimulationUtility.h provides utility function for the use of the simulation
 * 
 */
namespace SimulationUtility
{
    extern std::vector<Error> general_errors; // Errors regarding input provided by user
    // TODO add another argument for number of threads involved
    bool handleArgs(int argc, char **argv, std::vector<string> &travel_paths, string& algorithms_dir,
                    std::vector<string> &algorithm_names, string &output_path);
    bool parseArgs(int argc, char **argv, string& travelFolder, string& algorithmFolder, string& outputFolder);
}


#endif //EX2_SIMULATIONUTILITY_H
