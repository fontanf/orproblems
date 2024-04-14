/**
 * Single machine batch scheduling problem, total completion time
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

#pragma once

#include "optimizationtools/containers/indexed_set.hpp"

#include <stdexcept>
#include <fstream>
#include <iostream>
#include <iomanip>

namespace orproblems
{
namespace batch_scheduling_total_completion_time
{

using JobId = int64_t;
using JobPos = int64_t;
using Time = int64_t;
using Size = int64_t;
using Area = int64_t;

/**
 * Structure for a job.
 */
struct Job
{
    /** Processing-time of the job. */
    Time processing_time;

    /** Size of the job. */
    Size size;
};

/**
 * Instance class for a 'batch_scheduling_total_completion_time' problem.
 */
class Instance
{

public:

    /*
     * Getters
     */

    /** Get the number of jobs. */
    inline JobId number_of_jobs() const { return jobs_.size(); }

    /** Get a job. */
    inline const Job& job(JobId job_id) const { return jobs_[job_id]; }

    /** Get the capacity of the batches. */
    inline Size capacity() const { return capacity_; }

    /*
     * Outputs
     */

    /** Print the instance. */
    void format(
            std::ostream& os,
            int verbosity_level = 1) const
    {
        if (verbosity_level >= 1) {
            os << "Number of jobs:  " << number_of_jobs() << std::endl;
            os << "Batch capacity:  " << capacity() << std::endl;
        }

        if (verbosity_level >= 2) {
            os << std::endl
                << std::setw(12) << "Job"
                << std::setw(12) << "Proc. time"
                << std::setw(12) << "Size"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "----------"
                << std::setw(12) << "---------"
                << std::setw(12) << "--------"
                << std::setw(12) << "----"
                << std::setw(12) << "------"
                << std::endl;
            for (JobId job_id = 0; job_id < number_of_jobs(); ++job_id) {
                const Job& job = this->job(job_id);
                os << std::setw(12) << job_id
                    << std::setw(12) << job.processing_time
                    << std::setw(12) << job.size
                    << std::endl;
            }
        }
    }

    /** Check a certificate. */
    std::pair<bool, Time> check(
            const std::string& certificate_path,
            std::ostream& os,
            int verbosity_level = 1) const
    {
        std::ifstream file(certificate_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");
        }

        JobPos current_batch_size = -1;
        optimizationtools::IndexedSet jobs(number_of_jobs());
        JobPos number_of_batches = 0;
        JobPos number_of_duplicates = 0;
        JobPos number_of_overloaded_batches = 0;
        Time current_batch_end = 0;
        Time total_completion_time = 0;

        if (verbosity_level >= 2) {
            os << std::endl << std::right
                << std::setw(12) << "Job"
                << std::setw(12) << "Proc. time"
                << std::setw(12) << "Size"
                << std::setw(12) << "Bat. start"
                << std::setw(12) << "Batch size"
                << std::setw(12) << "Batch end"
                << std::setw(12) << "TCT"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "----------"
                << std::setw(12) << "----"
                << std::setw(12) << "----------"
                << std::setw(12) << "----------"
                << std::setw(12) << "---------"
                << std::setw(12) << "---"
                << std::endl;
        }

        while (file >> current_batch_size) {
            JobId job_id = -1;
            number_of_batches++;
            Time current_batch_start = current_batch_end;
            Time current_batch_time = 0;
            Size current_batch_size = 0;
            for (JobPos job_pos = 0; job_pos < current_batch_size; ++job_pos) {
                file >> job_id;
                const Job& job = this->job(job_id);

                // Check duplicates.
                if (jobs.contains(job_id)) {
                    number_of_duplicates++;
                    if (verbosity_level >= 2) {
                        os << std::endl << "Job " << job_id
                            << " has already benn scheduled." << std::endl;
                    }
                }
                jobs.add(job_id);

                current_batch_size += job.size;
                if (current_batch_time < job.processing_time)
                    current_batch_time = job.processing_time;
                current_batch_end = current_batch_start + current_batch_time;

                if (verbosity_level >= 2) {
                    os
                        << std::setw(12) << job_id
                        << std::setw(12) << job.processing_time
                        << std::setw(12) << job.size
                        << std::setw(12) << current_batch_start
                        << std::setw(12) << current_batch_size
                        << std::setw(12) << current_batch_end
                        << std::endl;
                }

            }
            total_completion_time += current_batch_size * current_batch_end;

            if (verbosity_level >= 2) {
                os << "Batch " << number_of_batches - 1
                    << "; number of jobs: " << current_batch_size
                    << "; total completion time: " << total_completion_time
                    << std::endl;
            }

            // Check batch capacity.
            if (current_batch_size > capacity()) {
                number_of_overloaded_batches++;
                if (verbosity_level == 2)
                    os << "Batch " << number_of_batches - 1 << " is overloaded." << std::endl;
            }

            current_batch_start = current_batch_end;
        }

        bool feasible
            = (jobs.size() == number_of_jobs())
            && (number_of_duplicates == 0)
            && (number_of_overloaded_batches == 0);

        if (verbosity_level >= 2)
            os << std::endl;
        if (verbosity_level >= 1) {
            os
                << "Number of jobs:                " << jobs.size() << " / " << number_of_jobs()  << std::endl
                << "Number of duplicates:          " << number_of_duplicates << std::endl
                << "Number of overloaded batches:  " << number_of_overloaded_batches << std::endl
                << "Feasible:                      " << feasible << std::endl
                << "Number of batches:             " << number_of_batches << std::endl
                << "Total completion time:         " << total_completion_time << std::endl
                ;
        }
        return {feasible, total_completion_time};
    }

private:

    /*
     * Private methods
     */

    /** Constructor to build an instance manually. */
    Instance() { }

    /*
     * Private attributes
     */

    /** Jobs. */
    std::vector<Job> jobs_;

    /** Capacity of the batches. */
    Size capacity_ = 0;

    friend class InstanceBuilder;
};

class InstanceBuilder
{

public:

    /** Constructor. */
    InstanceBuilder() { }

    /** Add a job. */
    void add_job(
            Time processing_time,
            Size size)
    {
        Job job;
        job.processing_time = processing_time;
        job.size = size;
        instance_.jobs_.push_back(job);
    }

    /** Set the capacity of the batches. */
    void set_capacity(Size capacity) { instance_.capacity_ = capacity; }

    /** Build an instance from a file. */
    void read(
            const std::string& instance_path,
            const std::string& format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        }
        if (format == "" || format == "alfieri2021") {
            read_alfieri2021(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    /*
     * Build
     */

    /** Build the instance. */
    Instance build()
    {
        return std::move(instance_);
    }

private:

    /*
     * Private methods
     */

    /** Read an instance from a file in 'alfieri2021' format. */
    void read_alfieri2021(std::ifstream& file)
    {
        JobId number_of_jobs = -1;
        Size capacity = -1;
        file >> number_of_jobs >> capacity;
        set_capacity(capacity);

        Time processing_time;
        Size size;
        for (JobId job_id = 0; job_id < number_of_jobs; ++job_id) {
            file >> processing_time >> size;
            add_job(processing_time, size);
        }
    }

    /*
     * Private attributes
     */

    /** Instance. */
    Instance instance_;

};

}
}
