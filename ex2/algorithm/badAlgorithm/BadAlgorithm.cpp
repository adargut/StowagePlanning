
#include "BadAlgorithm.h"

REGISTER_ALGORITHM(BadAlgorithm)

// Intentionally generate a bad load/unload/reject instruction by tossing coins
void BadAlgorithm::getInstructionForLoadingContainer(std::shared_ptr<Container> container_to_load, Instructions &result) 
{
    const Plan &ship_plan = m_ship.getPlan();
    int z = 0;
    int y = rand()%ship_plan[0].size();
    int x = rand()%ship_plan[0][0].size();
    m_ship.loadContainer(z, y, x, container_to_load);
    int i = rand()%3;
    switch (i)
    {
        case 0:
            result.push_back(Instruction(Instruction::Load, container_to_load->getId(), z, y, x));
            break;
        case 1:
            result.push_back(Instruction(Instruction::Unload, container_to_load->getId(), z, y, x));
            break;
        case 2:
            result.push_back(Instruction(Instruction::Reject, container_to_load->getId(), -1, -1, -1));
            break;
    }
    return;
}

