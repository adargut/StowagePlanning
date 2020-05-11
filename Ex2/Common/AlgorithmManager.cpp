#include "AlgorithmManager.h"


AlgorithmManager AlgorithmManager::instance;

void AlgorithmManager::registerAlgorithm(const std::function<std::unique_ptr<AbstractAlgorithm>()>& factory)
{
    factoryBuffer = std::make_unique<AlgorithmFactory>(factory);
}

bool AlgorithmManager::bufferToMap(const string &algorithmName)
{
    if (!factoryBuffer) return false;
    factoryMap[algorithmName] = std::move(factoryBuffer);
    return true;
}