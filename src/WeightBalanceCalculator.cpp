#include "WeightBalanceCalculator.h"

WeightBalanceCalculator::WeightBalanceCalculator(const Plan& ship_plan) : ship_plan(ship_plan) {};

NaiveWeightBalanceCalculator::NaiveWeightBalanceCalculator(const Plan& ship_plan) : WeightBalanceCalculator(ship_plan) {};

int NaiveWeightBalanceCalculator::checkBalance(const Instructions &instructions, const std::vector<int> &weights) {
    return BALANCED; // for now, balancer always returns balanced
}