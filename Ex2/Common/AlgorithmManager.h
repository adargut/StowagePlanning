//
// Created by nir on 11/05/2020.
//

#ifndef EX2_ALGORITHMMANAGER_H
#define EX2_ALGORITHMMANAGER_H

#include <vector>
#include <functional>
#include <memory>
#include "AbstractAlgorithm.h"
#include <string>

using string = std::string;
using AlgorithmFactory = std::function<std::unique_ptr<AbstractAlgorithm>()>;

class AlgorithmManager {
    static AlgorithmManager instance;
    std::unique_ptr<AlgorithmFactory> factoryBuffer;
    std::unordered_map<string, std::unique_ptr<AlgorithmFactory>> factoryMap;
public:
    void registerAlgorithm(const std::function<std::unique_ptr<AbstractAlgorithm>()>& factory);
    bool bufferToMap(const string& algorithmName){
        if(!factoryBuffer) return false;
        factoryMap[algorithmName] = std::move(factoryBuffer);
        return true;
    }
    static AlgorithmManager& getInstance() {
        return instance;
    }
};


#endif //EX2_ALGORITHMMANAGER_H
