//
// Created by nir on 09/06/2020.
//

#ifndef EX3_TRAVELDATA_H
#define EX3_TRAVELDATA_H

#include "../common/GeneralUtility.h"
#include "../common/Port.h"
#include "../common/Ship.h"
#include "../common/AlgorithmError.h"
#include "Error.h"

class TravelData
{
private:
    string m_travel_name;
    string m_full_path;
    string m_output_dir;
    Ship m_ship;
    std::vector<Error> m_travel_errors;
    Ports m_ports;
    bool m_valid;
public:
    // TODO not sure if this should be here?
    const string &getOutputDir() const
    {
        return m_output_dir;
    }

    void setOutputDir(const string &mOutputDir)
    {
        m_output_dir = mOutputDir;
    }
    
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

    void addTravelError(const string& algorithm_error)
    {
        m_travel_errors.emplace_back(algorithm_error);
    }

    void addPort(const string& port_name, const ContainersVector& containers)
    {
        m_ports.emplace_back(port_name, containers); //TODO check this is fine
    }
};


#endif //EX3_TRAVELDATA_H
