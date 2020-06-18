
#include "RandomAlgorithm.h"

REGISTER_ALGORITHM(RandomAlgorithm)

// Generate all pairs of format {x, y} with x, y upto max_x, max_y respectively, that are legal
bool RandomAlgorithm::generateAllPairs(std::vector<std::pair<int, int>>& res, std::optional<std::pair<int, int>> illegal_x_y)
{
    const Plan &ship_plan = m_ship.getPlan();
    int max_y = int(ship_plan[0].size()), max_x = int(ship_plan[0][0].size());

    for (int i = 0; i < max_x; ++i)
    {
        for (int j = 0; j < max_y; ++j)
        {
            int z = minFreeFloor(i, j);
            if (z != -1) // Found legal free floor
            {
                // Check we found different <x, y> than those we started with
                if (illegal_x_y.has_value() && i == illegal_x_y->first && j == illegal_x_y->second) continue;
                res.emplace_back(i, j);
            }
        }
    }
    return !(res.empty());
}

bool RandomAlgorithm::findFreePos(int &res_x, int &res_y, int &res_z, std::optional<std::pair<int, int>> illegal_x_y)
{
    PossiblePairs pairs;

    if (generateAllPairs(pairs, illegal_x_y))
    {
        int random_idx = rand() % pairs.size();
        res_x = pairs[random_idx].first;
        res_y = pairs[random_idx].second;
        res_z = minFreeFloor(res_x, res_y);
        return true;
    }
    return false;
}
