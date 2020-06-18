#ifndef __RANDOMALGORITHM_H__
#define __RANDOMALGORITHM_H__

#include "GenericAlgorithm.h"

using PossiblePairs = std::vector<std::pair<int, int>>;

/**
 * @brief RandomAlgorithm.h implements a non-deterministic algorithm for loading cargo
 * 
 */
class RandomAlgorithm : public GenericAlgorithm
{
public:
    bool findFreePos(int &res_x, int &res_y, int &res_z, std::optional<std::pair<int, int>> illegal_x_y) override;
private:
    bool generateAllPairs(PossiblePairs& res, std::optional<std::pair<int, int>> illegal_x_y);
};


#endif // __RANDOMALGORITHM_H__