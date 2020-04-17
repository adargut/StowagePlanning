#include "WeightBalanceCalculator.h"
#include "Utility.h"

WeightBalanceCalculator::BalanceStatus
NaiveWeightBalanceCalculator::tryOperation(const Instruction &instruction, int weight, const Plan &plan) {
    return Approved; // Naive for now
}

std::pair<int, WeightBalanceCalculator::BalanceStatus> NaiveWeightBalanceCalculator::tryOperations(
        const Instructions &instructions,
        const std::vector<int> &weights,
        const Plan &plan) {
    if (instructions.size() != weights.size()) {
        Error::throwSizeError();
        return std::make_pair(-1, Approved);
    }
    for (int i = 0; i < instructions.size(); i++) {
        BalanceStatus status = tryOperation(instructions[i], weights[i], plan);
        if (status != Approved) return std::make_pair(i, status);
    }
    return std::make_pair(-1, Approved);
}