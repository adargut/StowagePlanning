//
// Created by nir on 09/06/2020.
//

#include "PreProcessingTasksProducer.h"

// Checks if plan file is valid and sets data accordingly
static bool setPlan(const string& file_path, TravelData& travel_data, Ship& ship)
{
    Plan plan;
    AlgorithmError error = InputUtility::readShipPlan(file_path, plan);
    if(error) travel_data.addTravelError(error.errorToString() + " in " + file_path);
    ship.setPlan(plan);
    return !(error.getBit(AlgorithmError::BadPlanFile)
             || error.getBit(AlgorithmError::ConflictingXY));
}

// Checks if route file is valid and sets data accordingly
static bool setRoute(const string& file_path, TravelData& travel_data, Ship& ship)
{
    Route route;
    AlgorithmError error = InputUtility::readShipRoute(file_path, route);
    if(error) travel_data.addTravelError(error.errorToString() + " in " + file_path);
    ship.setRoute(route);
    return !(error.getBit(AlgorithmError::BadTravelFile)
             || error.getBit(AlgorithmError::SinglePortTravel));
}

// Sets the container's <PORT_NAME>_* for * the real integer representing the visit number for its unload
static void setRealDestinations(const Route& route, int curr_idx, ContainersVector& containers)
{
    for (auto& container : containers)
    {
        string destination = container->getPortCode();
        container->setPortCode(BAD_DESTINATION);
        for (size_t i = curr_idx; i < route.size(); ++i)
        {
            std::vector<string> split_line;
            GeneralUtility::split(split_line, route[i], UNDERSCORE);
            if(split_line[0] == destination)
            {
                container->setPortCode(route[i]);
                break;
            }
        }
    }
}

// Set the data of the ports for the travel
static void setPortsData(TravelData& travel_data)
{
    const string& full_travel_path = travel_data.getFullPath();
    auto& ship_route = travel_data.getShip().getRoute();
    // Set data of ports
    for (size_t i = 0; i < ship_route.size(); ++i)
    {
        auto& port = ship_route[i];
        ContainersVector port_containers;
        string port_file = full_travel_path + "/" + port + CARGO_SUFFIX;
        InputUtility::readCargo(port_file, port_containers);
        setRealDestinations(ship_route, i, port_containers);
        if(i == ship_route.size() - 1) port_containers.clear(); // Ignoring containers at the last port
        travel_data.addPort(port, port_containers);
  }
}

// Checks if cargo errors occurred
static bool reportCargoDataErrors(TravelData& travel_data)
{
    const string& full_travel_path = travel_data.getFullPath();
    const string& travel_name = travel_data.getTravelName();
    const std::vector<string>& route = travel_data.getShip().getRoute();
    const string& last_port = route.back();
    std::unordered_set<string> ports_set(route.begin(), route.end());
    std::error_code rc;
    for (const auto &file : DirectoryIterator(full_travel_path, rc))
    {
        auto& cargo_data_file = file.path();
        if (cargo_data_file.extension() == CARGO_SUFFIX)
        {
            if(!ports_set.count(cargo_data_file.filename().replace_extension("")))
            {
                travel_data.addTravelError(cargo_data_file.string() + " is not a part of the travel " + travel_name);
            }
            else
            {
                ports_set.erase(cargo_data_file.filename().replace_extension(""));
                ContainersVector temp;
                AlgorithmError error = InputUtility::readCargo(cargo_data_file, temp);
                if (error) travel_data.addTravelError(error.errorToString() + " in " + cargo_data_file.string());
                if(last_port == cargo_data_file.filename().replace_extension(""))
                {
                    if(!temp.empty()) travel_data.addTravelError(
                            cargo_data_file.string() + " has cargo data even though it's the last port");
                }
            }
        }
    }
    if(!ports_set.empty())
    {
        for (auto& port : ports_set)
        {
            travel_data.addTravelError(travel_name + ": Missing cargo file for " + port);
        }
    }
    return true;
}

std::optional<std::function<void(void)>> PreProcessingTasksProducer::getTask()
{
    auto task_index = next_task_index();
    if(task_index)
    {
        return [task_index, this]
        {
            const string &full_travel_path = m_travel_paths[*task_index];
            string travel_name = fs::path(full_travel_path).filename();
            TravelData& travel_data = m_travels_data[*task_index];
            travel_data.setTravelName(travel_name);
            travel_data.setFullPath(full_travel_path);
            Ship& ship = travel_data.getShip();
            std::error_code rc;
            bool valid_route_file = false;
            bool route_file_found = false;
            bool valid_plan_file = false;
            bool plan_file_found = false;
            for (const auto &file : DirectoryIterator(full_travel_path, rc))
            {
                if (file.path().extension() == ROUTE_SUFFIX)
                {
                    // Check route file (check validity)
                    valid_route_file = setRoute(file.path(), travel_data, ship);
                    if (route_file_found)                     // Two or more route files
                    {
                        travel_data.addTravelError("Two or more route files in " + travel_name);
                        valid_route_file = false;
                        break;
                    }
                    route_file_found = true;
                    travel_data.setRoutePath(file.path());
                }
                else if (file.path().extension() ==  PLAN_SUFFIX)
                {
                    // Check plan file (check validity)
                    valid_plan_file = setPlan(file.path(), travel_data, ship);
                    if (plan_file_found)                    // Two or more plan files
                    {
                        travel_data.addTravelError("Two or more plan files in " + travel_name);
                        valid_plan_file = false;
                        break;
                    }
                    plan_file_found = true;
                    travel_data.setPlanPath(file.path());
                }
            }
            if (valid_plan_file && valid_route_file)
            {
                reportCargoDataErrors(travel_data);
                setPortsData(travel_data);
                travel_data.setValid(true);
            }
            m.lock();
            std::cout << "thread: " << std::this_thread::get_id() << " finished preprocessing: " << travel_name << "\n";
            m.unlock();
        };
    }
    else return {};
}
