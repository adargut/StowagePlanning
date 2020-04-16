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

    void reset(const Plan &_plan, const Route &_route, WeightBalanceCalculator *_calculator) override;

    Instructions getInstructionsForCargo(const ContainersVector &containers_to_load) override;

    ~NaiveStowageAlgorithm() override;

private:
    void getInstructionsForUnloading(const ContainerMap &ship_map,
                                     const Plan &ship_plan,
                                     Instructions &result);

    // Utility function for getInstructions for cargo: load containers currently at port into ship
    void getInstructionsForLoading(const Plan& ship_plan, Instructions &result,
                                   ContainersVector& sorted_containers_to_load);

    void getInstructionForLoadingContainer(const Plan& ship_plan, Instructions &result,
                                           Container* container_to_load);
};

class RandomStowageAlgorithm : public StowageAlgorithm {
    // TODO implement random algorithm in Ex2
};

#endif //EX1_STOWAGEALGORITHM_H
