
#include "BadAlgorithm.h"

REGISTER_ALGORITHM(BadAlgorithm)

void BadAlgorithm::getInstructionForLoadingContainer(std::shared_ptr<Container> container_to_load, Instructions &result) 
{
    const Plan &ship_plan = m_ship.getPlan();

    for (int z = 0; z < int(ship_plan.size()); z++)
    {
        for (int y = 0; y < int(ship_plan[0].size()); y++)
        {
            for (int x = 0; x < int(ship_plan[0][0].size()); x++)
            {
                m_ship.loadContainer(z, y, x, container_to_load);
                result.push_back(Instruction(Instruction::Load, container_to_load->getId(), z, y, x));
                return;
            }
        }
    }
    result.push_back(Instruction(Instruction::Reject, container_to_load->getId(), -1, -1, -1));
}

