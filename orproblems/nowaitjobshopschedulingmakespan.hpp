#pragma once

#include "optimizationtools/utils/utils.hpp"
#include "optimizationtools/containers/indexed_set.hpp"
#include "interval_tree.hpp"

#include <iostream>
#include <fstream>

/**
 * No-wait job shop scheduling problem, Makespan.
 *
 * Input:
 * - m machines
 * - n jobs TODO
 * Problem:
 * - TODO
 * Objective:
 * - Minimize the makespan of the schedule
 *
 */

namespace orproblems
{

namespace nowaitjobshopschedulingmakespan
{

typedef int64_t JobId;
typedef int64_t JobPos;
typedef int64_t OperationId;
typedef int64_t OperationPos;
typedef int64_t MachineId;
typedef int64_t Time;

struct Operation
{
    MachineId machine_id = -1;
    Time processing_time = -1;
};

class Instance
{

public:

    Instance(MachineId m, JobId n):
        number_of_machines_(m), operations_(n) { }
    void add_operation(
            JobId j,
            MachineId i,
            Time processing_time)
    {
        Operation operation;
        operation.machine_id = i;
        operation.processing_time = processing_time;
        operations_[j].push_back(operation);
    }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        }

        if (format == "" || format == "default" || format == "tamy0612") {
            read_tamy0612(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    virtual ~Instance() { }

    inline JobId number_of_jobs() const { return operations_.size(); }
    inline MachineId number_of_machines() const { return number_of_machines_; }
    inline OperationPos number_of_operations(JobId j) const { return operations_[j].size(); }
    inline const Operation& operation(JobId j, OperationPos k) const { return operations_[j][k]; }

    std::pair<bool, Time> check(
            std::string certificate_path,
            int verbose = 1) const
    {
        // Initial display.
        if (verbose >= 1) {
            std::cout
                << "Checker" << std::endl
                << "-------" << std::endl;
        }

        std::ifstream file(certificate_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");
        }

        MachineId m = number_of_machines();
        JobId n = number_of_jobs();
        std::vector<lib_interval_tree::interval_tree_t<Time>> intervals(m);
        JobId j = 0;
        Time s = 0;
        OperationPos number_of_overlaps = 0;
        OperationPos number_of_negative_starts = 0;
        while (file >> s) {
            if (s < 0)
                number_of_negative_starts++;
            Time current_time = s;
            for (OperationPos k = 0; k < number_of_operations(j); ++k) {
                MachineId i = operation(j, k).machine_id;
                Time completion_time = current_time + operation(j, k).processing_time;
                if (intervals[i].overlap_find({current_time, completion_time}, true)
                        != intervals[i].end())
                    number_of_overlaps++;
                intervals[i].insert_overlap({current_time, completion_time});
                current_time = completion_time;
            }
            if (verbose == 2)
                std::cout << "Job: " << j
                    << "; Start: " << s
                    << std::endl;
            j += 1;
        }
        Time makespan = 0;
        for (MachineId i = 0; i < m; ++i)
            for (const auto& interval: intervals[i])
                makespan = std::max(makespan, interval.high());

        bool feasible
            = (j == n)
            && (number_of_overlaps == 0);
        if (verbose == 2)
            std::cout << "---" << std::endl;
        if (verbose >= 1) {
            std::cout << "Number of jobs:             " << j << " / " << n  << std::endl;
            std::cout << "Number of negative starts:  " << number_of_negative_starts << std::endl;
            std::cout << "Number of overlaps:         " << number_of_overlaps << std::endl;
            std::cout << "Feasible:                   " << feasible << std::endl;
            std::cout << "Makespan:                   " << makespan << std::endl;
        }
        return {feasible, makespan};
    }

private:

    void read_tamy0612(std::ifstream& file)
    {
        std::string tmp;
        do {
            getline(file, tmp);
        } while (tmp[0] == '#');
        std::stringstream ss(tmp);

        JobId n;
        ss >> n;
        ss >> number_of_machines_;

        operations_ = std::vector<std::vector<Operation>>(n);
        Time p = -1;
        MachineId i = -1;
        for (JobId j = 0; j < n; ++j) {
            do {
                getline(file, tmp);
            } while (tmp[0] == '#');
            std::stringstream ss(tmp);
            for (MachineId ii = 0; ii < number_of_machines(); ++ii) {
                ss >> i >> p;
                add_operation(j, i, p);
            }
        }
    }

    MachineId number_of_machines_ = 0;
    std::vector<std::vector<Operation>> operations_;

};

static inline std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "number of machines " << instance.number_of_machines() << std::endl;
    os << "number of jobs " << instance.number_of_jobs() << std::endl;
    for (JobId j = 0; j < instance.number_of_jobs(); ++j) {
        os << "job " << j << "; o:";
        for (OperationPos k = 0; k < instance.number_of_operations(j); ++k) {
            os
                << " i " << instance.operation(j, k).machine_id
                << " p " << instance.operation(j, k).processing_time;
        }
        os << std::endl;
    }
    return os;
}

}

}

