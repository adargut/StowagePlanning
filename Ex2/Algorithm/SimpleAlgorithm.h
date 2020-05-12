//
// Created by adargut on 5/12/20.
//

#ifndef EX2_SIMPLEALGORITHM_H
#define EX2_SIMPLEALGORITHM_H

#include "../Common/AbstractAlgorithm.h"
#include "../Common/AlgorithmError.h"
#include "../Common/Ship.h"
#include <string>
#include <memory>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>

using string = std::string;


class SimpleAlgorithm : public AbstractAlgorithm
{
private:
    string m_algorithmName;
    AlgorithmError m_algorithmErrors;
    std::unique_ptr<Ship> m_ship;
public:
    int readShipPlan(const std::string& full_path_and_file_name) override;
    int readShipRoute(const std::string& full_path_and_file_name) override;
    int setWeightBalanceCalculator(WeightBalanceCalculator& calculator) override;
    int getInstructionsForCargo(const std::string& input_full_path_and_file_name,
                                const std::string& output_full_path_and_file_name) override;
};


#endif //EX2_SIMPLEALGORITHM_H
