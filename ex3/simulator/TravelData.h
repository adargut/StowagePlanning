//
// Created by nir on 09/06/2020.
//

#ifndef EX3_TRAVELDATA_H
#define EX3_TRAVELDATA_H

#include "../common/GeneralUtility.h"
#include "../common/Port.h"
#include "../common/Ship.h"
#include "Error.h"

class TravelData
{
public:
    string m_travel_name;
    string m_full_path;
    Ship m_ship;
    std::vector<Error> m_travel_errors;
    Ports m_ports;
    bool m_valid;
    
    const string& getTravelName() const
    {
        return m_travel_name;
    }

    void setTravelName(const string& mTravelName)
    {
        m_travel_name = mTravelName;
    }

    const string& getFullPath() const
    {
        return m_full_path;
    }

    void setFullPath(const string& mFullPath)
    {
        m_full_path = mFullPath;
    }

    const Ship& getShip() const
    {
        return m_ship;
    }

    void setShip(const Ship& mShip)
    {
        m_ship = mShip;
    }

    const std::vector<Error>& getTravelErrors() const
    {
        return m_travel_errors;
    }

    const Ports& getPorts() const
    {
        return m_ports;
    }

    bool isValid() const
    {
        return m_valid;
    }

    void setValid(bool valid)
    {
        m_valid = valid;
    }

    void addTravelError(const string& error_code)
    {
        m_travel_errors.emplace_back(error_code);
    }

    void addPort(const Port& port)
    {
        m_ports.push_back(port); //TODO check this is fine
    }
};


#endif //EX3_TRAVELDATA_H
