#include "StowageAlgorithm.h"
#include <iostream>

// Utility functions used by getInstructionsForCargo
static void getInstructionsForUnloading(Ship *ship,
                                        Instructions &result) {
    Instructions tmp_instructions;
    ContainersVector containers_to_return;
    std::vector<std::string> containers_to_unload;
    const Plan &ship_plan = ship->getPlan();
    const ContainerMap &ship_map = ship->getContainerMap();

    for (auto &container_on_ship : ship_map) {
        std::string port_code = ship->getRoute()[ship->getPortIndex()];
        const Container *curr_container = container_on_ship.second.first;
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
        for (int z_above = ship->getPlan().size() - 1; z_above > z; z_above--) {
            std::string container_above_id = ship_plan[z_above][y][x];
            // Position of a container above container to be unloaded
            if (container_above_id != FREE_POS && container_above_id != ILLEGAL_POS) {
                containers_to_return.push_back(ship_map.find(container_above_id)->second.first);
                ship->unloadContainer(z, y, x);
                tmp_instructions.push_back(Instruction(Instruction::Unload, container_above_id, z_above, y, x));
            }
        }
        // TODO check weight balancer before
        ship->unloadContainer(z, y, x); // Unload container originally intended for unloading
        tmp_instructions.push_back(Instruction(Instruction::Unload, container_to_unload, z, y, x));

        // Load all containers above container popped back into the ship
        for (int i = containers_to_return.size() - 1; i >= 0; i--) {
            Container* container_to_return = containers_to_return[i];
            int new_z = z + containers_to_return.size() - i; // New z for reloading the unloaded container
            ship->loadContainer(new_z, y, x, container_to_return);
            tmp_instructions.push_back(Instruction(Instruction::Load, container_to_return->getId(), new_z, y, x));
        }
        for (Instruction instruction : tmp_instructions) {
            result.push_back(instruction);
        }
    }
}

static void getInstructionForLoadingContainer(Ship *ship, Instructions &result,
                                              Container * container_to_load) {
    const Plan &ship_plan = ship->getPlan();
    bool destination_in_route = false;
    for (int i = ship->getPortIndex() + 1; i < ship->getRoute().size(); ++i) {
        if (container_to_load->getPortCode() == ship->getRoute()[i]) destination_in_route = true;
    }

    // Container destination unreachable
    if (!destination_in_route) {
        result.push_back(Instruction(Instruction::Reject,
                                     container_to_load->getId(), -1, -1, -1));
        return;
    }

    // Container already on the ship
    if(ship->getContainerMap().count(container_to_load->getId()))
    {
        result.push_back(Instruction(Instruction::Reject, container_to_load->getId(), -1, -1, -1));
        return;
    }
    for (int z = 0; z < ship_plan.size(); z++) { // TODO optimize this n^3 loop
        for (int y = 0; y < ship_plan[0].size(); y++) {
            for (int x = 0; x < ship_plan[0][0].size(); x++) {
                if (ship_plan[z][y][x] == FREE_POS) {
                    // TODO check calculator
                    // Check if container destination still in route (beyond the current port)
                    ship->loadContainer(z, y, x, container_to_load);
                    result.push_back(Instruction(Instruction::Load, container_to_load->getId(), z, y, x));
                    return;
                }
            }
        }
    }
    result.push_back(Instruction(Instruction::Reject, container_to_load->getId(), -1, -1, -1));
}

static void getInstructionsForLoading(Ship *ship,
                                      Instructions &result,
                                      ContainersVector &sorted_containers_to_load) {
    for (auto container_to_load : sorted_containers_to_load) {
        getInstructionForLoadingContainer(ship, result, container_to_load);
    }
}

void NaiveStowageAlgorithm::reset(const Plan &_plan, const Route &_route, WeightBalanceCalculator *_calculator) {
    if (ship != nullptr) delete (ship);
    ship = new Ship(_plan, _route, _calculator);
}

const std::string &StowageAlgorithm::getAlgorithmName() const {
    return algorithm_name;
}

NaiveStowageAlgorithm::~NaiveStowageAlgorithm() {
    if (ship != nullptr) delete (ship);
}

NaiveStowageAlgorithm::NaiveStowageAlgorithm() {
    algorithm_name = "Naive Algorithm";
}

Instructions NaiveStowageAlgorithm::getInstructionsForCargo(const ContainersVector &containers_to_load) {
    using Cmp = Utility::DistanceToDestinationComparator;
    Cmp distance_to_destination(ship->getPortIndex(), ship->getRoute());
    Instructions result;
    Instructions tmp_instructions;
    std::vector<std::string> containers_to_unload;
    ContainersVector containers_to_return;

    // We want to load the containers closest to their destination first, so we sort them
    ContainersVector sorted_containers_to_load(containers_to_load.begin(), containers_to_load.end());
    std::sort(sorted_containers_to_load.begin(), sorted_containers_to_load.end(), distance_to_destination);
    WeightBalanceCalculator *calculator = ship->getCalculator();

    const ContainerMap &ship_map = ship->getContainerMap();
    const Plan &ship_plan = ship->getPlan();

    // Call helper functions, store their output in result
    getInstructionsForUnloading(ship, result);
    getInstructionsForLoading(ship, result, sorted_containers_to_load);

    ship->advanceCurrentPortIdx();
    return result;
}