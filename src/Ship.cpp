#include "Ship.h"

Ship::Ship(const Plan &_plan, const Route &_route, WeightBalanceCalculator* _calculator) {
    plan = _plan;
    route = _route;
    calculator = _calculator;
}

const Plan &Ship::getPlan() const {
    return plan;
}

const Route &Ship::getRoute() const {
    return route;
}

const int& Ship::getPortIndex() const {
    return current_port_idx;
}

const ContainerMap &Ship::getContainerMap() const {
    return containers;
}

void Ship::updatePlan(int floor, int row, int col, const std::string& val) {
    plan[floor][row][col] = val;
}

// Insert container to map
void Ship::insertContainerMap(int floor, int row, int col, const std::string& id, Container * container) {
    std::pair<Container *, Position> p(container, Position{floor, row, col});
    ContainerMap::value_type item(id, p);
    containers.insert(item);
}

// Remove container from map
void Ship::eraseContainerMap(int floor, int row, int col) {
    containers.erase(plan[floor][row][col]);
}

bool Ship::loadContainer(int floor, int row, int col, Container * container_to_load) {
    if (floor < 0 || row < 0 || col < 0 || floor > plan.size() || row > plan[0].size() || col > plan[0][0].size()) {
        return false;
    }
    const std::string& id = container_to_load->getId();
    // Position is occupied or container in ship
    if (plan[floor][row][col] != FREE_POS || containers.count(id)) return false;
    if (floor != 0) {
        if (plan[floor - 1][row][col] == FREE_POS) return false; // Trying to place container "in the air"
    }
    if (floor != plan.size() - 1) {
        if (plan[floor + 1][row][col] != FREE_POS) return false; // Trying to place container below an existing one
    }
    insertContainerMap(floor, row, col, container_to_load->getId(), container_to_load);
    updatePlan(floor, row, col, id);
    return true;
}

Container * Ship::unloadContainer(int floor, int row, int col) {
    if (floor < 0 || row < 0 || col < 0 || floor > plan.size() || row > plan[0].size() || col > plan[0][0].size()) {
        return nullptr;
    }
    if (plan[floor][row][col] == FREE_POS ||
    plan[floor][row][col] == ILLEGAL_POS) return nullptr; // Position is free or illegal
    if (floor != plan.size() - 1) {
        if (plan[floor + 1][row][col] != FREE_POS) return nullptr; // There's a container above the container to unload
    }
    Container * res = containers[plan[floor][row][col]].first;
    eraseContainerMap(floor, row, col);
    updatePlan(floor, row, col, std::string(FREE_POS));
    return res;
}

WeightBalanceCalculator *Ship::getCalculator() const {
    return calculator;
}

void Ship::advanceCurrentPortIdx() {
    current_port_idx++;
}

bool Ship::isShipFull() {
    for (int z = 0; z < plan.size(); z++) {
        for (int y = 0; y < plan[0].size(); y++) {
            for (int x = 0; x < plan[0][0].size(); x++) {
                if(plan[z][y][x] == FREE_POS) return false;
            }
        }
    }
    return true;
}
