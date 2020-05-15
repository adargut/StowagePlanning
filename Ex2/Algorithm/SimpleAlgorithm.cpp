//
// Created by adargut on 5/12/20.
//

#include "SimpleAlgorithm.h"

int SimpleAlgorithm::readShipPlan(const std::string& full_path_and_file_name)
{
    Plan plan;
    ErrorSet errors;
    errors = InputUtility::readShipPlan(full_path_and_file_name, plan);
    m_ship->setPlan(plan);

    for (auto& error : errors)
    {
        m_algorithmErrors.setBit(error);
    }
    return m_algorithmErrors.getAndClear();
}

int SimpleAlgorithm::readShipRoute(const std::string& full_path_and_file_name)
{
    Route route;
    ErrorSet errors;
    errors = InputUtility::readShipRoute(full_path_and_file_name, route);
    m_ship->setRoute(route);

    for (auto& error : errors)
    {
        m_algorithmErrors.setBit(error);
    }
    return m_algorithmErrors.getAndClear();
}

int SimpleAlgorithm::setWeightBalanceCalculator(WeightBalanceCalculator& calculator)
{
    (void)calculator;
    return 0;
}

void SimpleAlgorithm::getInstructionsForUnloading(Instructions& instructions)
{
    Instructions tmp_instructions;
    ContainersVector containers_to_return;
    std::vector<std::string> containers_to_unload;
    const Plan &ship_plan = m_ship->getPlan();
    const ContainerMap &ship_map = m_ship->getContainerMap();

    for (auto &container_on_ship : ship_map) {
        std::string port_code = m_ship->getRoute()[m_ship->getCurrentPortIdx()];
        auto curr_container = container_on_ship.second.first;
        if (curr_container->getPortCode() == port_code) { // Container needs to be unloaded here
            containers_to_unload.push_back(curr_container->getId());
        }
    }
    for (auto &container_to_unload : containers_to_unload) {
        tmp_instructions.clear();
        containers_to_return.clear();
        // TODO implement rollback/backup mechanism
        auto container_pos = ship_map.find(container_to_unload)->second.second;
        int z = container_pos[0];
        int y = container_pos[1];
        int x = container_pos[2];
        for (int z_above = m_ship->getPlan().size() - 1; z_above > z; z_above--) {
            std::string container_above_id = ship_plan[z_above][y][x];
            // Position of a container above container to be unloaded
            if (container_above_id != FREE_POS && container_above_id != ILLEGAL_POS) {
                containers_to_return.push_back(ship_map.find(container_above_id)->second.first);
                m_ship->unloadContainer(z_above, y, x);
                tmp_instructions.push_back(Instruction(Instruction::Unload, container_above_id, z_above, y, x));
            }
        }
        // TODO check weight balancer before
        m_ship->unloadContainer(z, y, x); // Unload container originally intended for unloading
        tmp_instructions.push_back(Instruction(Instruction::Unload, container_to_unload, z, y, x));

        // Load all containers above container popped back into the ship
        for (int i = containers_to_return.size() - 1; i >= 0; i--) {
            auto container_to_return = containers_to_return[i];
            int new_z = z + containers_to_return.size() - i - 1; // New z for reloading the unloaded container
            m_ship->loadContainer(new_z, y, x, container_to_return);
            tmp_instructions.push_back(Instruction(Instruction::Load, container_to_return->getId(), new_z, y, x));
        }
        for (Instruction instruction : tmp_instructions) {
            instructions.push_back(instruction);
        }
    }
}

void SimpleAlgorithm::getInstructionForLoadingContainer(std::shared_ptr<Container> container_to_load, Instructions &result) {
    const Plan &ship_plan = m_ship->getPlan();
    bool destination_in_route = false;
    for (int i = m_ship->getCurrentPortIdx() + 1; i < int(m_ship->getRoute().size()); ++i) {
        if (container_to_load->getPortCode() == m_ship->getRoute()[i]) destination_in_route = true;
    }

    // Container destination unreachable
    if (!destination_in_route) {
        result.push_back(Instruction(Instruction::Reject,
                                     container_to_load->getId(), -1, -1, -1));
        return;
    }

    // Container already on the ship
    if(m_ship->getContainerMap().count(container_to_load->getId()))
    {
        result.push_back(Instruction(Instruction::Reject, container_to_load->getId(), -1, -1, -1));
        return;
    }
    for (int z = 0; z < int(ship_plan.size()); z++) { // TODO optimize this n^3 loop
        for (int y = 0; y < int(ship_plan[0].size()); y++) {
            for (int x = 0; x < int(ship_plan[0][0].size()); x++) {
                if (ship_plan[z][y][x] == FREE_POS) {
                    // TODO check calculator
                    // Check if container destination still in route (beyond the current port)
                    m_ship->loadContainer(z, y, x, container_to_load);
                    result.push_back(Instruction(Instruction::Load, container_to_load->getId(), z, y, x));
                    return;
                }
            }
        }
    }
    result.push_back(Instruction(Instruction::Reject, container_to_load->getId(), -1, -1, -1));
}

int SimpleAlgorithm::getInstructionsForCargo(const std::string& input_full_path_and_file_name,
                                             const std::string& output_full_path_and_file_name)
{
    // TODO check algorithm is properly initialized
    (void)output_full_path_and_file_name;
    ErrorSet errors;
    ContainersVector containers_to_load;
    Instructions instructions;
    errors = InputUtility::readCargo(input_full_path_and_file_name, containers_to_load);
    string port_name = InputUtility::getFileName(input_full_path_and_file_name);
    getInstructionsForUnloading(instructions);
    setRealDestinations(containers_to_load);
    for (auto& container : containers_to_load)
    {
        getInstructionForLoadingContainer(container, instructions);
    }
    m_ship->advanceCurrentPortIdx();
    //TODO output instructions to file
    //TODO return errors
    return 0;
}

void SimpleAlgorithm::setRealDestinations(ContainersVector &containers) {
    const Route& route = m_ship->getRoute();
    for (auto& container : containers)
    {
        string destination = container->getPortCode();
        container->setPortCode(BAD_DESTINATION);
        for (size_t i = m_ship->getCurrentPortIdx(); i < route.size(); ++i)
        {
            std::vector<string> split_line;
            boost::algorithm::split(split_line, route[i], boost::is_any_of(UNDERSCORE));
            if(split_line[0] == destination)
            {
                container->setPortCode(route[i]);
                break;
            }
        }
    }
}
