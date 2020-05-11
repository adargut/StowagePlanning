//
// Created by nir on 11/05/2020.
//

#include "AlgorithmManager.h"
AlgorithmManager AlgorithmManager::instance;
void AlgorithmManager::registerAlgorithm(const std::function<std::unique_ptr<AbstractAlgorithm>()>& factory)
{
    factoryBuffer = std::make_unique<AlgorithmFactory>(factory);
}
