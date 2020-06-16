#include "../common/AlgorithmRegistration.h"
#include "../common/AlgorithmManager.h"

// Gets instance of factory
AlgorithmRegistration::AlgorithmRegistration(std::function<std::unique_ptr<AbstractAlgorithm>()> factory)
{
    AlgorithmManager::getInstance().registerFactory(factory);
}
