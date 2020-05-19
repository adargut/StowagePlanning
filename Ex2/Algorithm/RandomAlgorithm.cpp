
#include "RandomAlgorithm.h"

REGISTER_ALGORITHM(RandomAlgorithm)

// Generate all triplets of format {x, y, z} with x, y, z upto max_x, max_y and max_z respectively
void RandomAlgorithm::generateAllTriplets(int x, int y, int z, int max_x, int max_y, int max_z, PossibleTriplets &res)
{
    if (x > max_x || y > max_y || z > max_z) return;
    res.insert(std::to_string(x) + std::to_string(y) + std::to_string(z));
    generateAllTriplets(x+1, y, z, max_x, max_y, max_z, res);
    generateAllTriplets(x, y+1, z, max_x, max_y, max_z, res);
    generateAllTriplets(x, y, z+1, max_x, max_y, max_z, res);
}

// Find minimum Z value that is free for given <x, y>
int RandomAlgorithm::minFreeFloor(int x, int y, int z)
{
    const Plan &ship_plan = m_ship.getPlan();
    while (z >= 0 && ship_plan[z][y][x] == FREE_POS) z--; // TODO not sure here if should be 0 or 1?
    return z;
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

    int max_z = int(ship_plan.size()) - 1, max_y = int(ship_plan[0].size()) - 1, max_x = int(ship_plan[0][0].size()) - 1;
    PossibleTriplets triplets;
    generateAllTriplets(0, 0, 0, max_x, max_y, max_z, triplets);

    while (!triplets.empty())
    {
        int random_idx = rand() % triplets.size();
        int curr_idx = 0;
        string res_triplet;

        // Generate a random "<x><y><z>" style triplet
        for (auto &triplet : triplets)
        {
            if (curr_idx++ == random_idx) 
            {
                res_triplet = triplet;
                triplets.erase(res_triplet);
                break;
            }
        }
        int x = res_triplet[0] - '0', y = res_triplet[1] - '0', z = res_triplet[2] - '0';
        if (ship_plan[z][y][x] == FREE_POS)
        {
            z = minFreeFloor(x, y, z);
            m_ship.loadContainer(z, y, x, container_to_load);
            result.push_back(Instruction(Instruction::Load, container_to_load->getId(), z, y, x));
            return;
        }
    }
    // No valid free position triplet was found, so we reject
    result.push_back(Instruction(Instruction::Reject, container_to_load->getId(), -1, -1, -1));
}