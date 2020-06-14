#include "Simulation.h"

// Constructor
Simulation::Simulation(std::unique_ptr<AbstractAlgorithm> algorithm, string algorithm_name,
                       const TravelData &travel_data) :
                       m_algorithm(std::move(algorithm)), m_algorithmName(std::move(algorithm_name)),
                       m_travel_data(travel_data), m_ports(travel_data.getPorts()), m_ship(travel_data.getShip()) {}

// Checks if instruction is in valid range for plan
static bool isRangeValid(const Plan &plan, const Instruction &instruction)
{
    if (instruction.getFloor() < 0 || instruction.getFloor() >= int(plan.size())) return false;
    if (instruction.getRow() < 0 || instruction.getRow() >= int(plan[0].size())) return false;
    if (instruction.getCol() < 0 || instruction.getCol() >= int(plan[0][0].size())) return false;
    if(instruction.getOp() == Instruction::Move)
    {
        if (instruction.getNewFloor() < 0 || instruction.getNewFloor() >= int(plan.size())) return false;
        if (instruction.getNewRow() < 0 || instruction.getNewRow() >= int(plan[0].size())) return false;
        if (instruction.getNewCol() < 0 || instruction.getNewCol() >= int(plan[0][0].size())) return false;
    }
    return true;
}

// Checks if container has destination reachable for ship
bool Simulation::isDestinationReachable(std::shared_ptr<const Container> container)
{
    for (int i = m_ship.getCurrentPortIdx(); i < int(m_ship.getRoute().size()); i++) {
        if(m_ship.getRoute()[i] == container->getPortCode()) return true;
    }
    return false;
}

// Initialize simulation
// TODO this function is not needed: most happens in constructor, rest needs to happen in preprocessing..
void Simulation::initialize()
{
    uint32_t err = 0;
    string plan_file = m_travel_data.getPlanPath();
    string route_file = m_travel_data.getRoutePath();

    auto wbc = WeightBalanceCalculator();
    err = m_algorithm->setWeightBalanceCalculator(wbc);
    if (err) m_algorithmErrors.emplace_back(err);
    err = m_algorithm->readShipRoute(route_file);
    if (err) m_algorithmErrors.emplace_back(err);
    AlgorithmError alg_init_errors = AlgorithmError(err);
    if(alg_init_errors.getBit(AlgorithmError::BadTravelFile)
       || alg_init_errors.getBit(AlgorithmError::SinglePortTravel))
    {
        m_canRun = false;
    }
    err = m_algorithm->readShipPlan(plan_file);
    if (err) m_algorithmErrors.push_back(AlgorithmError(err));
    alg_init_errors = AlgorithmError(err);
    if(alg_init_errors.getBit(AlgorithmError::BadPlanFile)
       || alg_init_errors.getBit(AlgorithmError::ConflictingXY))
    {
        m_canRun = false;
    }
}

