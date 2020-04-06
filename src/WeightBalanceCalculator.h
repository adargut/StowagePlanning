/**
    WeightBalanceCalculator.h
    Weight balance calculator that checks the balance an instruction set
*/
#ifndef EX1_WEIGHTBALANCECALCULATOR_H
#define EX1_WEIGHTBALANCECALCULATOR_H
#define BALANCED (-1)

#include <vector>
#include "Instruction.h"
#include "Utility.h"

class WeightBalanceCalculator {
protected:
    const Plan& ship_plan;
public:
    explicit WeightBalanceCalculator(const Plan& ship_plan);
    virtual int checkBalance(const Instructions& instructions, const std::vector<int>& weights) = 0;
    virtual ~WeightBalanceCalculator() = 0;
};

class NaiveWeightBalanceCalculator: public WeightBalanceCalculator {
public:
    explicit NaiveWeightBalanceCalculator(const Plan &ship_plan);
    int checkBalance(const Instructions &instructions, const std::vector<int> &weights) override;
    ~NaiveWeightBalanceCalculator() override; //TODO he said whenever adding new desturctor, need to overload operators?
};

#endif //EX1_WEIGHTBALANCECALCULATOR_H
