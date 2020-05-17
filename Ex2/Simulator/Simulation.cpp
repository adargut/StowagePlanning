//
// Created by nir on 12/05/2020.
//

#include "Simulation.h"

static bool isRangeValid(const Plan &plan, const Instruction &instruction)
{
    if (instruction.getFloor() < 0 || instruction.getFloor() >= int(plan.size())) return false;
    if (instruction.getRow() < 0 || instruction.getFloor() >= int(plan[0].size())) return false;
    if (instruction.getCol() < 0 || instruction.getFloor() >= int(plan[0][0].size())) return false;
    if(instruction.getOp() == Instruction::Move)
    {
        if (instruction.getNewFloor() < 0 || instruction.getNewFloor() >= int(plan.size())) return false;
        if (instruction.getNewRow() < 0 || instruction.getNewFloor() >= int(plan[0].size())) return false;
        if (instruction.getNewCol() < 0 || instruction.getNewFloor() >= int(plan[0][0].size())) return false;
    }
    return true;
}

bool Simulation::isDestinationReachable(std::shared_ptr<const Container> container)
{
    for (int i = m_ship.getCurrentPortIdx(); i < int(m_ship.getRoute().size()); i++) {
        if(m_ship.getRoute()[i] == container->getPortCode()) return true;
    }
    return false;
}

bool Simulation::initialize()
{
    Plan ship_plan;
    Route ship_route;
    string plan_file;
    string route_file;
    ErrorSet errors;

    // Set ship initial configuration
    for (const auto &file : DirectoryIterator(m_travelDir))
    {
        string file_path = file.path();
        if (boost::algorithm::ends_with(file_path, ROUTE_SUFFIX))
        {
            route_file = std::move(file_path);
            break;
        }
    }
    errors = InputUtility::readShipRoute(route_file, ship_route);
    //TODO handle errors
    for (const auto &file : DirectoryIterator(m_travelDir))
    {
        string file_path = file.path();
        if (boost::algorithm::ends_with(file_path, PLAN_SUFFIX))
        {
            plan_file = std::move(file_path);
            break;
        }
    }
    errors = InputUtility::readShipPlan(plan_file, ship_plan);
    //TODO handle errors
    m_ship.setRoute(ship_route);
    m_ship.setPlan(ship_plan);

    // Set data of ports
    for (auto& port :ship_route)
    {
        ContainersVector port_containers;
        string port_file = m_travelDir + "/" + port + CARGO_SUFFIX;
        errors = InputUtility::readCargo(port_file, port_containers);
        //TODO handle errors
        m_ports.emplace_back(port, port_containers);
    }
    return true;
}

bool Simulation::run()
{
    bool run_failed = 0;
    int number_of_operations = 0;
    int reported_errors;
    Errors errors;
    for (auto& port : m_ports)
    {
        using Cmp = DistanceToDestinationComparator;
        Cmp distance_to_dest(m_ship.getCurrentPortIdx(), m_ship.getRoute());
        std::vector<std::string> rejected; // Vector to keep track of rejected container id's for this port
        PortContainers original_containers(port.getContainers());
        const string& port_code = port.getCode();
        string cargo_file = m_travelDir + "/" + port_code + CARGO_SUFFIX;
        string crane_instructions_file = m_outputDir + "/" + port_code + CRANE_INSTRUCTIONS_SUFFIX;
        reported_errors = m_algorithm->getInstructionsForCargo(cargo_file, crane_instructions_file);
        Instructions instructions; //TODO fill from crane instructions file
        if(!InputUtility::readCraneInstructions(crane_instructions_file, instructions))
        {
            // TODO handle error while loading instructions from instructions file
        }
        number_of_operations+=Instruction::countInstructions(instructions);
        for (auto& instruction : instructions)
        {
            // Handle unload operation
            if(instruction.getOp() == Instruction::Unload)
                handleUnloadOperation(port, instruction, errors);
            // Handle load operation
            if(instruction.getOp() == Instruction::Load)
                handleLoadOperation(port, instruction, errors);
            // Handle move operation
            if(instruction.getOp() == Instruction::Move)
                handleMoveOperation(instruction, errors);
            // Handle reject operation
            if(instruction.getOp() == Instruction::Reject)
                handleRejectOperation(port, instruction, errors, rejected);
        }
        // Post all operations for this port:
        // Check that no container destined for this port was forgotten on the ship
        checkContainersForgottenOnShip(port, errors);
        // Check containers left on the port are only those destined for that port, or were originally on the port
        checkContainersLeftOnPort(port, original_containers, errors);

        PortContainers unloaded_containers;
        for (auto &container : port.getContainers()) {
            if (std::find(original_containers.begin(),
                          original_containers.end(), container) != original_containers.end())
                unloaded_containers.insert(container);
        }
        // Check that we rejected only the containers with the latest destinations
        checkLatestDestinationsRejected(port, unloaded_containers, distance_to_dest, errors);
        // Check that each got rejected properly by the algorithm
        checkUnloadedRejected(unloaded_containers, rejected, errors);
        // Check there's no more room on the ship for unloaded containers that should be loaded
        checkNoRoomForContainers(unloaded_containers, distance_to_dest, errors);
        m_ship.advanceCurrentPortIdx();
    }
    // TODO: Save errors and number of operations to a file
    (void)reported_errors;
    return run_failed;
}



