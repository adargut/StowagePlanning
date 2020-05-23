#ifndef EX2_OUTPUTUTILITY_H
#define EX2_OUTPUTUTILITY_H

#include "GeneralUtility.h"
#include "Instruction.h"
#include "AlgorithmError.h"
#include "../simulator/Error.h"
#include <fstream>
#include <iostream>
#include <filesystem>

#define RESULTS "RESULTS,"
#define GENERAL_ERRORS_SUFFIX ".general_errors"
#define SIMULATION_ERRORS_SUFFIX ".crane_errors"
#define ALG_ERRORS_SUFFIX ".alg_errors"
#define LINE_SEPERATOR "=====================================================\n";
#define SUM "Sum"
#define ERRORS "Num Errors"
#define ERRORS_ALT "ERRORS,"
#define ERRORS_DIR "errors"
#define RESULTS_FILENAME "simulation.results"

namespace fs = std::filesystem;
using ifstream = std::ifstream;
using ofstream = std::ofstream;

/**
 * @brief OutputUtility.h provides useful utilities for writing to files
 * 
 */
namespace OutputUtility
{
    bool writeCargoInstructions(const string &output_full_path_and_file_name, const Instructions &instructions);
    bool writeErrors(const string &output_full_path_and_file_name, std::vector<Error> &algorithm_errors);
    bool writeAlgorithmErrors(const string &output_full_path_and_file_name, std::vector<AlgorithmError> &errors);
    bool writeResults(const string &output_full_path_and_file_name, AlgorithmTravelResultsMap &results,
                      const std::vector<string> &travels_seen);
}


#endif //OUTPUTUTILITY_H