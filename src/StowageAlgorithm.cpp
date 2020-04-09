#include "StowageAlgorithm.h"
#include <fstream>
#include <iostream>

NaiveStowageAlgorithm::NaiveStowageAlgorithm(const Plan& _plan, const Route& _route,
                                             WeightBalanceCalculator* _calculator) {
    ship = new Ship(_plan, _route, _calculator);
}

// TODO break this into sub functions
Instructions NaiveStowageAlgorithm::getInstructionsForCargo(const ContainersVector &containers_to_load) {
    Instructions result;
    Instructions tmp_instructions;
    std::vector<int> containers_to_unload;
    ContainersVector containers_to_return;
    int port_idx = ship->getPortIndex();
    const ContainerMap& ship_map = ship->getContainerMap();
    const Plan& ship_plan = ship->getPlan();

    // Containers that need to be unloaded at port
    for (auto& container_on_ship : ship_map) {
        std::string port_code = ship->getRoute()[port_idx];
        const Container* curr_container = container_on_ship.second.first;

        if (curr_container->getPortCode() == port_code) { // Container needs to be unloaded here
            containers_to_unload.push_back(curr_container->getId());
        }
    }

    for (auto& container_id : containers_to_unload) {
        // TODO implement rollback/backup mechanism
        auto container_pos = ship_map.find(container_id)->second.second;
        // TODO make this size_t? for all ints in project??
        int z = container_pos[0];
        int x = container_pos[1];
        int y = container_pos[2];

        for (int z_above = ship->getPlan().size() - 1; z_above > z; z_above--) {
            int position_above = ship_plan[z_above][x][y];

            if (position_above > 0) { // Position of a container above container to be unloaded
                containers_to_return.push_back(ship_map[position_above]);
                ship->unloadContainer(position_above[0], position_above[1], position_above[2]);
                tmp_instructions.push_back(Instruction(Instruction::Unload, position_above, z_above, x, y));
            }
        }
        // TODO check weight balancer before
        ship->unloadContainer(z, x, y); // Unload container originally intended for unloading
        tmp_instructions.push_back(Instruction(Instruction::Unload, container_id, z, x, y));

        // Load all containers above container popped back into the ship
        for (int i = containers_to_return.size() - 1; i >= 0; i--) {
            const Container* container_to_return = containers_to_return[i];
            int new_z = z + containers_to_return.size() - i; // New z for reloading the unloaded container
            ship->loadContainer(new_z, x, y, container_to_return);
            tmp_instructions.push_back(Instruction(Instruction::Load, container_to_return->getId(), new_z, x, y));
        }

        for (Instruction instruction : tmp_instructions) {
            result.push_back(instruction);
        }
    }

    int x = 0, y = 0, z = 0;
    // Containers that need to be loaded from port
    for (auto container_to_load : containers_to_load) {
        for (int z = 0; z < ship_plan.size(); z++) { // TODO optimize this n^3 loop
            for (int x = 0; x < ship_plan[0].size(); x++) {
                for (int y = 0; y < ship_plan[0][0].size(); y++) {
                    if (ship_plan[z][x][y] == 0) {
                        // TODO check calculator
                        ship->loadContainer(z, x, y, container_to_load);
                        result.push_back(Instruction(Instruction::Load, container_to_load->getId(), z, x, y));
                    }
                }
            }
        }
    }
    return result;
}