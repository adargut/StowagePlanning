#ifndef EX2_SIMPLEALGORITHM_H
#define EX2_SIMPLEALGORITHM_H

#include "GenericAlgorithm.h"

/**
 * @brief SimpleAlgorithm.h implements a determinstic algorithm for loading containers
 * 
 */
// TODO unload top containers first by sorting based on number of containers above, another optimization:
//  after first sort by destination take first k containers (k=number of empty spots) and sort them reversed with
//  same comparator
class SimpleAlgorithm : public GenericAlgorithm
{
public:
    void getInstructionForLoadingContainer(std::shared_ptr<Container> container_to_load, Instructions& instructions) override;
};


#endif //EX2_SIMPLEALGORITHM_H
