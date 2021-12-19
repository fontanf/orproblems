#pragma once

#include "optimizationtools/utils.hpp"
#include "optimizationtools/indexed_set.hpp"

#include <iostream>
#include <fstream>

/**
 * Permutation flow shop scheduling problem, Makespan.
 *
 * Input:
 * - m machines
 * - n jobs composed of m operations for each machine with pᵢⱼ the processing
 *   time of the operation of job j on machine i, j = 1..n, i = 1..m
 * Problem:
 * - Find a schedule of jobs such that:
 *   - all operations of all jobs are scheduled
 *   - for all job j = 1..n, i = 1..m - 1, operations (j, i + 1) starts after
 *     the end of operation (j, i)
 *   - the job sequence is the same on all machines
 * Objective:
 * - Minimize the makespan of the schedule
 *
 */

namespace orproblems
{

namespace permutationflowshopschedulingmakespan
{

typedef int64_t JobId;
typedef int64_t JobPos;
typedef int64_t MachineId;
typedef int64_t Time;

class Instance
{

public:

    Instance(MachineId m, JobId n):
        processing_times_(n, std::vector<Time>(m, 0)) { }
    void set_processing_time(
            JobId j,
            MachineId i,
            Time processing_time)
    {
        processing_times_[j][i] = processing_time;
    }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");

        if (format == "" || format == "default") {
            read_default(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    virtual ~Instance() { }

    inline JobId number_of_jobs() const { return processing_times_.size(); }
    inline MachineId number_of_machines() const { return processing_times_[0].size(); }
    inline Time processing_time(JobId j, MachineId i) const { return processing_times_[j][i]; }

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
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");

        MachineId m = number_of_machines();
        JobId n = number_of_jobs();
        std::vector<Time> times(m, 0);
        JobId j = 0;
        optimizationtools::IndexedSet jobs(n);
        JobPos duplicates = 0;
        while (file >> j) {
            if (jobs.contains(j)) {
                duplicates++;
                if (verbose == 2)
                    std::cout << "Job " << j << " already scheduled." << std::endl;
            }
            jobs.add(j);
            times[0] = times[0] + processing_time(j, 0);
            for (MachineId i = 1; i < m; ++i) {
                if (times[i - 1] > times[i]) {
                    times[i] = times[i - 1] + processing_time(j, i);
                } else {
                    times[i] = times[i] + processing_time(j, i);
                }
            }
            if (verbose == 2)
                std::cout << "Job: " << j
                    << "; Time: " << times[m - 1]
                    << std::endl;
        }

        bool feasible
            = (jobs.size() == n)
            && (duplicates == 0);
        if (verbose == 2)
            std::cout << "---" << std::endl;
        if (verbose >= 1) {
            std::cout << "Number of jobs:        " << jobs.size() << " / " << n  << std::endl;
            std::cout << "Number of duplicates:  " << duplicates << std::endl;
            std::cout << "Feasible:              " << feasible << std::endl;
            std::cout << "Makespan:              " << times[m - 1] << std::endl;
        }
        return {feasible, times[m - 1]};
    }

private:

    void read_default(std::ifstream& file)
    {
        JobId n;
        MachineId m;
        file >> n;
        file >> m;
        processing_times_ = std::vector<std::vector<Time>>(n, std::vector<Time>(m, 0));

        for (MachineId i = 0; i < m; i++) {
            Time p;
            for (JobId j = 0; j < n; j++) {
                file >> p;
                set_processing_time(j, i, p);
            }
        }
    }

    std::vector<std::vector<Time>> processing_times_;
    Time machine_total_processing_time_max = 0;
    Time job_total_processing_time_max = 0;

};

static inline std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "number of machines " << instance.number_of_machines() << std::endl;
    os << "number of jobs " << instance.number_of_jobs() << std::endl;
    for (JobId j = 0; j < instance.number_of_jobs(); ++j) {
        os << "job " << j << ":";
        for (MachineId i = 0; i < instance.number_of_machines(); ++i)
            os << " " << instance.processing_time(j, i);
        os << std::endl;
    }
    return os;
}

}

}

