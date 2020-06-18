#include "GenericAlgorithm.h"

// Read plan for usage of algorithm
int GenericAlgorithm::readShipPlan(const std::string& full_path_and_file_name)
{
    Plan plan;
    AlgorithmError errors;
    m_algorithmErrors = InputUtility::readShipPlan(full_path_and_file_name, plan);
    m_ship.setPlan(plan);

    if(!(m_algorithmErrors.getBit(AlgorithmError::errorCode::BadPlanFile)
    || m_algorithmErrors.getBit(AlgorithmError::errorCode::ConflictingXY))) m_plan_initialized = true;
    return m_algorithmErrors.getAndClear();
}

// Read route for usage of simulation
int GenericAlgorithm::readShipRoute(const std::string& full_path_and_file_name)
{
    Route route;
    m_algorithmErrors = InputUtility::readShipRoute(full_path_and_file_name, route);
    m_ship.setRoute(route);

    if(!(m_algorithmErrors.getBit(AlgorithmError::errorCode::BadTravelFile)
    || m_algorithmErrors.getBit(AlgorithmError::errorCode::SinglePortTravel))) m_route_initialized = true;
    return m_algorithmErrors.getAndClear();
}

// Initialize weight balance calculator for simulation
int GenericAlgorithm::setWeightBalanceCalculator(WeightBalanceCalculator& calculator)
{
    (void)calculator;
    m_balance_calculator_initialized = true;
    return 0;
}

// Updates instructions for unloading cargo
void GenericAlgorithm::getInstructionsForUnloading(Instructions& instructions)
{
    Instructions tmp_instructions;
    ContainersVector containers_to_return;
    std::vector<std::string> containers_to_unload;
    const Plan &ship_plan = m_ship.getPlan();
    const ContainerMap &ship_map = m_ship.getContainerMap();

    for (auto &container_on_ship : ship_map)
    {
        std::string port_code = m_ship.getRoute()[m_ship.getCurrentPortIdx()];
        auto curr_container = container_on_ship.second.first;
        if (curr_container->getPortCode() == port_code)
        { // Container needs to be unloaded here
            containers_to_unload.push_back(curr_container->getId());
        }
    }
    // Unload higher containers first to optimize performance
    // TODO check on Coliru
    std::sort(containers_to_unload.begin(), containers_to_unload.end(),
            [&,ship_map](std::shared_ptr<Container> c1, std::shared_ptr<Container> c2)
            { return ship_map.find(c1->getId())->second.second[0] > ship_map.find(c2->getId())->second.second[0]; });

    for (auto &container_to_unload : containers_to_unload) {
        tmp_instructions.clear();
        containers_to_return.clear();
        auto container_pos = ship_map.find(container_to_unload)->second.second;
        int z = container_pos[0];
        int y = container_pos[1];
        int x = container_pos[2];

        for (int z_above = m_ship.getPlan().size() - 1; z_above > z; z_above--)
        {
            std::string container_above_id = ship_plan[z_above][y][x];
            // Position of a container above container to be unloaded
            if (container_above_id != FREE_POS && container_above_id != ILLEGAL_POS)
            {
                int res_x, res_y, res_z;
                auto illegal_x_y = std::make_pair(x, y);
                if (m_ship.findFreePos(res_x, res_y, res_z, illegal_x_y))
                {
                    tmp_instructions.push_back(Instruction(Instruction::Move, container_above_id, z_above, y, x, res_z, res_y, res_x));
                    auto container_moved = ship_map.find(container_above_id)->second.first;
                    m_ship.unloadContainer(z_above, y, x);
                    m_ship.loadContainer(res_z, res_y, res_x, container_moved);
                }
                else
                {
                    containers_to_return.push_back(ship_map.find(container_above_id)->second.first);
                    m_ship.unloadContainer(z_above, y, x);
                    tmp_instructions.push_back(Instruction(Instruction::Unload, container_above_id, z_above, y, x));
                }
            }
        }
        m_ship.unloadContainer(z, y, x); // Unload container originally intended for unloading
        tmp_instructions.push_back(Instruction(Instruction::Unload, container_to_unload, z, y, x));

        // Load all containers above container popped back into the ship
        for (int i = containers_to_return.size() - 1; i >= 0; i--)
        {
            auto container_to_return = containers_to_return[i];
            int new_z = z + containers_to_return.size() - i - 1; // New z for reloading the unloaded container
            m_ship.loadContainer(new_z, y, x, container_to_return);
            tmp_instructions.push_back(Instruction(Instruction::Load, container_to_return->getId(), new_z, y, x));
        }
        for (const Instruction& instruction : tmp_instructions)
        {
            instructions.push_back(instruction);
        }
    }
}

