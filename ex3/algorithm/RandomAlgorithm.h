#ifndef __RANDOMALGORITHM_H__
#define __RANDOMALGORITHM_H__

#include "GenericAlgorithm.h"

using PossiblePairs = std::unordered_set<string>;

/**
 * @brief RandomAlgorithm.h implements a non-deterministic algorithm for loading cargo
 * 
 */
 // TODO add more randomization, unload top containers first by sorting based on number of containers above
class RandomAlgorithm : public GenericAlgorithm
{
public:
    void getInstructionForLoadingContainer(std::shared_ptr<Container> container_to_load, Instructions& instructions) override;
private:
    int minFreeFloor(int x, int y);
    void generateAllPairs(int x, int y, int max_x, int max_y, PossiblePairs &res);
};


#endif // __RANDOMALGORITHM_H__