/**
    StowageAlgorithm.h
    Algorithmic logic of stowage
*/
#ifndef EX1_STOWAGEALGORITHM_H
#define EX1_STOWAGEALGORITHM_H

#include "Utility.h"
#include "Ship.h"
#include "WeightBalanceCalculator.h"

class StowageAlgorithm { // TODO implement me
public:
    virtual Instructions getInstructionsForCargo(const Containers& containers_to_load) = 0;
};

class NaiveStowageAlgorithm : public StowageAlgorithm {
private:
    Ship* ship;
public:
    NaiveStowageAlgorithm(const Plan& _plan, const Route& _route, WeightBalanceCalculator* _calculator);
    Instructions getInstructionsForCargo(const Containers &containers_to_load) override;
};

class RandomStowageAlgorithm : public StowageAlgorithm {
    //
};

#endif //EX1_STOWAGEALGORITHM_H
