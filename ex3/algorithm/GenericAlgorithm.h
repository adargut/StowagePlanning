#ifndef __GENERICALGORITHM_H__
#define __GENERICALGORITHM_H__

#define BAD_WEIGHT -1

#include <string>
#include <memory>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include "../common/ISO_6346.h"
#include "../common/AbstractAlgorithm.h"
#include "../common/AlgorithmError.h"
#include "../common/InputUtility.h"
#include "../common/Ship.h"
#include "../common/Instruction.h"
#include "../common/Container.h"
#include "../common/GeneralUtility.h"
#include "../common/OutputUtility.h"
#include "../common/DistanceToDestinationComparator.h"
#include "../common/AlgorithmRegistration.h"

using string = std::string;

/**
 * @brief GenericAlgorithm.h is the common functions between our algorithms
 * 
 */
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
    int minFreeFloor(int x, int y);
    virtual bool findFreePos(int &res_x, int &res_y, int &res_z, std::optional<std::pair<int, int>> illegal_x_y) = 0;
//    bool findRandomFreePos(int &res_x, int &res_y, int &res_z, std::optional<std::pair<int, int>> illegal_x_y = {});
    void getInstructionsForUnloading(Instructions& instructions);
    virtual void getInstructionForLoadingContainer(std::shared_ptr<Container> container_to_load, Instructions& instructions);
    void setRealDestinations(ContainersVector& containers);
};


#endif // __GENERICALGORITHM_H__