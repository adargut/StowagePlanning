//
// Created by adargut on 5/12/20.
//

#include "SimpleAlgorithm.h"

int SimpleAlgorithm::readShipPlan(const std::string& full_path_and_file_name)
{
    Plan &plan;
    ErrorSet errors;
    errors = InputUtility::readShipPlan(full_path_and_file_name, plan);
    m_ship->setMPlan(plan);

    for (auto& error : errors)
    {
        m_algorithmErrors.setBit(error);
    }
    return m_algorithmErrors.getAndClear();
}

int SimpleAlgorithm::readShipRoute(const std::string& full_path_and_file_name)
{
    Route &route;
    ErrorSet errors;
    errors = InputUtility::readShipRoute(full_path_and_file_name, route);
    m_ship->setMRoute(plan);

    for (auto& error : errors)
    {
        m_algorithmErrors.setBit(error);
    }
    return m_algorithmErrors.getAndClear();
}

int SimpleAlgorithm::setWeightBalanceCalculator(WeightBalanceCalculator& calculator)
{

};
int SimpleAlgorithm::getInstructionsForCargo(const std::string& input_full_path_and_file_name,
                                             const std::string& output_full_path_and_file_name)
{
    return 0;
}