void Simulation::handleUnloadOperation(Port &port, const Instruction &instruction, Errors &errors)
{
    if (!isRangeValid(m_ship.getPlan(), instruction))
    {
        errors.push_back(Error(Error::InvalidCommand, instruction));
    }
    else
    {
        std::shared_ptr<Container> container = m_ship.unloadContainer(instruction.getFloor(),
                                                                      instruction.getRow(), instruction.getCol());
        // Failed unloading from ship
        if (container == nullptr)
        {
            errors.push_back(
                    Error(Error::InvalidCraneOperation, instruction));
        }
            //container ID mismatch
        else if (container->getId() != instruction.getContainerId())
        {
            errors.push_back(Error(Error::InvalidCommand, instruction));
        }
            //container already on the port
        else if (!port.loadContainer(container))
        {
            errors.push_back(
                    Error(Error::InvalidCommand, instruction));
        }
    }
}

void Simulation::handleLoadOperation(Port &port, const Instruction &instruction, Errors &errors)
{
    //TODO check container wasn't rejected before?
    if(!isRangeValid(m_ship.getPlan(), instruction))
    {
        errors.push_back(Error(Error::InvalidCommand, instruction));
    }
    else
    {
        std::shared_ptr<Container> container = port.unloadContainer(instruction.getContainerId());
        // No such container on port
        if (container == nullptr) errors.push_back(Error(Error::InvalidCommand, instruction));
            // Failed to load container to ship
        else if (!m_ship.loadContainer(instruction.getFloor(), instruction.getRow(),
                                     instruction.getCol(), container))
        {
            if (m_ship.getContainerMap().count(instruction.getContainerId()))
                // ... because the container is already on the ship
                errors.push_back(Error(Error::InvalidCommand, instruction));
            else {
                // because the position for loading is invalid
                errors.push_back(Error(Error::InvalidCraneOperation, instruction));
            }
        } else {
            // Check if trying to load container with unreachable destination
            if (!isDestinationReachable(container))
                errors.push_back(Error(Error::InvalidCommand, instruction));
        }
    }
}

