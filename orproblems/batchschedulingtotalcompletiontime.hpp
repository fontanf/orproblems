#pragma once

#include "optimizationtools/containers/indexed_set.hpp"

#include <stdexcept>
#include <fstream>
#include <iostream>

/**
 * Single machine batch scheduling problem, Total completion time.
 *
 * Input:
 * - n jobs; for each job j = 1..n
 *   - a processing time pⱼ
 *   - a size sⱼ
 * - a batch capacity Q
 * Problem:
 * - partition the jobs into batches and sequence the batches such that:
 *   - each job must be in exactly one of the batches
 *   - the processing time of a batch is equal to the longest processing time
 *     among all jobs it contains
 *   - the total size of the jobs in a batch does not exceed its capacity
 * Objective:
 * - minimize the total completion time of the schedule
 *
 */

namespace orproblems
{

namespace batchschedulingtotalcompletiontime
{

typedef int64_t JobId;
typedef int64_t JobPos;
typedef int64_t Time;
typedef int64_t Size;
typedef int64_t Area;

struct Job
{
    JobId id;
    Time processing_time;
    Size size;
};

class Instance
{

public:

    Instance() { }
    void add_job(Time p, Size s)
    {
        Job job;
        job.id = jobs_.size();
        job.processing_time = p;
        job.size = s;
        jobs_.push_back(job);
    }
    void set_capacity(Size q) { capacity_ = q; }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        if (format == "" || format == "alfieri2021") {
            read_alfieri2021(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    virtual ~Instance() { }

    inline JobId number_of_jobs() const { return jobs_.size(); }
    inline const Job& job(JobId j) const { return jobs_[j]; }
    inline Size capacity() const { return capacity_; }

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

        JobId n = number_of_jobs();
        JobPos s = -1;
        optimizationtools::IndexedSet jobs(n);
        JobPos number_of_batches = 0;
        JobPos number_of_duplicates = 0;
        JobPos number_of_overloaded_batches = 0;
        Time total_completion_time = 0;
        Time current_batch_start = 0;
        Time current_batch_end = 0;

        while (file >> s) {
            JobId j = -1;
            Size size = 0;
            number_of_batches++;
            if (verbose == 2)
                std::cout << "batch: " << number_of_batches - 1 << "; Jobs";
            std::vector<JobId> batch_jobs;
            for (JobPos j_pos = 0; j_pos < s; ++j_pos) {
                file >> j;
                // Check duplicates.
                if (jobs.contains(j)) {
                    number_of_duplicates++;
                    if (verbose == 2)
                        std::cout << std::endl << "Job " << j << " has already benn scheduled." << std::endl;
                }
                if (verbose == 2)
                    std::cout << " " << j;
                jobs.add(j);
                batch_jobs.push_back(j);
                size += job(j).size;
            }
            current_batch_start = current_batch_end;
            for (JobId j: batch_jobs)
                if (current_batch_end < current_batch_start + job(j).processing_time)
                    current_batch_end = current_batch_start + job(j).processing_time;
            total_completion_time += current_batch_end * batch_jobs.size();
            if (verbose == 2)
                std::cout << "; Size: " << size << " / " << capacity() << std::endl;
            if (size > capacity()) {
                number_of_overloaded_batches++;
                if (verbose == 2)
                    std::cout << "Batch " << number_of_batches - 1 << " is overloaded." << std::endl;
            }
            current_batch_start = current_batch_end;
        }

        bool feasible
            = (jobs.size() == n)
            && (number_of_duplicates == 0)
            && (number_of_overloaded_batches == 0);
        if (verbose == 2)
            std::cout << "---" << std::endl;
        if (verbose >= 1) {
            std::cout << "Number of jobs:                " << jobs.size() << " / " << n  << std::endl;
            std::cout << "Number of duplicates:          " << number_of_duplicates << std::endl;
            std::cout << "Number of overloaded batches:  " << number_of_overloaded_batches << std::endl;
            std::cout << "Feasible:                      " << feasible << std::endl;
            std::cout << "Number of batches:             " << number_of_batches << std::endl;
            std::cout << "Total completion time:         " << total_completion_time << std::endl;
        }
        return {feasible, total_completion_time};
    }

private:

    void read_alfieri2021(std::ifstream& file)
    {
        JobId n = -1;
        Size c = -1;
        file >> n >> c;
        set_capacity(c);

        Time p;
        Size s;
        for (JobId j = 0; j < n; ++j) {
            file >> p >> s;
            add_job(p, s);
        }
    }

    std::vector<Job> jobs_;
    Size capacity_ = 0;

};

static inline std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "number of jobs: " << instance.number_of_jobs() << std::endl;
    os << "capacity: " << instance.capacity() << std::endl;
    for (JobId j = 0; j < instance.number_of_jobs(); ++j)
        os << "job: " << j
            << "; processing time: " << instance.job(j).processing_time
            << "; size: " << instance.job(j).size
            << std::endl;
    return os;
}

}

}

