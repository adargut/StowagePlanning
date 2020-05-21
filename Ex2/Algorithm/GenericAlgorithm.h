#ifndef __GENERICALGORITHM_H__
#define __GENERICALGORITHM_H__

#define BAD_WEIGHT -1

#include <string>
#include <memory>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include "../Common/ISO_6346.h"
#include "../Common/AbstractAlgorithm.h"
#include "../Common/AlgorithmError.h"
#include "../Common/InputUtility.h"
#include "../Common/Ship.h"
#include "../Common/Instruction.h"
#include "../Common/Container.h"
#include "../Common/GeneralUtility.h"
#include "../Common/OutputUtility.h"
#include "../Common/DistanceToDestinationComparator.h"
#include "../Common/AlgorithmRegistration.h"

using string = std::string;


class GenericAlgorithm : public AbstractAlgorithm
{
protected:
    AlgorithmError m_algorithmErrors;
    Ship m_ship;
    bool m_plan_initialized = false;
    bool m_route_initialized = false;
    bool m_balance_calculator_initialized = false;
public:
    int readShipPlan(const std::string& full_path_and_file_name) override;
    int readShipRoute(const std::string& full_path_and_file_name) override;
    int setWeightBalanceCalculator(WeightBalanceCalculator& calculator) override;
    int getInstructionsForCargo(const std::string& input_full_path_and_file_name,
                                const std::string& output_full_path_and_file_name) override;
    void getInstructionsForUnloading(Instructions& instructions);
    virtual void getInstructionForLoadingContainer(std::shared_ptr<Container> container_to_load, Instructions& instructions) = 0;
    void setRealDestinations(ContainersVector& containers);
};


#endif // __GENERICALGORITHM_H__