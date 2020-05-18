#include "AlgorithmManager.h"


//AlgorithmManager AlgorithmManager::instance;

void AlgorithmManager::registerFactory(const std::function<std::unique_ptr<AbstractAlgorithm>()>& factory)
{
    factoryBuffer = std::make_unique<AlgorithmFactory>(factory);
}

bool AlgorithmManager::bufferToMap(const string &algorithmName)
{
    if (!factoryBuffer) return false;
    factoryMap[algorithmName] = std::move(factoryBuffer);
    return true;
}

void AlgorithmManager::setAlgorithmsPath(const string &algorithmsPath) {
    m_algorithmsPath = algorithmsPath;
}

bool AlgorithmManager::registerAlgorithm(const string &algorithmName) {
    std::string SoPath = m_algorithmsPath + algorithmName + SO_SUFFIX;
    std::unique_ptr<void, DLCloser> handle(dlopen(SoPath.c_str(), RTLD_LAZY));
    if(handle)
    {
        std::cout << "failed loading: " << SoPath << dlerror() << std::endl;
        return false;
    } else
    {
        DLVector.push_back(std::move(handle));
        if(!bufferToMap(algorithmName)) {
            cout << "Algorithm " << algorithmName << " didn't register properly\n";
            return false;
        }
    }
    return true;
}

std::unique_ptr<AbstractAlgorithm> AlgorithmManager::getAlgorithmInstance(const string& algorithmName)
{
    if(!factoryMap.count(algorithmName)) return nullptr;
    return factoryMap[algorithmName]->operator()();
}
