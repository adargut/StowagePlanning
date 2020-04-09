#include "WeightBalanceCalculator.h"

WeightBalanceCalculator::BalanceStatus
NaiveWeightBalanceCalculator::tryOperation(const Instruction &instruction, int weight, const Plan &plan) {
    return Approved;
}

std::pair<int, WeightBalanceCalculator::BalanceStatus> // TODO style me better
NaiveWeightBalanceCalculator::tryOperations(const Instructions &instructions, const std::vector<int> &weights,
                                            const Plan &plan) {
    if (instructions.size() != weights.size()) {
        // TODO return error
    }
    for (int i = 0; i < instructions.size(); i++) {
        BalanceStatus status = tryOperation(instructions[i], weights[i], plan);
        if (status != Approved) return std::make_pair(i, status);
    }
    return std::make_pair(-1, Approved);
}