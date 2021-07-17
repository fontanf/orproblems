#pragma once

#include "optimizationtools/utils.hpp"
#include "optimizationtools/indexed_set.hpp"

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

namespace orproblems
{

namespace permutationflowshopschedulingtt
{

typedef int64_t JobId;
typedef int64_t JobPos;
typedef int64_t MachineId;
typedef int64_t Time;
typedef int64_t GuideId;

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
            std::cerr << "\033[31m" << "ERROR, unable to open file \"" << instance_path << "\"" << "\033[0m" << std::endl;
            assert(false);
            return;
        }
        if (format == "" || format == "vallada2008") {
            read_vallada2008(file);
        } else {
            std::cerr << "\033[31m" << "ERROR, unknown instance format \"" << format << "\"" << "\033[0m" << std::endl;
        }
        file.close();
    }

    virtual ~Instance() { }

    inline JobId job_number() const { return jobs_.size(); }
    inline MachineId machine_number() const { return jobs_[0].processing_times.size(); }
    inline const Job& job(JobId j) const { return jobs_[j]; }

    std::pair<bool, Time> check(std::string certificate_path)
    {
        std::ifstream file(certificate_path);
        if (!file.good()) {
            std::cerr << "\033[31m" << "ERROR, unable to open file \"" << certificate_path << "\"" << "\033[0m" << std::endl;
            assert(false);
            return {false, 0};
        }

        MachineId m = machine_number();
        JobId n = job_number();
        std::vector<Time> times(m, 0);
        JobId j = 0;
        optimizationtools::IndexedSet jobs(n);
        JobPos duplicates = 0;
        Time total_tardiness = 0;
        while (file >> j) {
            if (jobs.contains(j)) {
                duplicates++;
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
            std::cout << "Job: " << j
                << "; Due date: " << job(j).due_date
                << "; Time: " << times[m - 1]
                << "; Total tardiness: " << total_tardiness
                << std::endl;
        }
        bool feasible
            = (jobs.size() == n)
            && (duplicates == 0);

        std::cout << "---" << std::endl;
        std::cout << "Job number:             " << jobs.size() << " / " << n  << std::endl;
        std::cout << "Duplicates:             " << duplicates << std::endl;
        std::cout << "Feasible:               " << feasible << std::endl;
        std::cout << "Total tardiness:        " << total_tardiness << std::endl;
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

        for (MachineId i = 0; i < m; i++) {
            Time p = -1;
            MachineId i_tmp = -1;
            for (JobId j = 0; j < n; j++) {
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

std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "machine number " << instance.machine_number() << std::endl;
    os << "job number " << instance.job_number() << std::endl;
    for (JobId j = 0; j < instance.job_number(); ++j) {
        os << "job " << j << "; due date " << instance.job(j).due_date << "; processing times:";
        for (MachineId i = 0; i < instance.machine_number(); ++i)
            os << " " << instance.job(j).processing_times[i];
        os << std::endl;
    }
    return os;
}

}

}

