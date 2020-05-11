#ifndef EX2_ALGORITHMMANAGER_H
#define EX2_ALGORITHMMANAGER_H

#include <vector>
#include <functional>
#include <memory>
#include "AbstractAlgorithm.h"
#include <string>

using string = std::string;
using AlgorithmFactory = std::function<std::unique_ptr<AbstractAlgorithm>()>;


class AlgorithmManager
{
private:
    static AlgorithmManager instance;
    std::unique_ptr<AlgorithmFactory> factoryBuffer;
    std::unordered_map<string, std::unique_ptr<AlgorithmFactory>> factoryMap;
public:
    static AlgorithmManager& getInstance() { return instance; }
    void registerAlgorithm(const std::function<std::unique_ptr<AbstractAlgorithm>()>& factory);
    bool bufferToMap(const string& algorithmName);
};


#endif //EX2_ALGORITHMMANAGER_H
