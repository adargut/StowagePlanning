#include <iostream>
#include "WeightBalanceCalculator.h"

// Reads plan for balancer calculator
int WeightBalanceCalculator::readShipPlan(const std::string& full_path_and_file_name)
{
    (void)full_path_and_file_name;
    return 0;
}

// Tries operation in balance calculator, always returns approved for now
WeightBalanceCalculator::BalanceStatus WeightBalanceCalculator::tryOperation(char loadUnload, int kg, int x, int y)
{
    (void)loadUnload; (void)kg; (void)x; (void)y;
    return WeightBalanceCalculator::APPROVED;
}
