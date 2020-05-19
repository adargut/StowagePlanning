
#include "RandomAlgorithm.h"

REGISTER_ALGORITHM(RandomAlgorithm)

// Generate all pairs of format {x, y} with x, y upto max_x, max_y respectively
void RandomAlgorithm::generateAllPairs(int x, int y, int max_x, int max_y, PossiblePairs &res)
{
    if (x > max_x || y > max_y) return;
    string new_pair = std::to_string(x) + std::to_string(y); 
    if (res.count(new_pair) > 0) return;
    res.insert(new_pair);
    generateAllPairs(x+1, y, max_x, max_y, res);
    generateAllPairs(x, y+1, max_x, max_y, res);
    generateAllPairs(x, y, max_x, max_y, res);
}

// Find minimum Z value that is free for given <x, y>
int RandomAlgorithm::minFreeFloor(int x, int y)
{
    const Plan &ship_plan = m_ship.getPlan();
    for (int z = 0; z < int(ship_plan.size()); z++)
    {
        if (ship_plan[z][y][x] == FREE_POS) return z; 
    }
    return -1;
}

void RandomAlgorithm::getInstructionForLoadingContainer(std::shared_ptr<Container> container_to_load, Instructions &result) 
{
    const Plan &ship_plan = m_ship.getPlan();
    bool destination_in_route = false;
    for (int i = m_ship.getCurrentPortIdx() + 1; i < int(m_ship.getRoute().size()); ++i)
    {
        if (container_to_load->getPortCode() == m_ship.getRoute()[i]) destination_in_route = true;
    }

    // Container destination unreachable
    if (!destination_in_route)
    {
        result.push_back(Instruction(Instruction::Reject,
                                     container_to_load->getId(), -1, -1, -1));
        return;
    }

    // Container already on the ship
    if(m_ship.getContainerMap().count(container_to_load->getId()))
    {
        result.push_back(Instruction(Instruction::Reject, container_to_load->getId(), -1, -1, -1));
        return;
    }

    int max_y = int(ship_plan[0].size()) - 1, max_x = int(ship_plan[0][0].size()) - 1;
    PossiblePairs pairs;
    generateAllPairs(0, 0, max_x, max_y, pairs);

    while (!pairs.empty())
    {
        int random_idx = rand() % pairs.size();
        int curr_idx = 0;
        string res_pair;

        // Generate a random "<x><y>" style triplet
        for (auto &pair : pairs)
        {
            if (curr_idx++ == random_idx) 
            {
                res_pair = pair;
                pairs.erase(res_pair);
                break;
            }
        }
        int x = res_pair[0] - '0', y = res_pair[1] - '0';
        int z = minFreeFloor(x, y);
        // Found valid free pos
        if (z != -1)
        {
            m_ship.loadContainer(z, y, x, container_to_load);
            result.push_back(Instruction(Instruction::Load, container_to_load->getId(), z, y, x));
            return;
        }
    }
    // No valid free position triplet was found, so we reject
    result.push_back(Instruction(Instruction::Reject, container_to_load->getId(), -1, -1, -1));
}