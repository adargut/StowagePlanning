//
// Created by nir on 12/05/2020.
//
#include "AlgorithmRegistration.h"
#include "AlgorithmManager.h"

AlgorithmRegistration::AlgorithmRegistration(std::function<std::unique_ptr<AbstractAlgorithm>()> factory) {
    AlgorithmManager::getInstance().registerAlgorithm(factory);
}
