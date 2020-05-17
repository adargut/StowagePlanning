#ifndef EX2_OUTPUTUTILITY_H
#define EX2_OUTPUTUTILITY_H

#include "GeneralUtility.h"
#include "Instruction.h"
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>

#define RESULTS "RESULTS,"
#define SUM "Sum"
#define ERRORS "Num Errors"

namespace fs = std::filesystem;
using ifstream = std::ifstream;
using ofstream = std::ofstream;


namespace OutputUtility
{
    bool writeCargoInstructions(const string &output_full_path_and_file_name, const Instructions &instructions);
    bool OutputUtility::writeSimulationResults(const string &output_full_path_and_file_name, const string &travel_name, const string &algorithm_name, 
                                               int sum, int num_errors);
}


#endif //OUTPUTUTILITY_H