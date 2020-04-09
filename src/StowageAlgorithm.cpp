//
// Created by Adar on 26/03/2020.
//

#include "StowageAlgorithm.h"
#include <fstream>
#include <iostream>

NaiveStowageAlgorithm::NaiveStowageAlgorithm(const Plan& _plan, const Route& _route,
                                             WeightBalanceCalculator* _calculator) {
    ship = new Ship(_plan, _route, _calculator);
}

Instructions NaiveStowageAlgorithm::getInstructionsForCargo(const Containers &containers_to_load) {
    return Instructions();
}

//const Instructions &NaiveStowageAlgorithm::getInstructionsForCargo(const Containers &containers_to_load) const {
//    return <#initializer#>;
//}
