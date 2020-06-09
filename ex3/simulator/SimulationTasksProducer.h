//
// Created by nir on 09/06/2020.
//

#ifndef EX3_SIMULATIONTASKSPRODUCER_H
#define EX3_SIMULATIONTASKSPRODUCER_H

#include "AbstractTasksProducer.h"

class SimulationTasksProducer : public AbstractTasksProducer
{
    std::vector<string> &m_algo_travel_pairs; //TODO something else
    std::vector<string> &m_results; //TODO something else
public:
    SimulationTasksProducer(int numTasks, std::vector<string> &algo_travel_pairs, std::vector<string> &results) : AbstractTasksProducer(numTasks), m_algo_travel_pairs(algo_travel_pairs), m_results(results) {}
    SimulationTasksProducer(SimulationTasksProducer && other):  AbstractTasksProducer(std::move(other)), m_algo_travel_pairs(other.m_algo_travel_pairs), m_results(other.m_results) {}
    std::optional<std::function<void(void)>> getTask() override;
};


#endif //EX3_SIMULATIONTASKSPRODUCER_H
