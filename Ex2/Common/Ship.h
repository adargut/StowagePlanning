//
// Created by osboxes on 5/14/20.
//

#ifndef EX2_SHIP_H
#define EX2_SHIP_H

#include "GeneralUtility.h"
#include "Container.h"

class Ship
{
private:
    Route m_route;
    Plan m_plan;
    int m_currentPortIdx = 0;
    ContainerMap m_containers;
public:
    const Route &getRoute() const;
    void setRoute(const Route &mRoute);
    const Plan &getPlan() const;
    void setPlan(const Plan &mPlan);
    size_t getCurrentPortIdx() const;
    void setCurrentPortIdx(int mCurrentPortIdx);
    const ContainerMap& getContainerMap() const;
    // Unload the top container in this position, returns nullptr if none exists
    /* return false if no position is available, and true otherwise */
    bool loadContainer(int floor, int row, int col, std::shared_ptr<Container> container_to_load);
    std::shared_ptr<Container> unloadContainer(int floor, int row, int col);
    void advanceCurrentPortIdx();
    bool isShipFull();
    bool hasContainer(const std::string &container_id);

private:
    void updatePlan(int floor, int row, int col, const std::string& val);
    void insertContainerMap(int floor, int row, int col, const std::string& id, std::shared_ptr<Container> container);
    void eraseContainerMap(int floor, int row, int col);
};


#endif //EX2_SHIP_H
