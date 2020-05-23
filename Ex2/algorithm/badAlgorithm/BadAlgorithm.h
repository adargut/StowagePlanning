#ifndef __RANDOMALGORITHM_H__
#define __RANDOMALGORITHM_H__

#include "../GenericAlgorithm.h"

using PossiblePairs = std::unordered_set<string>;

/**
 * @brief BadAlgorithm.h implements a purposefully bad algorithm for error showcasing
 * 
 */
class BadAlgorithm : public GenericAlgorithm
{
public:
    void getInstructionForLoadingContainer(std::shared_ptr<Container> container_to_load, Instructions& instructions) override;
};


#endif // __BADALGORITHM_H__