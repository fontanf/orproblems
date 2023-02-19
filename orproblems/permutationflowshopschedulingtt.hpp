/**
 * Permutation flow shop scheduling problem, Total tardiness.
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
 * - Minimize the total tardiness of the jobs
 *
 */

#pragma once

#include "optimizationtools/utils/utils.hpp"
#include "optimizationtools/containers/indexed_set.hpp"

#include <iostream>
#include <fstream>

namespace orproblems
{

namespace permutationflowshopschedulingtt
{

typedef int64_t JobId;
typedef int64_t JobPos;
typedef int64_t MachineId;
typedef int64_t Time;

struct Job
{
    std::vector<Time> processing_times;
    Time due_date;
};

class Instance
{

public:

    Instance(MachineId m, JobId n):
        jobs_(n) 
    {
        for (JobId j = 0; j < n; ++j)
            jobs_[j].processing_times.resize(m);
    }
    void set_due_date(JobId j, Time due_date) { jobs_[j].due_date = due_date; }
    void set_processing_time(
            JobId j,
            MachineId i,
            Time processing_time)
    {
        jobs_[j].processing_times[i] = processing_time;
    }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        }

        if (format == "" || format == "vallada2008") {
            read_vallada2008(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    virtual ~Instance() { }

    inline JobId number_of_jobs() const { return jobs_.size(); }
    inline MachineId number_of_machines() const { return jobs_[0].processing_times.size(); }
    inline const Job& job(JobId j) const { return jobs_[j]; }

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
        std::vector<Time> times(m, 0);
        JobId j = 0;
        optimizationtools::IndexedSet jobs(n);
        JobPos number_of_duplicates = 0;
        Time total_tardiness = 0;
        while (file >> j) {
            if (jobs.contains(j)) {
                number_of_duplicates++;
                if (verbose == 2)
                    std::cout << "Job " << j << " already scheduled." << std::endl;
            }
            jobs.add(j);
            times[0] = times[0] + job(j).processing_times[0];
            for (MachineId i = 1; i < m; ++i) {
                if (times[i - 1] > times[i]) {
                    times[i] = times[i - 1] + job(j).processing_times[i];
                } else {
                    times[i] = times[i] + job(j).processing_times[i];
                }
            }
            if (times[m - 1] > job(j).due_date)
                total_tardiness += (times[m - 1] - job(j).due_date);
            if (verbose == 2)
                std::cout << "Job: " << j
                    << "; Due date: " << job(j).due_date
                    << "; Time: " << times[m - 1]
                    << "; Total tardiness: " << total_tardiness
                    << std::endl;
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
            std::cout << "Total tardiness:        " << total_tardiness << std::endl;
        }
        return {feasible, total_tardiness};
    }

private:

    void read_vallada2008(std::ifstream& file)
    {
        JobId n;
        MachineId m;
        file >> n >> m;
        jobs_ = std::vector<Job>(n);
        for (JobId j = 0; j < n; ++j)
            jobs_[j].processing_times.resize(m);

        for (JobId j = 0; j < n; j++) {
            Time p = -1;
            MachineId i_tmp = -1;
            for (MachineId i = 0; i < m; i++) {
                file >> i_tmp >> p;
                set_processing_time(j, i, p);
            }
        }
        std::string tmp;
        file >> tmp;
        for (JobId j = 0; j < n; ++j) {
            Time d = -1;
            file >> tmp >> d >> tmp >> tmp;
            set_due_date(j, d);
        }
    }

    std::vector<Job> jobs_;

};

static inline std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "number of machines " << instance.number_of_machines() << std::endl;
    os << "number of jobs " << instance.number_of_jobs() << std::endl;
    for (JobId j = 0; j < instance.number_of_jobs(); ++j) {
        os << "job " << j << "; due date " << instance.job(j).due_date << "; processing times:";
        for (MachineId i = 0; i < instance.number_of_machines(); ++i)
            os << " " << instance.job(j).processing_times[i];
        os << std::endl;
    }
    return os;
}

}

}

