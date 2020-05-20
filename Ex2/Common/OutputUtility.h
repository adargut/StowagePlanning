#ifndef EX2_OUTPUTUTILITY_H
#define EX2_OUTPUTUTILITY_H

#include "GeneralUtility.h"
#include "Instruction.h"
#include "../Simulator/Error.h"
#include <fstream>
#include <iostream>
#include <filesystem>

#define RESULTS "RESULTS,"
#define SUM "Sum"
#define ERRORS "Num Errors"
#define ERRORS_ALT "ERRORS,"
#define RESULTS_FILENAME "simulation.results"

namespace fs = std::filesystem;
using ifstream = std::ifstream;
using ofstream = std::ofstream;


namespace OutputUtility
{
    bool writeCargoInstructions(const string &output_full_path_and_file_name, const Instructions &instructions);
    bool writeErrors(const string &output_full_path_and_file_name, std::vector<Error> &algorithm_errors);
    bool writeResults(const string &output_full_path_and_file_name, AlgorithmTravelResultsMap &results,
                      const std::vector<string> &travels_seen);
}


#endif //OUTPUTUTILITY_H