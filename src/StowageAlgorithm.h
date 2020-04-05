/**
    StowageAlgorithm.h
    Algorithmic logic of stowage
*/
#ifndef EX1_STOWAGEALGORITHM_H
#define EX1_STOWAGEALGORITHM_H

#include "Utility.h"
#include "WeightBalanceCalculator.h"

class StowageAlgorithm { // TODO implement me
    const Ship& ship;
public:
    StowageAlgorithm(const Ship& _ship);
    const Instructions& getInstructionsForCargo(const Containers& containers_to_load) const;
};

#endif //EX1_STOWAGEALGORITHM_H
