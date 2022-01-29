#pragma once

#include "optimizationtools/utils.hpp"
#include "optimizationtools/indexed_set.hpp"

#include <iostream>
#include <fstream>

/**
 * Distributed permutation flow shop scheduling problem, Total completion time.
 *
 * Input:
 * - F factories
 * - m machines
 * - n jobs composed of m operations for each machine with pᵢⱼ the processing
 *   time of the operation of job j on machine i, j = 1..n, i = 1..m
 * Problem:
 * - Find a schedule of jobs for each factory such that:
 *   - all operations of all jobs are scheduled exactly once
 *   - for all job j = 1..n, i = 1..m - 1, operations (j, i + 1) starts after
 *     the end of operation (j, i)
 *   - the job sequence is the same on all machines of a factory
 * Objective:
 * - Minimize the total completion time of the jobs
 *
 */

namespace orproblems
{

namespace distributedpfsstct
{

typedef int64_t JobId;
typedef int64_t JobPos;
typedef int64_t MachineId;
typedef int64_t FactoryId;
typedef int64_t Time;

class Instance
{

public:

    Instance(MachineId m, JobId n):
        processing_times_(n, std::vector<Time>(m, 0)) { }
    void set_number_of_factories(FactoryId f) { number_of_factories_ = f; }
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

        if (format == "" || format == "default" || format == "naderi2010") {
            read_naderi2010(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    virtual ~Instance() { }

    inline FactoryId number_of_factories() const { return number_of_factories_; }
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
        optimizationtools::IndexedSet jobs(n);
        JobPos number_of_duplicates = 0;
        JobPos factory_number_of_jobs = -1;
        Time total_completion_time = 0;
        while (file >> factory_number_of_jobs) {
            JobId j = -1;
            while (file >> j) {
                if (jobs.contains(j)) {
                    number_of_duplicates++;
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
                total_completion_time += times[m - 1];
                if (verbose == 2)
                    std::cout << "Job: " << j
                        << "; Time: " << times[m - 1]
                        << std::endl;
            }
        }

        bool feasible
            = (jobs.size() == n)
            && (number_of_duplicates == 0);
        if (verbose == 2)
            std::cout << "---" << std::endl;
        if (verbose >= 1) {
            std::cout << "Number of jobs:         " << jobs.size() << " / " << n  << std::endl;
            std::cout << "Number of duplicates:   " << number_of_duplicates << std::endl;
            std::cout << "Feasible:               " << feasible << std::endl;
            std::cout << "Total completion time:  " << total_completion_time << std::endl;
        }
        return {feasible, total_completion_time};
    }

private:

    void read_naderi2010(std::ifstream& file)
    {
        JobId n;
        MachineId m;
        file >> n;
        file >> m;
        file >> number_of_factories_;
        processing_times_ = std::vector<std::vector<Time>>(n, std::vector<Time>(m, 0));

        Time p = -1;
        MachineId i_tmp = -1;
        for (JobId j = 0; j < n; j++) {
            for (MachineId i = 0; i < m; i++) {
                file >> i_tmp >> p;
                set_processing_time(j, i, p);
            }
        }
    }

    FactoryId number_of_factories_ = 1;
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

