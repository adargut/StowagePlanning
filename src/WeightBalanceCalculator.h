/**
    WeightBalanceCalculator.h
    Weight balance calculator that checks the balance an instruction set
*/
#ifndef EX1_WEIGHTBALANCECALCULATOR_H
#define EX1_WEIGHTBALANCECALCULATOR_H
#define BALANCED -1

#include <vector>
#include "Instruction.h"
#include "Utility.h"

class WeightBalanceCalculator {
protected:
    const Plan& ship_plan;
public:
    WeightBalanceCalculator(const Plan& ship_plan);
    virtual int checkBalance(const Instructions& instructions, const std::vector<int>& weights) = 0;
};

class NaiveWeightBalanceCalculator: public WeightBalanceCalculator {
public:
    NaiveWeightBalanceCalculator(const Plan &ship_plan);
    int checkBalance(const Instructions &instructions, const std::vector<int> &weights) override;
};

#endif //EX1_WEIGHTBALANCECALCULATOR_H
