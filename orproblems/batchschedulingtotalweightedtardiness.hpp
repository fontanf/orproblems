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

#pragma once

#include "optimizationtools/containers/indexed_set.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>

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
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        }
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

    std::ostream& print(
            std::ostream& os,
            int verbose = 1) const
    {
        if (verbose >= 1) {
            os << "Number of jobs:  " << number_of_jobs() << std::endl;
            os << "Batch capacity:  " << capacity() << std::endl;
        }
        if (verbose >= 2) {
            os << std::endl
                << std::setw(12) << "Job"
                << std::setw(12) << "Proc. time"
                << std::setw(12) << "Rel. date"
                << std::setw(12) << "Due date"
                << std::setw(12) << "Size"
                << std::setw(12) << "Weight"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "----------"
                << std::setw(12) << "---------"
                << std::setw(12) << "--------"
                << std::setw(12) << "----"
                << std::setw(12) << "------"
                << std::endl;
            for (JobId j = 0; j < number_of_jobs(); ++j)
                os << std::setw(12) << j
                    << std::setw(12) << job(j).processing_time
                    << std::setw(12) << job(j).release_date
                    << std::setw(12) << job(j).due_date
                    << std::setw(12) << job(j).size
                    << std::setw(12) << job(j).weight
                    << std::endl;
        }
        return os;
    }

    std::pair<bool, Time> check(
            std::string certificate_path,
            std::ostream& os,
            int verbose = 1) const
    {
        std::ifstream file(certificate_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");
        }

        JobId n = number_of_jobs();
        JobPos s = -1;
        optimizationtools::IndexedSet jobs(n);
        JobPos number_of_batches = 0;
        JobPos number_of_duplicates = 0;
        JobPos number_of_overloaded_batches = 0;
        Time current_batch_end = 0;
        Time total_weighted_tardiness = 0;

        if (verbose >= 2) {
            os << std::endl << std::right
                << std::setw(12) << "Job"
                << std::setw(12) << "Proc. time"
                << std::setw(12) << "Rel. date"
                << std::setw(12) << "Due date"
                << std::setw(12) << "Size"
                << std::setw(12) << "Weight"
                << std::setw(12) << "Bat. start"
                << std::setw(12) << "Batch size"
                << std::setw(12) << "Batch end"
                << std::setw(12) << "Total TWT"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "----------"
                << std::setw(12) << "---------"
                << std::setw(12) << "--------"
                << std::setw(12) << "----"
                << std::setw(12) << "------"
                << std::setw(12) << "----------"
                << std::setw(12) << "----------"
                << std::setw(12) << "---------"
                << std::setw(12) << "---------"
                << std::endl;
        }

        while (file >> s) {
            JobId j = -1;
            number_of_batches++;
            std::vector<JobId> batch_jobs;
            Time current_batch_start = current_batch_end;
            Time current_batch_time = 0;
            Size current_batch_size = 0;
            for (JobPos j_pos = 0; j_pos < s; ++j_pos) {
                file >> j;
                // Check duplicates.
                if (jobs.contains(j)) {
                    number_of_duplicates++;
                    if (verbose >= 2)
                        os << std::endl << "Job " << j << " has already benn scheduled." << std::endl;
                }
                jobs.add(j);
                batch_jobs.push_back(j);
                current_batch_size += job(j).size;
                if (current_batch_start < job(j).release_date)
                    current_batch_start = job(j).release_date;
                if (current_batch_time < job(j).processing_time)
                    current_batch_time = job(j).processing_time;
                current_batch_end = current_batch_start + current_batch_time;
                if (verbose >= 2) {
                    os
                        << std::setw(12) << j
                        << std::setw(12) << job(j).processing_time
                        << std::setw(12) << job(j).release_date
                        << std::setw(12) << job(j).due_date
                        << std::setw(12) << job(j).size
                        << std::setw(12) << job(j).weight
                        << std::setw(12) << current_batch_start
                        << std::setw(12) << current_batch_size
                        << std::setw(12) << current_batch_end
                        << std::endl;
                }
            }
            for (JobId j: batch_jobs)
                if (current_batch_end > job(j).due_date)
                    total_weighted_tardiness += job(j).weight * (current_batch_end - job(j).due_date);
            if (verbose >= 2) {
                os << "Batch " << number_of_batches - 1
                    << "; number of jobs: " << batch_jobs.size()
                    << "; total weighted tardiness: " << total_weighted_tardiness
                    << std::endl;
            }
            if (current_batch_size > capacity()) {
                number_of_overloaded_batches++;
                if (verbose == 2)
                    os << "Batch " << number_of_batches - 1 << " is overloaded." << std::endl;
            }
            current_batch_start = current_batch_end;
        }

        bool feasible
            = (jobs.size() == n)
            && (number_of_duplicates == 0)
            && (number_of_overloaded_batches == 0);
        if (verbose >= 2)
            os << std::endl;
        if (verbose >= 1) {
            os << "Number of jobs:                " << jobs.size() << " / " << n  << std::endl;
            os << "Number of duplicates:          " << number_of_duplicates << std::endl;
            os << "Number of overloaded batches:  " << number_of_overloaded_batches << std::endl;
            os << "Feasible:                      " << feasible << std::endl;
            os << "Number of batches:             " << number_of_batches << std::endl;
            os << "Total weighted tardiness:      " << total_weighted_tardiness << std::endl;
        }
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

}

}

