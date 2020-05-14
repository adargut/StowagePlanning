//
// Created by osboxes on 5/14/20.
//

#include "Ship.h"

const Route &Ship::getMRoute() const
{
    return m_route;
}

void Ship::setMRoute(const Route &mRoute)
{
    m_route = mRoute;
}

const Plan &Ship::getMPlan() const
{
    return m_plan;
}

void Ship::setMPlan(const Plan &mPlan)
{
    m_plan = mPlan;
}

int Ship::getMCurrenPortIdx() const
{
    return m_currenPortIdx;
}

void Ship::setMCurrenPortIdx(int mCurrenPortIdx)
{
    m_currenPortIdx = mCurrenPortIdx;
}
