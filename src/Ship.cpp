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

int Ship::getPortIndex() const {
    return current_port_idx;
}

const ContainerMap &Ship::getContainerMap() const {
    return containers;
}

void Ship::updatePlan(int floor, int row, int col, int val) {
    plan[floor][row][col] = val;
}

// Insert container to map
void Ship::insertContainerMap(int floor, int row, int col, int id, const Container *const container) {
    std::pair<const Container *const, Position> p(container, Position(floor, row, col));
    ContainerMap::value_type item(id, p);
    containers.insert(item); //TODO:: maybe emplace instead
}

// Remove container from map
void Ship::eraseContainerMap(int floor, int row, int col) {
    containers.erase(plan[floor][row][col]);
}

bool Ship::loadContainer(int floor, int row, int col, const Container *const container_to_load) {
    int id = container_to_load->getId();
    if (plan[floor][row][col] != 0 || containers.count(id)) return false; // Position is occupied or container in ship
    insertContainerMap(floor, row, col, container_to_load->getId(), container_to_load);
    updatePlan(floor, row, col, id);
    return true;
}

const Container *Ship::unloadContainer(int floor, int row, int col) {
    // TODO make this return error so we know why it failed
    if (plan[floor][row][col] <= 0) return nullptr; // Position is free or illegal
    const Container *const res = containers[plan[floor][row][col]].first;
    eraseContainerMap(floor, row, col);
    updatePlan(floor, row, col, 0);
    return res;
}

Ship::~Ship() {
    delete calculator;
}
