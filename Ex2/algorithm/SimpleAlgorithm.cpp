#include "SimpleAlgorithm.h"

REGISTER_ALGORITHM(SimpleAlgorithm)

void SimpleAlgorithm::getInstructionForLoadingContainer(std::shared_ptr<Container> container_to_load, Instructions &result) 
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
    for (int z = 0; z < int(ship_plan.size()); z++)
    {
        for (int y = 0; y < int(ship_plan[0].size()); y++)
        {
            for (int x = 0; x < int(ship_plan[0][0].size()); x++)
            {
                if (ship_plan[z][y][x] == FREE_POS)
                {
                    m_ship.loadContainer(z, y, x, container_to_load);
                    result.push_back(Instruction(Instruction::Load, container_to_load->getId(), z, y, x));
                    return;
                }
            }
        }
    }
    result.push_back(Instruction(Instruction::Reject, container_to_load->getId(), -1, -1, -1));
}
