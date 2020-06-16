//
// Created by nir on 09/06/2020.
//

#ifndef STOWAGEPLANNING_THREADPOOLEXECUTOR_H
#define STOWAGEPLANNING_THREADPOOLEXECUTOR_H

#include "../common/GeneralUtility.h"

template <typename TasksProducer>
class ThreadPoolExecutor {
    TasksProducer producer;
    const int numThreads = -1;
    std::vector<std::thread> workers;

    void worker_function() {
        while(true) {
            auto task = producer.getTask();
            if(!task) break;
            (*task)();
        }
        std::cout << std::this_thread::get_id() << " - finished after processing " << std::endl;
    }
public:
    ThreadPoolExecutor(TasksProducer producer, int numThreads)
            : producer(std::move(producer)), numThreads(numThreads) {
        workers.reserve(numThreads);
    }
    bool start() {
        for(int i=0; i<numThreads; ++i) {
            workers.push_back(std::thread([this]{
                worker_function();
            }));
        }
        return true;
    }
    void wait_till_finish() {
        for(auto& t : workers) {
            t.join();
        }
    }
};

#endif //STOWAGEPLANNING_THREADPOOLEXECUTOR_H
