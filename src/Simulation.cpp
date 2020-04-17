#include "Simulation.h"

static bool isRangeValid(const Plan &plan, const Instruction &instruction) {
    if (instruction.getFloor() < 0 || instruction.getFloor() >= plan.size()) return false;
    if (instruction.getRow() < 0 || instruction.getFloor() >= plan[0].size()) return false;
    return !(instruction.getCol() < 0 || instruction.getFloor() >= plan[0][0].size());
}

static bool isDestinationReachable(const Ship &ship, const Container *container) {
    for (int i = ship.getPortIndex()+1; i < ship.getRoute().size(); i++) {
        if(ship.getRoute()[i] == container->getPortCode()) return true;
    }
    return false;
}

static int count_instructions(Instructions& instructions) {
    int counter = 0;

    for (auto& instruction : instructions)
        if(instruction.getOp() != Instruction::Reject) counter++;
    return counter;
}

static void handle_unload_operation(Port& port, Ship& ship, AlgorithmErrors& errors, const Instruction& instruction) {
    if (!isRangeValid(ship.getPlan(), instruction)) {
        errors.push_back(AlgorithmError(AlgorithmError::InvalidCommand));
    }
    else {
        Container *container = ship.unloadContainer(instruction.getFloor(),
                                                    instruction.getRow(), instruction.getCol());
        // Failed unloading from ship
        if (container == nullptr)
            errors.push_back(
                    AlgorithmError(AlgorithmError::InvalidCraneOperation));
            //container ID mismatch
        else if (container->getId() != instruction.getContainerId())
            errors.push_back(AlgorithmError(AlgorithmError::InvalidCommand));
            //container already on the port
        else if (!port.loadContainer(container))
            errors.push_back(
                    AlgorithmError(AlgorithmError::InvalidCommand));
    }
}

static void handle_load_operation(Port& port, Ship& ship, AlgorithmErrors& errors, const Instruction& instruction) {
    if(!isRangeValid(ship.getPlan(), instruction))
    {
        errors.push_back(AlgorithmError(AlgorithmError::InvalidCommand));
    }
    else
    {
        Container * container = port.unloadContainer(instruction.getContainerId());
        // No such container on port
        if (container == nullptr) errors.push_back(AlgorithmError(AlgorithmError::InvalidCommand));
            // Failed to load container to ship
        else if (!ship.loadContainer(instruction.getFloor(), instruction.getRow(),
                                     instruction.getCol(), container)) {
            if (ship.getContainerMap().count(instruction.getContainerId()))
                // ... because the container is already on the ship
                errors.push_back(AlgorithmError(AlgorithmError::InvalidCommand));
            else
                errors.push_back(AlgorithmError(AlgorithmError::InvalidCraneOperation));
        } else {
            // Check if trying to load container with unreachable destination
            if (!isDestinationReachable(ship, container))
                errors.push_back(AlgorithmError(AlgorithmError::InvalidCommand));
        }
    }
}

static void handle_reject_operation(Port& port, Ship& ship, AlgorithmErrors& errors, const Instruction& instruction,
                                    std::vector<std::string>& rejected) {
    bool in_containers_to_load = false;

    for(auto& container : port.getContainersToLoad())
    {
        if(container->getId() == instruction.getContainerId())
            in_containers_to_load = true;
    }
    // Rejecting container that was not meant to be loaded
    if(!in_containers_to_load) errors.push_back(AlgorithmError(AlgorithmError::InvalidCommand));
    else rejected.push_back(instruction.getContainerId());
}

static void check_containers_forgotten_on_ship(Port& port, Ship& ship, AlgorithmErrors& errors) {
    for (auto &container : ship.getContainerMap()) {
        if (container.second.first->getPortCode() == port.getCode())
            errors.push_back(AlgorithmError(AlgorithmError::IgnoredContainer));
    }
}

static void check_containers_left_on_port(Port& port, Ship& ship, AlgorithmErrors& errors,
                                          Port::PortContainers& original_containers) {
    for (auto &container : port.getContainers()) {
        if (container.second->getPortCode() != port.getCode()) {
            if (std::find(original_containers.begin(),
                          original_containers.end(), container) == original_containers.end())
                errors.push_back(AlgorithmError(AlgorithmError::IgnoredContainer));
        }
    }
}

