#ifndef EX3_SIMULATIONTASKSPRODUCER_H
#define EX3_SIMULATIONTASKSPRODUCER_H

#include "AbstractTasksProducer.h"
#include "Simulation.h"

class SimulationTasksProducer : public AbstractTasksProducer
{
    const ProcessedDataList &m_processed_travels; // the tasks
    AlgorithmTravelResultsMap &m_results; // where task results are stored
public:
    SimulationTasksProducer(int numTasks, ProcessedDataList &processed_travels, AlgorithmTravelResultsMap &results) :
    AbstractTasksProducer(numTasks), m_processed_travels(processed_travels), m_results(results) {}
    SimulationTasksProducer(SimulationTasksProducer && other) : AbstractTasksProducer(std::move(other)),
    m_processed_travels(other.m_processed_travels), m_results(other.m_results) {}
    std::optional<std::function<void(void)>> getTask() override;
};


#endif //EX3_SIMULATIONTASKSPRODUCER_H
