#ifndef EX2_SIMPLEALGORITHM_H
#define EX2_SIMPLEALGORITHM_H

#include "GenericAlgorithm.h"

/**
 * @brief SimpleAlgorithm.h implements a determinstic algorithm for loading containers
 * 
 */
class SimpleAlgorithm : public GenericAlgorithm
{
public:
    bool findFreePos(int &res_x, int &res_y, int &res_z, std::optional<std::pair<int, int>> illegal_x_y) override;
};


#endif //EX2_SIMPLEALGORITHM_H
