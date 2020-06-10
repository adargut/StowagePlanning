#ifndef EX3_SIMULATIONTASKSPRODUCER_H
#define EX3_SIMULATIONTASKSPRODUCER_H

#include "AbstractTasksProducer.h"
#include "Simulation.h"

class SimulationTasksProducer : public AbstractTasksProducer
{
    ProcessedDataList m_processed_travels; // the tasks
    AlgorithmTravelResultsMap &m_results; // where task results are stored
public:
    SimulationTasksProducer(int numTasks, ProcessedDataSingleton &travel_data) : AbstractTasksProducer(numTasks), m_travel_data(travel_data) {}
    SimulationTasksProducer(SimulationTasksProducer && other) : AbstractTasksProducer(std::move(other)), m_travel_data(other.m_travel_data), m_results(other.m_results) {}
    std::optional<std::function<void(void)>> getTask() override;
};


#endif //EX3_SIMULATIONTASKSPRODUCER_H
