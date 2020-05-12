#include "AlgorithmRegistration.h"
#include "AlgorithmManager.h"


AlgorithmRegistration::AlgorithmRegistration(std::function<std::unique_ptr<AbstractAlgorithm>()> factory)
{
    AlgorithmManager::getInstance().registerFactory(factory);
}
