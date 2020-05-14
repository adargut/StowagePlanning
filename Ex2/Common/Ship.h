//
// Created by osboxes on 5/14/20.
//

#ifndef EX2_SHIP_H
#define EX2_SHIP_H

#include "../Common/GeneralUtility.h"


class Ship
{
private:
    Route m_route;
    Plan m_plan;
    int m_currenPortIdx;
public:
    const Route &getMRoute() const;
    void setMRoute(const Route &mRoute);
    const Plan &getMPlan() const;
    void setMPlan(const Plan &mPlan);
    int getMCurrenPortIdx() const;
    void setMCurrenPortIdx(int mCurrenPortIdx);
};


#endif //EX2_SHIP_H