static void check_latest_destinations_rejected(Port& port, Ship& ship, AlgorithmErrors& errors,
                                               Port::PortContainers& unloaded_containers,
                                               Utility::DistanceToDestinationComparator distance_to_dest) {
    ContainersVector sorted_containers_to_load(port.getContainersToLoad().begin(),
                                               port.getContainersToLoad().end());
    std::sort(sorted_containers_to_load.begin(), sorted_containers_to_load.end(), distance_to_dest);
    size_t minimum_idx = port.getContainersToLoad().size() - unloaded_containers.size();
    if (minimum_idx < sorted_containers_to_load.size()) {
        int minimum_distance = distance_to_dest.distance_to_destination(
                sorted_containers_to_load[minimum_idx]);
        for (auto &container : unloaded_containers) {
            int distance = distance_to_dest.distance_to_destination(sorted_containers_to_load[minimum_idx]);
            if (distance < minimum_distance) {
                errors.push_back(AlgorithmError(AlgorithmError::IgnoredContainer));
            }
        }
    }
}

static void check_unloaded_rejected(Port& port, Ship& ship, AlgorithmErrors& errors,
                                    Port::PortContainers& unloaded_containers, std::vector<std::string>& rejected) {
    for (auto &container: unloaded_containers) {
        if (std::find(rejected.begin(), rejected.end(), container.second->getId()) == rejected.end())
            errors.push_back(AlgorithmError(AlgorithmError::IgnoredContainer));
    }
}

static void check_no_room_for_containers(Port& port, Ship& ship, AlgorithmErrors& errors,
                                         Port::PortContainers& unloaded_containers,
                                         Utility::DistanceToDestinationComparator distance_to_dest) {
    for (auto& container : unloaded_containers)
        if(distance_to_dest.distance_to_destination(container.second) < INT_MAX && !ship.is_ship_full())
            errors.push_back(AlgorithmError(AlgorithmError::IgnoredContainer));
}

Simulation::Simulation(Ports _ports, const Plan &_plan, const Route &_route,
                       WeightBalanceCalculator *_calculator,
                       StowageAlgorithm *_algorithm, std::string _travel_name)
        : ship(_plan, _route, _calculator), algorithm(_algorithm), ports(std::move(_ports)),
          travel_name(std::move(_travel_name)) {}

void Simulation::run_simulation() {
    AlgorithmErrors errors;
    algorithm->reset(ship.getPlan(), ship.getRoute(), ship.getCalculator());
    int number_of_operations = 0;
    for (auto& port : ports)
    {
        using Cmp = Utility::DistanceToDestinationComparator;
        Cmp distance_to_dest(ship.getPortIndex(), ship.getRoute());
        std::vector<std::string> rejected; // Vector to keep track of rejected container id's for this port
        Port::PortContainers original_containers(port.getContainers());
        Instructions instructions = algorithm->getInstructionsForCargo(port.getContainersToLoad());
        number_of_operations+=count_instructions(instructions);
        for (auto& instruction : instructions)
        {
            //handle unload operation
            if(instruction.getOp() == Instruction::Unload)
                handle_unload_operation(port, ship, errors, instruction);
            //handle load operation
            if(instruction.getOp() == Instruction::Load)
                handle_load_operation(port, ship, errors, instruction);
            //handle reject operation
            if(instruction.getOp() == Instruction::Reject)
                handle_reject_operation(port, ship, errors, instruction, rejected);
        }

        // Post all operations for this port:
        // Check that no container destined for this port was forgotten on the ship
        check_containers_forgotten_on_ship(port, ship, errors);
        // Check containers left on the port are only those destined for that port, or were originally on the port
        check_containers_left_on_port(port, ship, errors, original_containers);

        Port::PortContainers unloaded_containers;
        for (auto &container : port.getContainers()) {
            if (std::find(original_containers.begin(),
                          original_containers.end(), container) != original_containers.end())
                unloaded_containers.insert(container);
        }
        // Check that we rejected only the containers with the latest destinations
        check_latest_destinations_rejected(port, ship, errors, unloaded_containers, distance_to_dest);
        // Check that each got rejected properly by the algorithm
        check_unloaded_rejected(port, ship, errors, unloaded_containers, rejected);
        // Check there's no more room on the ship for unloaded containers that should be loaded
        check_no_room_for_containers(port, ship, errors, unloaded_containers, distance_to_dest);

        ship.advanceCurrentPortIdx();
        // Save instructions for port to a file
        Utility::savePortInstructions(instructions, algorithm->getAlgorithmName(),
                                      port.getCode(), travel_name);
    }
    // Save errors and number of operations to a file
    std::string error_string = AlgorithmError::errorsToString(errors);
    std::string result_string = std::to_string(number_of_operations);
    Utility::saveSimulation(result_string, algorithm->getAlgorithmName(), travel_name, SIMULATION_FILE);
    Utility::saveSimulation(error_string, algorithm->getAlgorithmName(), travel_name, SIMULATION_ERRORS);
}