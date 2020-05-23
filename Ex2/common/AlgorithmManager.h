#ifndef EX2_ALGORITHMMANAGER_H
#define EX2_ALGORITHMMANAGER_H

#include <vector>
#include <functional>
#include <memory>
#include "AbstractAlgorithm.h"
#include <string>
#include "InputUtility.h"
#include <dlfcn.h>

using string = std::string;
using AlgorithmFactory = std::function<std::unique_ptr<AbstractAlgorithm>()>;

struct DLCloser
{
    void operator()(void* dlhandle) const noexcept 
    {
        dlclose(dlhandle); 
    }
};

/**
 * @brief AlgorithmManager.h manages the registration of algorithms (factories)
 * 
 */
class AlgorithmManager
{
private:
    string m_algorithmsPath = CWD;
private:
    AlgorithmManager() = default; // Private to ensure only one static instance is created
    std::unique_ptr<AlgorithmFactory> factoryBuffer;
    std::vector<std::unique_ptr<void, DLCloser>> DLVector;
    std::unordered_map<string, std::unique_ptr<AlgorithmFactory>> factoryMap;
    bool bufferToMap(const string& algorithmName);
public:
    static AlgorithmManager& getInstance() {
        static AlgorithmManager instance; //Singleton
        return instance; }
    void setAlgorithmsPath(const string& algorithmsPath);
    bool registerAlgorithm(const string& algorithmName);
    void registerFactory(const std::function<std::unique_ptr<AbstractAlgorithm>()>& factory);
    std::unique_ptr<AbstractAlgorithm> getAlgorithmInstance(const string& algorithmName);
};


#endif //EX2_ALGORITHMMANAGER_H
