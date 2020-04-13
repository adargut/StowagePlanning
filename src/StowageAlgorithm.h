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

class StowageAlgorithm { // TODO implement me
public:
    virtual Instructions getInstructionsForCargo(const ContainersVector& containers_to_load) = 0;
    virtual void reset(const Plan& _plan, const Route& _route, WeightBalanceCalculator* _calculator) = 0;
    virtual ~StowageAlgorithm() = default;
};

class NaiveStowageAlgorithm : public StowageAlgorithm {
private:
    Ship* ship = nullptr;
public:
    // TODO reset instead of constructor
    void reset(const Plan& _plan, const Route& _route, WeightBalanceCalculator* _calculator) override;
    Instructions getInstructionsForCargo(const ContainersVector &containers_to_load) override;
    ~NaiveStowageAlgorithm() override;
};

class RandomStowageAlgorithm : public StowageAlgorithm {
    //
};

#endif //EX1_STOWAGEALGORITHM_H
