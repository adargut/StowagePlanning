//
// Created by osboxes on 5/14/20.
//

#include "Ship.h"

const Route &Ship::getRoute() const
{
    return m_route;
}

void Ship::setRoute(const Route &mRoute)
{
    m_route = mRoute;
}

const Plan &Ship::getPlan() const
{
    return m_plan;
}

void Ship::setPlan(const Plan &mPlan)
{
    m_plan = mPlan;
}

int Ship::getCurrentPortIdx() const
{
    return m_currentPortIdx;
}

const ContainerMap &Ship::getContainerMap() const {
    return m_containers;
}

bool Ship::loadContainer(int floor, int row, int col, std::shared_ptr<Container> container_to_load) {
    if (floor < 0 || row < 0 || col < 0 || floor > int(m_plan.size()) || row > int(m_plan[0].size()) ||
        col > int(m_plan[0][0].size())) {
        return false;
    }
    const std::string& id = container_to_load->getId();
    // Position is occupied or container in ship
    if (m_plan[floor][row][col] != FREE_POS || m_containers.count(id)) return false;
    if (floor != 0) {
        if (m_plan[floor - 1][row][col] == FREE_POS) return false; // Trying to place container "in the air"
    }
    if (floor != int(m_plan.size() - 1)) {
        if (m_plan[floor + 1][row][col] != FREE_POS) return false; // Trying to place container below an existing one
    }
    insertContainerMap(floor, row, col, container_to_load->getId(), container_to_load);
    updatePlan(floor, row, col, id);
    return true;
}

std::shared_ptr<Container> Ship::unloadContainer(int floor, int row, int col) {
    if (floor < 0 || row < 0 || col < 0 || floor > int(m_plan.size()) || row > int(m_plan[0].size()) ||
        col > int(m_plan[0][0].size())) {
        return nullptr;
    }
    if (m_plan[floor][row][col] == FREE_POS ||
        m_plan[floor][row][col] == ILLEGAL_POS) return nullptr; // Position is free or illegal
    if (floor != int(m_plan.size() - 1)) {
        if (m_plan[floor + 1][row][col] != FREE_POS) return nullptr; // There's a container above the container to unload
    }
    std::shared_ptr<Container> res = m_containers[m_plan[floor][row][col]].first;
    eraseContainerMap(floor, row, col);
    updatePlan(floor, row, col, std::string(FREE_POS));
    return res;
}

void Ship::setCurrentPortIdx(int mCurrentPortIdx)
{
    m_currentPortIdx = mCurrentPortIdx;
}

void Ship::advanceCurrentPortIdx() {
    m_currentPortIdx++;
}

bool Ship::isShipFull() {
    for (int z = 0; z < int(m_plan.size()); z++) {
        for (int y = 0; y < int(m_plan[0].size()); y++) {
            for (int x = 0; x < int(m_plan[0][0].size()); x++) {
                if(m_plan[z][y][x] == FREE_POS) return false;
            }
        }
    }
    return true;
}

void Ship::updatePlan(int floor, int row, int col, const std::string& val) {
    m_plan[floor][row][col] = val;
}

// Insert container to map
void Ship::insertContainerMap(int floor, int row, int col, const std::string& id, std::shared_ptr<Container> container) {
    std::pair<std::shared_ptr<Container>, Position> p(container, Position{floor, row, col});
    ContainerMap::value_type item(id, p);
    m_containers.insert(item);
}

// Remove container from map
void Ship::eraseContainerMap(int floor, int row, int col) {
    m_containers.erase(m_plan[floor][row][col]);
}
