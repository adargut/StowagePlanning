//
// Created by Nir on 13/04/2020.
//

#include "Simulation.h"
#include "AlgorithmError.h"

//TODO move me
bool isRangeValid(const Plan& plan, Instruction& instruction)
{
    if(instruction.getFloor() < 0 || instruction.getFloor() >= plan.size()) return false;
    if(instruction.getRow() < 0 || instruction.getFloor() >= plan[0].size()) return false;
    return !(instruction.getCol() < 0 || instruction.getFloor() >= plan[0][0].size());
}

bool isDestinationReachable(const Ship& ship, const Container * container)
{
    for (int i = ship.getPortIndex()+1; i < ship.getRoute().size(); i++) {
        if(ship.getRoute()[i] == container->getPortCode()) return true;
    }
    return false;
}

Simulation::Simulation(const Ports& _ports, const Plan& _plan, const Route& _route,
                       WeightBalanceCalculator* _calculator, StowageAlgorithm* _algorithm)
                       : ship(_plan, _route, _calculator), algorithm(_algorithm), ports(_ports) {}

bool Simulation::run_simulation()
{
    AlgorithmErrors errors;
    algorithm->reset(ship.getPlan(), ship.getRoute(), ship.getCalculator());
    int number_of_operations = 0;
    for (auto& port : ports)
    {
        std::vector<int> rejected; // Vector to keep track of rejected container id's for this port
        Port::PortContainers original_containers(port.getContainers());
        Instructions instructions = algorithm->getInstructionsForCargo(port.getContainersToLoad());
        number_of_operations+=instructions.size();
        for (auto& instruction : instructions)
        {
            //handle Unload operation
            if(instruction.getOp() == Instruction::Unload)
            {
                if(!isRangeValid(ship.getPlan(), instruction))
                {
                    errors.push_back(AlgorithmError(AlgorithmError::InvalidCommand));
                }
                else
                {
                    const Container * container = ship.unloadContainer(instruction.getFloor(),
                            instruction.getRow(), instruction.getCol());
                    // Failed unloading from ship
                    if(container == nullptr) errors.push_back(AlgorithmError(AlgorithmError::InvalidCraneOperation));
                    //container ID mismatch
                    else if (container->getId() != instruction.getContainerId())
                        errors.push_back(AlgorithmError(AlgorithmError::InvalidCommand));
                    //container already on the port
                    else if(!port.loadContainer(container)) errors.push_back(AlgorithmError(AlgorithmError::InvalidCommand));
                }
            }

            //handle load operation
            if(instruction.getOp() == Instruction::Load)
            {
                if(!isRangeValid(ship.getPlan(), instruction))
                {
                    errors.push_back(AlgorithmError(AlgorithmError::InvalidCommand));
                }
                else
                {
                    const Container * container = port.unloadContainer(instruction.getContainerId());
                    // No such container on port
                    if (container == nullptr) errors.push_back(AlgorithmError(AlgorithmError::InvalidCommand));
                    // Failed to load container to ship
                    if(!ship.loadContainer(instruction.getFloor(), instruction.getRow(), instruction.getCol(), container))
                    {
                        if(ship.getContainerMap().count(instruction.getContainerId()))
                            // ... because the container is already on the ship
                            errors.push_back(AlgorithmError(AlgorithmError::InvalidCommand));
                        else
                            errors.push_back(AlgorithmError(AlgorithmError::InvalidCraneOperation));
                    }
                    else
                    {
                        // Check if trying to load container with unreachable destination
                        if(!isDestinationReachable(ship, container))
                            errors.push_back(AlgorithmError(AlgorithmError::InvalidCommand));
                    }
                }
            }

            //handle reject operation
            if(instruction.getOp() == Instruction::Reject)
            {
                bool in_containers_to_load = false;
                for(auto& container : port.getContainersToLoad())
                {
                    if(container->getId() == instruction.getContainerId())
                        in_containers_to_load = true;
                }
                // Rejecting container that was not meant to be loaded
                if(!in_containers_to_load) errors.push_back(AlgorithmError(AlgorithmError::InvalidCommand));
                else
                {
                    if(!ship.is_ship_full()) errors.push_back(AlgorithmError(AlgorithmError::IgnoredContainer));
                    rejected.push_back(instruction.getContainerId());
                }
            }
        }

        // Check containers left on the port are only those that were originally on the port
        for (auto& container : port.getContainers())
        {
            if(std::find(original_containers.begin(), original_containers.end(), container) == original_containers.end())
                errors.push_back(AlgorithmError(AlgorithmError::IgnoredContainer));
        }

        // Check that we rejected only the containers with the latest destinations
        using Cmp = Utility::DistanceToDestinationComparator;
        Cmp distance_to_destination(ship.getPortIndex(), ship.getRoute());
        ContainersVector sorted_containers_to_load(port.getContainersToLoad().begin(), port.getContainersToLoad().end());
        std::sort(sorted_containers_to_load.begin(), sorted_containers_to_load.end(), distance_to_destination);
        int minimum_idx = port.getContainersToLoad().size() - port.getContainers().size();
        for (auto& container : port.getContainers())
        {
            int j = -1;
            for (int i = 0; i < sorted_containers_to_load.size(); ++i) {
                if(sorted_containers_to_load[i] == container.second) j = i;
            }
            if(j < minimum_idx) errors.push_back(AlgorithmError(AlgorithmError::IgnoredContainer));
        }

        // Check that each got rejected properly by the algorithm
        for (auto &container: port.getContainers()) {
            if (std::find(rejected.begin(), rejected.end(), container.second->getId()) == rejected.end())
                errors.push_back(AlgorithmError(AlgorithmError::IgnoredContainer));
        }

        ship.advanceCurrentPortIdx();
        // Save instructions for port to a file
        Utility::savePortInstructions(port.getCode(), instructions); // TODO change arguments here..
    }
    // Save errors and number of operations to a file
    Utility::saveSimulationErrors("somepath.txt", errors);
    Utility::saveSimulationResult("respath.txt", number_of_operations);

    //TODO return value?
    return false;
}