void Simulation::handleMoveOperation(const Instruction &instruction, Errors &errors)
{
    if (!isRangeValid(m_ship.getPlan(), instruction))
    {
        errors.push_back(Error(Error::InvalidCommand, instruction));
    } else
    {
        std::shared_ptr<Container> container = m_ship.unloadContainer(instruction.getFloor(),
                                                                     instruction.getRow(), instruction.getCol());
        // Failed unloading from ship
        if (container == nullptr)
        {
            errors.push_back(
                    Error(Error::InvalidCraneOperation, instruction));
        }
            //container ID mismatch
        else if (container->getId() != instruction.getContainerId())
        {
            errors.push_back(Error(Error::InvalidCommand, instruction));
        }
        else
        {
            // Failed loading container to the new position
            if (!m_ship.loadContainer(instruction.getNewFloor(), instruction.getNewRow(),
                                      instruction.getNewCol(), container))
            {
                if (m_ship.getContainerMap().count(instruction.getContainerId()))
                    // ... because the container is already on the ship
                    errors.push_back(Error(Error::InvalidCommand, instruction));
                else
                {
                    // because the position for loading is invalid
                    errors.push_back(Error(Error::InvalidCraneOperation, instruction));
                }
                // Return the container to its original placement
                m_ship.loadContainer(instruction.getFloor(),
                                       instruction.getRow(), instruction.getCol(), container);
            }
        }
    }
}

void Simulation::handleRejectOperation(Port& port, const Instruction& instruction, Errors& errors,
                                       std::vector<string>& rejected)
{
    // TODO check container was not rejected twice?
    // Check container is currently on the port
    if(port.getContainers().count(instruction.getContainerId()))
        errors.push_back(Error(Error::InvalidCommand, instruction));
    bool in_containers_to_load = false;
    // Check container was meant to be loaded
    for(auto& container : port.getContainersToLoad())
    {
        if(container->getId() == instruction.getContainerId())
            in_containers_to_load = true;
    }
    // Rejecting container that was not meant to be loaded
    if(!in_containers_to_load) errors.push_back(Error(Error::InvalidCommand, instruction));
    else rejected.push_back(instruction.getContainerId());
}

void Simulation::checkContainersForgottenOnShip(Port& port, Errors& errors)
{
    for (auto &container : m_ship.getContainerMap())
    {
        if (container.second.first->getPortCode() == port.getCode())
            errors.push_back(Error(Error::IgnoredContainer));
    }
}

void Simulation::checkContainersLeftOnPort(Port& port, PortContainers& original_containers, Errors& errors)
{
    for (auto &container : port.getContainers())
    {
        if (container.second->getPortCode() != port.getCode())
        {
            if (std::find(original_containers.begin(), original_containers.end(), container)
                == original_containers.end())
            {
                errors.push_back(Error(Error::IgnoredContainer));
            }
        }
    }
}

void Simulation::checkUnloadedRejected(PortContainers& unloaded_containers, std::vector<std::string>& rejected,
                                       Errors& errors)
{
    for (auto &container: unloaded_containers)
    {
        if (std::find(rejected.begin(), rejected.end(), container.second->getId()) == rejected.end())
            errors.push_back(Error(Error::IgnoredContainer));
    }
}

void Simulation::checkLatestDestinationsRejected(Port& port, PortContainers& unloaded_containers,
                                                 DistanceToDestinationComparator& distance_to_dest, Errors& errors)
{
    ContainersVector sorted_containers_to_load(port.getContainersToLoad().begin(),
                                               port.getContainersToLoad().end());
    std::sort(sorted_containers_to_load.begin(), sorted_containers_to_load.end(), distance_to_dest);
    // Minimal index from which we can reject containers
    size_t minimum_idx = port.getContainersToLoad().size() - unloaded_containers.size();
    if (minimum_idx < sorted_containers_to_load.size()) {
        // Minimal distance from which we can reject containers
        int minimum_distance = distance_to_dest.distanceToDestination(
                sorted_containers_to_load[minimum_idx]);
        for (auto &container : unloaded_containers) {
            int distance = distance_to_dest.distanceToDestination(container.second);
            if (distance < minimum_distance) {
                errors.push_back(Error(Error::IgnoredContainer));
            }
        }
    }
}

void Simulation::checkNoRoomForContainers(PortContainers& unloaded_containers,
                                          DistanceToDestinationComparator& distance_to_dest, Errors& errors)
{
    for (auto& container : unloaded_containers)
        if(distance_to_dest.distanceToDestination(container.second) < INT_MAX && !m_ship.isShipFull())
            errors.push_back(Error(Error::IgnoredContainer));
}


