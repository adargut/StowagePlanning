/**
    StowageAlgorithm.h
    Algorithmic logic of stowage
*/

#ifndef EX1_STOWAGEALGORITHM_H
#define EX1_STOWAGEALGORITHM_H

#include "Utility.h"
#include "Ship.h"
#include "WeightBalanceCalculator.h"
#include "Instruction.h"

class StowageAlgorithm {
protected:
    std::string algorithm_name;
public:
    virtual Instructions getInstructionsForCargo(const ContainersVector &containers_to_load) = 0;
    const std::string& getAlgorithmName() const;
    virtual void reset(const Plan &_plan, const Route &_route, WeightBalanceCalculator *_calculator) = 0;
    virtual ~StowageAlgorithm() = default;
};

class NaiveStowageAlgorithm : public StowageAlgorithm {
private:
    Ship *ship = nullptr;
public:
    NaiveStowageAlgorithm();
    // Resets the data structure used by the algorithm to keep track of the ship's state during travel
    void reset(const Plan &_plan, const Route &_route, WeightBalanceCalculator *_calculator) override;
    // Construct vector of instructions based on the list of containers to load and the ship's state
    Instructions getInstructionsForCargo(const ContainersVector &containers_to_load) override;
    ~NaiveStowageAlgorithm() override;
};

class RandomStowageAlgorithm : public StowageAlgorithm {
    // TODO implement random algorithm in Ex2
};

#endif //EX1_STOWAGEALGORITHM_H
