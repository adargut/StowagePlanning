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
    std::atomic_int total_num_tasks_finished { 0 };

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
        // bool running_status = false;
        // // see: https://en.cppreference.com/w/cpp/atomic/atomic/compare_exchange
        // if(!running.compare_exchange_strong(running_status, true)) {
        //     return false;
        // }
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
        std::cout << "thread pool finished/stopped after processing " << total_num_tasks_finished << " task(s)" << std::endl;
    }
};

#endif //STOWAGEPLANNING_THREADPOOLEXECUTOR_H
