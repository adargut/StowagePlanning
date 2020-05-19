#ifndef __RANDOMALGORITHM_H__
#define __RANDOMALGORITHM_H__

#include "GenericAlgorithm.h"

using PossibleTriplets = std::unordered_set<string>;

class RandomAlgorithm : public GenericAlgorithm
{
private:
    AlgorithmError m_algorithmErrors;
    Ship m_ship;
public:
    void getInstructionForLoadingContainer(std::shared_ptr<Container> container_to_load, Instructions& instructions) override;
private:
    int minFreeFloor(int x, int y, int z);
    void generateAllTriplets(int x, int y, int z, int max_x, int max_y, int max_z, PossibleTriplets &res);
};


#endif // __RANDOMALGORITHM_H__