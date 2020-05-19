//
// Created by adargut on 5/12/20.
//

#ifndef EX2_SIMPLEALGORITHM_H
#define EX2_SIMPLEALGORITHM_H

#include <string>
#include <memory>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include "../Common/AbstractAlgorithm.h"
#include "../Common/AlgorithmError.h"
#include "../Common/InputUtility.h"
#include "../Common/Ship.h"
#include "../Common/Instruction.h"
#include "../Common/Container.h"
#include "../Common/GeneralUtility.h"
#include "../Common/OutputUtility.h"
#include "../Common/DistanceToDestinationComparator.h"

using string = std::string;


class SimpleAlgorithm : public AbstractAlgorithm
{
private:
    AlgorithmError m_algorithmErrors;
    Ship m_ship;
public:
    int readShipPlan(const std::string& full_path_and_file_name) override;
    int readShipRoute(const std::string& full_path_and_file_name) override;
    int setWeightBalanceCalculator(WeightBalanceCalculator& calculator) override;
    int getInstructionsForCargo(const std::string& input_full_path_and_file_name,
                                const std::string& output_full_path_and_file_name) override;
private:
    void getInstructionsForUnloading(Instructions& instructions);
    void getInstructionForLoadingContainer(std::shared_ptr<Container> container_to_load, Instructions& instructions);
    void setRealDestinations(ContainersVector& containers);
};


#endif //EX2_SIMPLEALGORITHM_H
