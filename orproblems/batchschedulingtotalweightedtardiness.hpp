#pragma once

#include "optimizationtools/indexed_set.hpp"

/**
 * Single machine batch scheduling problem, Total weighted tardiness.
 *
 * Input:
 * - n jobs; for each job j = 1..n
 *   - a processing time pⱼ
 *   - a size sⱼ
 *   - a release date rⱼ
 *   - a due date dⱼ
 *   - a weight wⱼ
 * - a batch capacity Q
 * Problem:
 * - partition the jobs into batches and sequence the batches such that:
 *   - each job must be in exactly one of the batches
 *   - the processing time of a batch is equal to the longest processing time
 *     among all jobs it contains
 *   - the total size of the jobs in a batch does not exceed its capacity
 *   - each job starts after its release date (each jobs start at the start
 *     date of its batch)
 * Objective:
 * - minimize the total weighted tardiness of the schedule
 *
 */

namespace orproblems
{

namespace batchschedulingtotalweightedtardiness
{

typedef int64_t JobId;
typedef int64_t JobPos;
typedef int64_t Time;
typedef int64_t Weight;
typedef int64_t Size;
typedef int64_t Area;

struct Job
{
    JobId id;
    Time processing_time;
    Time release_date;
    Time due_date;
    Size size;
    Weight weight;
};

class Instance
{

public:

    Instance() { }
    void add_job(Time p, Time r, Time d, Size s, Weight w)
    {
        Job job;
        job.id = jobs_.size();
        job.processing_time = p;
        job.release_date = r;
        job.due_date = d;
        job.size = s;
        job.weight = w;
        jobs_.push_back(job);
    }
    void set_capacity(Size q) { capacity_ = q; }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        if (format == "" || format == "queiroga2020") {
            read_queiroga2020(file);
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

    std::pair<bool, Time> check(std::string certificate_path)
    {
        std::ifstream file(certificate_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");

        JobId n = number_of_jobs();
        JobPos s = -1;
        optimizationtools::IndexedSet jobs(n);
        JobPos number_of_batches = 0;
        JobPos duplicates = 0;
        JobPos number_of_overloaded_batches = 0;
        Time total_weighted_tardiness = 0;
        Time current_batch_start = 0;
        Time current_batch_end = 0;

        while (file >> s) {
            JobId j = -1;
            Size size = 0;
            number_of_batches++;
            std::cout << "batch: " << number_of_batches - 1 << "; Jobs";
            std::vector<JobId> batch_jobs;
            for (JobPos j_pos = 0; j_pos < s; ++j_pos) {
                file >> j;
                // Check duplicates.
                if (jobs.contains(j)) {
                    duplicates++;
                    std::cout << std::endl << "Job " << j << " has already benn scheduled." << std::endl;
                }
                std::cout << " " << j;
                jobs.add(j);
                batch_jobs.push_back(j);
                size += job(j).size;
            }
            current_batch_start = current_batch_end;
            for (JobId j: batch_jobs)
                if (current_batch_start < job(j).release_date)
                    current_batch_start = job(j).release_date;
            for (JobId j: batch_jobs)
                if (current_batch_end < current_batch_start + job(j).processing_time)
                    current_batch_end = current_batch_start + job(j).processing_time;
            for (JobId j: batch_jobs)
                if (current_batch_end > job(j).due_date)
                    total_weighted_tardiness += job(j).weight * (current_batch_end - job(j).due_date);
            std::cout << "; Size: " << size << " / " << capacity() << std::endl;
            if (size > capacity()) {
                number_of_overloaded_batches++;
                std::cout << "Batch " << number_of_batches - 1 << " is overloaded." << std::endl;
            }
            current_batch_start = current_batch_end;
        }
        bool feasible
            = (jobs.size() == n)
            && (duplicates == 0)
            && (number_of_overloaded_batches == 0);

        std::cout << "---" << std::endl;
        std::cout << "Job number:                   " << jobs.size() << " / " << n  << std::endl;
        std::cout << "Duplicates:                   " << duplicates << std::endl;
        std::cout << "Overloaded batch number:      " << number_of_overloaded_batches << std::endl;
        std::cout << "Feasible:                     " << feasible << std::endl;
        std::cout << "Batch number:                 " << number_of_batches << std::endl;
        std::cout << "Total weighted tardiness:     " << total_weighted_tardiness << std::endl;
        return {feasible, total_weighted_tardiness};
    }

private:

    void read_queiroga2020(std::ifstream& file)
    {
        JobId n = -1;
        Size c = -1;
        file >> n >> c;
        set_capacity(c);

        Time p, r, d;
        Size s;
        Weight w;
        for (JobId j = 0; j < n; ++j) {
            file >> p >> d >> s >> w >> r;
            add_job(p, r, d, s, w);
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
            << "; release date: " << instance.job(j).release_date
            << "; due date: " << instance.job(j).due_date
            << "; size: " << instance.job(j).size
            << "; weight: " << instance.job(j).weight
            << std::endl;
    return os;
}

}

}

