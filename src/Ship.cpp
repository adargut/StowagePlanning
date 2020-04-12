#include "Ship.h"

Ship::Ship(const Plan &_plan, const Route &_route, WeightBalanceCalculator* _calculator) {
    plan = _plan;
    route = _route;
    calculator = _calculator;
}

const Plan& Ship::getPlan() const {
    return plan;
}

const Route& Ship::getRoute() const {
    return route;
}

const int& Ship::getPortIndex() const {
    return current_port_idx;
}

const ContainerMap& Ship::getContainerMap() const {
    return containers;
}

void Ship::updatePlan(int floor, int row, int col, int val) {
    plan[floor][row][col] = val;
}

// Insert container to map
void Ship::insertContainerMap(int floor, int row, int col, int id, const Container *const container) {
    Position pos = {floor, row, col};
    std::pair<const Container *const, Position> p(container, pos);
    ContainerMap::value_type item(id, p);
    containers.insert(item); //TODO:: maybe emplace instead
}

// Remove container from map
void Ship::eraseContainerMap(int floor, int row, int col) {
    containers.erase(plan[floor][row][col]);
}

bool Ship::loadContainer(int row, int col, const Container * const container_to_load) {
    int id = container_to_load->getId();
    if (containers.count(id)) return false; // Position is occupied or container in ship
    for (int floor = 0; floor < plan.size(); ++floor)
    {
        if(plan[floor][row][col] == 0)
        {
            insertContainerMap(floor, row, col, container_to_load->getId(), container_to_load);
            updatePlan(floor, row, col, id);
            return true;
        }
    }

    return false;
}

const Container * const Ship::unloadContainer(int row, int col) {
    // TODO make this return error so we know why it failed
    for (int floor = plan.size()-1; floor >= 0 ; --floor) {
        if(plan[floor][row][col] > 0)
        {
            const Container *const res = containers[plan[floor][row][col]].first;
            eraseContainerMap(floor, row, col);
            updatePlan(floor, row, col, 0);
            return res;
        }
    }
    return nullptr; // No container in this position

}

Ship::~Ship() {
    delete calculator;
}

WeightBalanceCalculator *Ship::getCalculator() const {
    return calculator;
}
