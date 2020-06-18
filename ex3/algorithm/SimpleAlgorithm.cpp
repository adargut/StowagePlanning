#include "SimpleAlgorithm.h"

REGISTER_ALGORITHM(SimpleAlgorithm)

bool SimpleAlgorithm::findFreePos(int &res_x, int &res_y, int &res_z, std::optional<std::pair<int, int>> illegal_x_y)
{
    const Plan& plan = m_ship.getPlan();
    for (int z = 0; z < int(plan.size()); z++)
    {
        for (int y = 0; y < int(plan[0].size()); y++)
        {
            for (int x = 0; x < int(plan[0][0].size()); x++)
            {
                // Ignore unwanted free positions
                if (illegal_x_y.has_value() && illegal_x_y->first == x && illegal_x_y->second == y) continue;
                if (plan[z][y][x] == FREE_POS)
                {
                    res_x = x;
                    res_y = y;
                    res_z = z;
                    return true;
                }
            }
        }
    }
    return false;
}

