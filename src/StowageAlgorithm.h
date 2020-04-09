/**
    StowageAlgorithm.h
    Algorithmic logic of stowage
*/
#ifndef EX1_STOWAGEALGORITHM_H
#define EX1_STOWAGEALGORITHM_H

#include "Utility.h"
#include "WeightBalanceCalculator.h"

class StowageAlgorithm { // TODO implement me
public:
//    StowageAlgorithm(const Ship& _ship);
    virtual const Instructions& getInstructionsForCargo(const Containers& containers_to_load) const = 0;
};

class NaiveStowageAlgorithm : public StowageAlgorithm {
private:
    Ship* ship;
public:
    NaiveStowageAlgorithm(const Plan& _plan, const Port& _port, const WeightBalanceCalculator& _calculator);
    const Instructions& getInstructionsForCargo(const Containers& containers_to_load) const override;
};

class RandomStowageAlgorithm : public StowageAlgorithm {
    //
};

#endif //EX1_STOWAGEALGORITHM_H