// Fetch instructions for cargo
int GenericAlgorithm::getInstructionsForCargo(const std::string& input_full_path_and_file_name,
                                              const std::string& output_full_path_and_file_name)
{
    using Cmp = DistanceToDestinationComparator;
    Cmp distance_to_destination(m_ship.getCurrentPortIdx(), m_ship.getRoute());
    (void)output_full_path_and_file_name;
    ContainersVector containers_to_load;
    Instructions instructions;
    // Check algorithm is properly initialized
    if(!m_route_initialized)
    {
        m_algorithmErrors.setBit(AlgorithmError::errorCode::BadTravelFile);
        OutputUtility::writeCargoInstructions(output_full_path_and_file_name, instructions);
        return m_algorithmErrors.getAndClear();
    }
    if(!m_plan_initialized)
    {
        m_algorithmErrors.setBit(AlgorithmError::errorCode::BadPlanFile);
        OutputUtility::writeCargoInstructions(output_full_path_and_file_name, instructions);
        return m_algorithmErrors.getAndClear();
    }
    std::unordered_set<string> containers_seen;
    m_algorithmErrors = InputUtility::readCargo(input_full_path_and_file_name, containers_to_load);
    if(m_ship.getCurrentPortIdx() == m_ship.getRoute().size()-1) //At last port
    {
        if(!containers_to_load.empty())
        {
            containers_to_load.clear();
            m_algorithmErrors.setBit(AlgorithmError::errorCode::LastPortNotEmpty);
        }
    }
    string port_name = m_ship.getRoute()[m_ship.getCurrentPortIdx()];
    setRealDestinations(containers_to_load);
    ContainersVector valid_containers_to_load;

    // Check ISO, format and valid destination for containers on port
    for (auto& container : containers_to_load)
    {
        bool was_rejected = false;
        // ISO check
        if (!ISO_6346::isValidId(container->getId()))
        {
            m_algorithmErrors.setBit(AlgorithmError::BadContainerID);
            instructions.push_back(Instruction(Instruction::Reject, container->getId(), -1, -1, -1));
            was_rejected = true;
        }
        // Weight check
        if (container->getWeight() == BAD_WEIGHT)
        {
            m_algorithmErrors.setBit(AlgorithmError::BadContainerWeight);
            if (!was_rejected) // Make sure we don't reject the same container twice
            {
                instructions.push_back(Instruction(Instruction::Reject, container->getId(), -1, -1, -1));
                was_rejected = true;
            }
        }
        // Destination reachable check
        if (container->getPortCode() == BAD_DESTINATION)
        {
            m_algorithmErrors.setBit(AlgorithmError::BadContainerDest);
            if (!was_rejected) // Make sure we don't reject the same container twice
            {
                instructions.push_back(Instruction(Instruction::Reject, container->getId(), -1, -1, -1));
                was_rejected = true;
            }
        }
        // Reject container already on ship
        if (m_ship.hasContainer(container->getId()))
        {
            m_algorithmErrors.setBit(AlgorithmError::errorCode::DuplicateContainerOnShip);
            if (!was_rejected)
            {
                instructions.push_back(Instruction(Instruction::Reject, container->getId(), -1, -1, -1));
                was_rejected = true;
            }
        }
        // Reject duplicate container on port
        if (containers_seen.count(container->getId()) > 0) 
        {
            m_algorithmErrors.setBit(AlgorithmError::errorCode::DuplicateContainerOnPort);
            // Make sure container wasn't already rejected
            if (!m_ship.hasContainer(container->getId()))
            {
                instructions.push_back(Instruction(Instruction::Reject, container->getId(), -1, -1, -1));
            }
        }
        // We only care about valid containers
        if (!was_rejected) valid_containers_to_load.push_back(container);
        // Mark container as seen
        containers_seen.insert(container->getId());
    }

    getInstructionsForUnloading(instructions);
    std::sort(valid_containers_to_load.begin(), valid_containers_to_load.end(), distance_to_destination);
    size_t free_positions = m_ship.countFreePos();

    // Reject all containers that are farthest and there's no place to load them
    while (valid_containers_to_load.size() > free_positions)
    {
        instructions.push_back(Instruction(Instruction::Reject, valid_containers_to_load.back()->getId()));
        valid_containers_to_load.pop_back();
        m_algorithmErrors.setBit(AlgorithmError::ContainersExceedingCapacity);
    }

//     Load far away containers first
    std::reverse(valid_containers_to_load.begin(), valid_containers_to_load.end());
    for (auto& container : valid_containers_to_load)
    {
        getInstructionForLoadingContainer(container, instructions);
    }
    m_ship.advanceCurrentPortIdx();

    OutputUtility::writeCargoInstructions(output_full_path_and_file_name, instructions);
    return m_algorithmErrors.getAndClear();
}

// Adds _* for * an integer representing cargo_* as the container destination
void GenericAlgorithm::setRealDestinations(ContainersVector &containers)
{
    const Route& route = m_ship.getRoute();
    for (auto& container : containers)
    {
        string destination = container->getPortCode();
        container->setPortCode(BAD_DESTINATION);
        for (size_t i = m_ship.getCurrentPortIdx(); i < route.size(); ++i)
        {
            std::vector<string> split_line;
            GeneralUtility::split(split_line, route[i], UNDERSCORE);
            if(split_line[0] == destination)
            {
                container->setPortCode(route[i]);
                break;
            }
        }
    }
}
