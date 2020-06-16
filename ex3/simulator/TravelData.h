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
    string m_route_path;
    string m_plan_path;
    static string m_output_dir;
    Ship m_ship;
    std::vector<Error> m_travel_errors;
    Ports m_ports;
    bool m_valid;
public:
    static const string &getOutputDir()
    {
        return m_output_dir;
    }

    static void setOutputDir(const string &mOutputDir)
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

    Ship& getShip()
    {
        return m_ship;
    }

    const Ship& getShip() const
    {
        return m_ship;
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
        m_ports.emplace_back(port_name, containers);
    }

    const string &getRoutePath() const {
        return m_route_path;
    }

    void setRoutePath(const string &mRoutePath) {
        m_route_path = mRoutePath;
    }

    const string &getPlanPath() const {
        return m_plan_path;
    }

    void setPlanPath(const string &mPlanPath) {
        m_plan_path = mPlanPath;
    }
};


#endif //EX3_TRAVELDATA_H
