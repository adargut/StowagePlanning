#include "SimpleAlgorithm.h"

REGISTER_ALGORITHM(SimpleAlgorithm)

// Fetch instructions for loading
void SimpleAlgorithm::getInstructionForLoadingContainer(std::shared_ptr<Container> container_to_load, Instructions &result) 
{
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

    int z, y, x;
    if (m_ship.findFreePos(x, y, z))
    {
        m_ship.loadContainer(z, y, x, container_to_load);
        result.push_back(Instruction(Instruction::Load, container_to_load->getId(), z, y, x));
    }
    else
    {
        result.push_back(Instruction(Instruction::Reject, container_to_load->getId(), -1, -1, -1));
    }
}