// Run simulation
int Simulation::run()
{
    int number_of_operations = 0;
    uint32_t reported_errors;
    Errors errors;
    string crane_instructions_dir = m_travel_data.getOutputDir() + "/" + m_algorithmName + "_" +
                                    m_travel_data.getTravelName() + "_crane_instructions";
    fs::create_directories(crane_instructions_dir);
    if(!m_canRun)
    {
        errors.push_back(Error(
                "Algorithm failed to init properly, wasn't run for this travel"));
    }
    else
    for (auto& port : m_ports)
    {
        using Cmp = DistanceToDestinationComparator;
        Cmp distance_to_dest(m_ship.getCurrentPortIdx(), m_ship.getRoute());
        std::vector<std::string> rejected; // Vector to keep track of rejected container id's for this port
        PortContainers original_containers(port.getContainers());
        const string& port_code = port.getCode();
        string cargo_file = m_travel_data.getFullPath() + "/" + port_code + CARGO_SUFFIX;
        string crane_instructions_file = crane_instructions_dir + "/" + port_code + CRANE_INSTRUCTIONS_SUFFIX;
        reported_errors = m_algorithm->getInstructionsForCargo(cargo_file, crane_instructions_file);
        if (reported_errors) m_algorithmErrors.emplace_back(reported_errors);
        Instructions instructions;
        if(!InputUtility::readCraneInstructions(crane_instructions_file, instructions))
        {
            errors.push_back(Error(
                    "Bad/Missing crane instructions file for port " + port.getCode()));
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
        for (auto &container : port.getContainers())
        {
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
    string crane_errors_path = m_travel_data.getOutputDir() + "/" + ERRORS_DIR + "/" + m_algorithmName + UNDERSCORE +
                               m_travel_data.getTravelName() + SIMULATION_ERRORS_SUFFIX;
    string algorithm_errors_path = m_travel_data.getOutputDir() + "/" + ERRORS_DIR + "/" + m_algorithmName + UNDERSCORE +
                                   m_travel_data.getTravelName() + ALG_ERRORS_SUFFIX;
    // Flush errors into file
    OutputUtility::writeErrors(crane_errors_path, errors);
    OutputUtility::writeAlgorithmErrors(algorithm_errors_path, m_algorithmErrors);
    if(!errors.empty()) return -1;
    // TODO push into operations vector at position n (reserved slot for this pair)
    return number_of_operations;
}

// Handle unload operation
void Simulation::handleUnloadOperation(Port &port, const Instruction &instruction, Errors &errors)
{
    if (!isRangeValid(m_ship.getPlan(), instruction))
    {
        errors.push_back(Error(
                "Unload coordinates exceed ship's dimensions", instruction));
    }
    else
    {
        std::shared_ptr<Container> container = m_ship.unloadContainer(instruction.getFloor(),
                                                                      instruction.getRow(), instruction.getCol());
        // Failed unloading from ship
        if (container == nullptr)
        {
            errors.push_back(
                    Error(
                            "Failed unloading container from the ship", instruction));
        }
        // Container ID mismatch
        else if (container->getId() != instruction.getContainerId())
        {
            errors.push_back(Error(
                    "ID mismatch with container on ship", instruction));
        }
        // Container already on the port
        else if (!port.loadContainer(container))
        {
            errors.push_back(
                    Error("Container already on the port", instruction));
        }
    }
}

// Handle load operation
void Simulation::handleLoadOperation(Port &port, const Instruction &instruction, Errors &errors)
{
    if(!isRangeValid(m_ship.getPlan(), instruction))
    {
        errors.push_back(Error(
                "Load coordinates exceed ship's dimensions", instruction));
    }
    else
    {
        std::shared_ptr<Container> container = port.unloadContainer(instruction.getContainerId());
        // No such container on port
        if (container == nullptr) errors.push_back(Error(
                    "Container not on port", instruction));
            // Failed to load container to ship
        else if (!m_ship.loadContainer(instruction.getFloor(), instruction.getRow(),
                                     instruction.getCol(), container))
        {
            if (m_ship.getContainerMap().count(instruction.getContainerId()))
                // ... because the container is already on the ship
                errors.push_back(Error("Container already on ship", instruction));
            else {
                // because the position for loading is invalid
                errors.push_back(Error("Invalid load position", instruction));
            }
        } else {
            // Check if trying to load container with unreachable destination
            if (!isDestinationReachable(container))
                errors.push_back(Error(
                        "Loaded container with unreachable destination", instruction));
        }
    }
}

// Handle move operation
void Simulation::handleMoveOperation(const Instruction &instruction, Errors &errors)
{
    if (!isRangeValid(m_ship.getPlan(), instruction))
    {
        errors.push_back(Error(
                "Move coordinates exceed ship's dimensions", instruction));
    } 
    else
    {
        std::shared_ptr<Container> container = m_ship.unloadContainer(instruction.getFloor(),
                                                                     instruction.getRow(), instruction.getCol());
        // Failed unloading from ship
        if (container == nullptr)
        {
            errors.push_back(
                    Error("Failed unloading from ship", instruction));
        }
            //container ID mismatch
        else if (container->getId() != instruction.getContainerId())
        {
            errors.push_back(Error(
                    "ID mismatch with container on ship", instruction));
        }
        else
        {
            // Failed loading container to the new position
            if (!m_ship.loadContainer(instruction.getNewFloor(), instruction.getNewRow(),
                                      instruction.getNewCol(), container))
            {
                if (m_ship.getContainerMap().count(instruction.getContainerId()))
                    // ... because the container is already on the ship
                    errors.push_back(Error(
                            "When loading, container is already on the ship", instruction));
                else
                {
                    // because the position for loading is invalid
                    errors.push_back(Error(
                            "Invalid load position", instruction));
                }
                // Return the container to its original placement
                m_ship.loadContainer(instruction.getFloor(),
                                       instruction.getRow(), instruction.getCol(), container);
            }
        }
    }
}

// Handle reject operation
void Simulation::handleRejectOperation(Port& port, const Instruction& instruction, Errors& errors,
                                       std::vector<string>& rejected)
{
    // Check container is currently on the port
    if(!port.getContainers().count(instruction.getContainerId()))
        errors.push_back(Error("Rejected container not on port", instruction));
    bool in_containers_to_load = false;
    // Check container was meant to be loaded
    for(auto& container : port.getContainersToLoad())
    {
        if(container->getId() == instruction.getContainerId())
            in_containers_to_load = true;
    }
    // Rejecting container that was not meant to be loaded
    if(!in_containers_to_load) errors.push_back(Error(
                "Rejecting container that wasn't meant to be loaded", instruction));
    else rejected.push_back(instruction.getContainerId());
}

// Check if we left a container on ship that could've been unloaded
void Simulation::checkContainersForgottenOnShip(Port& port, Errors& errors)
{
    for (auto &container : m_ship.getContainerMap())
    {
        if (container.second.first->getPortCode() == port.getCode())
            errors.push_back(Error(
                    "A container destined for " + port.getCode() + " was forgotten on the ship"));
    }
}

// Check if we left a container on port that could've been loaded
void Simulation::checkContainersLeftOnPort(Port& port, PortContainers& original_containers, Errors& errors)
{
    for (auto &container : port.getContainers())
    {
        if (container.second->getPortCode() != port.getCode())
        {
            if (std::find(original_containers.begin(), original_containers.end(), container)
                == original_containers.end())
            {
                errors.push_back(Error(
                        "Container left on " + port.getCode() +
                        " wasn't destined for that port nor originally on the port"));
            }
        }
    }
}

// Check if algorithm didn't load a container, but forgot to reject it
void Simulation::checkUnloadedRejected(PortContainers& unloaded_containers, std::vector<std::string>& rejected,
                                       Errors& errors)
{
    for (auto &container: unloaded_containers)
    {
        if (std::find(rejected.begin(), rejected.end(), container.second->getId()) == rejected.end())
            errors.push_back(Error(
                    "Container that wasn't loaded didn't get rejected"));
    }
}

// Check if containers rejected are actually the farthest, as in the soritng by distance works
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
                errors.push_back(Error(
                        "Could reject a container with further destination (" + port.getCode() + ")"));
            }
        }
    }
}

// Check if we left a container on port but the ship isn't full
void Simulation::checkNoRoomForContainers(PortContainers& unloaded_containers,
                                          DistanceToDestinationComparator& distance_to_dest, Errors& errors)
{
    for (auto& container : unloaded_containers)
        if(distance_to_dest.distanceToDestination(container.second) < INT_MAX && !m_ship.isShipFull()
        && !m_ship.hasContainer(container.first))
        {
            errors.push_back(Error(
                    container.first + " which could be loaded was left on port while "
                                      "there's still room on the ship"));
        }
}

// Sets the container's <PORT_NAME>_* for * the real integer representing the visit number for its unload
void Simulation::setRealDestinations(const Route& route, int curr_idx, ContainersVector& containers)
{
    for (auto& container : containers)
    {
        string destination = container->getPortCode();
        container->setPortCode(BAD_DESTINATION);
        for (size_t i = curr_idx; i < route.size(); ++i)
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
