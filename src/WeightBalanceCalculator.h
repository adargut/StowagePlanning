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
//    const Plan& ship_plan;
public:
    enum BalanceStatus {
    Approved,
    X_IMBALANCED,
    Y_IMBALANCED,
    X_Y_IMBALANCED
    };
    virtual BalanceStatus tryOperation(const Instruction& instruction, int weight, const Plan &plan) = 0;
    virtual std::pair<int, BalanceStatus> tryOperations(const Instructions &instructions,
                                                        const std::vector<int> &weights, const Plan &plan) = 0;
    virtual ~WeightBalanceCalculator() = default;
};

class NaiveWeightBalanceCalculator : public WeightBalanceCalculator {
public:
    NaiveWeightBalanceCalculator() = default;
    // Try a single operation
    BalanceStatus tryOperation(const Instruction& instruction, int weight, const Plan &plan) override;
    // Try a set of operations
    std::pair<int, BalanceStatus> tryOperations(const Instructions &instructions,
                                                const std::vector<int> &weights, const Plan &plan) override;
    ~NaiveWeightBalanceCalculator() override = default;
};

#endif //EX1_WEIGHTBALANCECALCULATOR_H
