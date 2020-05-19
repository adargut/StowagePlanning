#ifndef EX2_SIMPLEALGORITHM_H
#define EX2_SIMPLEALGORITHM_H

#include "GenericAlgorithm.h"

class SimpleAlgorithm : public GenericAlgorithm
{
public:
    void getInstructionForLoadingContainer(std::shared_ptr<Container> container_to_load, Instructions& instructions) override;
};


#endif //EX2_SIMPLEALGORITHM_H
