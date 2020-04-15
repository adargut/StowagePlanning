#include "StowageAlgorithm.h"
#include <fstream>
#include <iostream>

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


void NaiveStowageAlgorithm::getInstructionsForUnloading(const ContainerMap &ship_map,
                                                        std::vector<int> containers_to_unload, const Plan &ship_plan,
                                                        Instructions &result) {
    Instructions tmp_instructions;
    ContainersVector containers_to_return;

    for (auto &container_on_ship : ship_map) {
        std::string port_code = ship->getRoute()[ship->getPortIndex()];
        const Container *curr_container = container_on_ship.second.first;

        if (curr_container->getPortCode() == port_code) { // Container needs to be unloaded here
            containers_to_unload.push_back(curr_container->getId());
        }
    }

    for (auto &container_to_unload : containers_to_unload) {
        tmp_instructions.clear();
        // TODO implement rollback/backup mechanism
        auto container_pos = ship_map.find(container_to_unload)->second.second;
        // TODO make this size_t? for all ints in project??
        int z = container_pos[0];
        int y = container_pos[1];
        int x = container_pos[2];

        for (int z_above = ship->getPlan().size() - 1; z_above > z; z_above--) {
            int container_above_id = ship_plan[z_above][y][x];

            if (container_above_id > 0) { // Position of a container above container to be unloaded
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
            const Container* container_to_return = containers_to_return[i];
            int new_z = z + containers_to_return.size() - i; // New z for reloading the unloaded container
            ship->loadContainer(new_z, y, x, container_to_return);
            tmp_instructions.push_back(Instruction(Instruction::Load, container_to_return->getId(), new_z, y, x));
        }

        for (Instruction instruction : tmp_instructions) {
            result.push_back(instruction);
        }
    }
}

void NaiveStowageAlgorithm::getInstructionForLoadingContainer(const Plan &ship_plan, Instructions &result,
                                                              const Container *const container_to_load) {
    for (int z = 0; z < ship_plan.size(); z++) { // TODO optimize this n^3 loop
        for (int y = 0; y < ship_plan[0].size(); y++) {
            for (int x = 0; x < ship_plan[0][0].size(); x++) {
                if (ship_plan[z][y][x] == 0) {
                    // TODO check calculator
                    // TODO check if container destination still in route (beyond the current port)
                    ship->loadContainer(z, y, x, container_to_load);
                    result.push_back(Instruction(Instruction::Load, container_to_load->getId(), z, y, x));
                    return;
                }
            }
        }
    }
        result.push_back(Instruction(Instruction::Reject, container_to_load->getId(), -1, -1, -1));
}

void NaiveStowageAlgorithm::getInstructionsForLoading(const Plan &ship_plan,
                                                      Instructions &result,
                                                      ContainersVector& sorted_containers_to_load)
    {
    for (auto container_to_load : sorted_containers_to_load) {
        getInstructionForLoadingContainer(ship_plan, result, container_to_load);
        }
}

Instructions NaiveStowageAlgorithm::getInstructionsForCargo(const ContainersVector &containers_to_load) {
    using Cmp = Utility::DistanceToDestinationComparator;
    Cmp distance_to_destination(ship->getPortIndex(), ship->getRoute());
    Instructions result;
    Instructions tmp_instructions;
    std::vector<int> containers_to_unload;
    ContainersVector containers_to_return;

    // We want to load the containers closest to their destination first, so we sort them
    ContainersVector sorted_containers_to_load(containers_to_load.begin(), containers_to_load.end());
    std::sort(sorted_containers_to_load.begin(), sorted_containers_to_load.end(), distance_to_destination);
    WeightBalanceCalculator *calculator = ship->getCalculator();

    const ContainerMap &ship_map = ship->getContainerMap();
    const Plan &ship_plan = ship->getPlan();

    // Call helper functions, store their output in result
    getInstructionsForUnloading(ship_map, containers_to_unload, ship_plan, result);
    getInstructionsForLoading(ship_plan, result, sorted_containers_to_load);

    ship->advanceCurrentPortIdx();
    return result;
}

NaiveStowageAlgorithm::NaiveStowageAlgorithm() {
    algorithm_name = "Naive Algorithm";
}
