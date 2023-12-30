/**
 * Single machine batch scheduling problem, total weighted tardiness
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

using JobId = int64_t;
using JobPos = int64_t;
using Time = int64_t;
using Weight = int64_t;
using Size = int64_t;
using Area = int64_t;

/**
 * Structure for a job.
 */
struct Job
{
    /** Processing-time of the job. */
    Time processing_time;

    /** Release date of the job. */
    Time release_date;

    /** Due date of the job. */
    Time due_date;

    /** Size of the job. */
    Size size;

    /** Weight of the job. */
    Weight weight;
};

/**
 * Instance class for a 'batchschedulingtotalweightedtardiness' problem.
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
            for (JobId job_id = 0; job_id < number_of_jobs(); ++job_id) {
                const Job& job = this->job(job_id);
                os << std::setw(12) << job_id
                    << std::setw(12) << job.processing_time
                    << std::setw(12) << job.release_date
                    << std::setw(12) << job.due_date
                    << std::setw(12) << job.size
                    << std::setw(12) << job.weight
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
        Time total_weighted_tardiness = 0;

        if (verbosity_level >= 2) {
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

        while (file >> current_batch_size) {
            JobId job_id = -1;
            number_of_batches++;
            std::vector<JobId> batch_jobs;
            Time current_batch_start = current_batch_end;
            Time current_batch_time = 0;
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

                batch_jobs.push_back(job_id);
                if (current_batch_start < job.release_date)
                    current_batch_start = job.release_date;
                if (current_batch_time < job.processing_time)
                    current_batch_time = job.processing_time;
                current_batch_end = current_batch_start + current_batch_time;

                if (verbosity_level >= 2) {
                    os
                        << std::setw(12) << job_id
                        << std::setw(12) << job.processing_time
                        << std::setw(12) << job.release_date
                        << std::setw(12) << job.due_date
                        << std::setw(12) << job.size
                        << std::setw(12) << job.weight
                        << std::setw(12) << current_batch_start
                        << std::setw(12) << batch_jobs.size()
                        << std::setw(12) << current_batch_end
                        << std::endl;
                }

            }
            for (JobId job_id: batch_jobs) {
                const Job& job = this->job(job_id);
                if (current_batch_end > job.due_date) {
                    total_weighted_tardiness += job.weight
                        * (current_batch_end - job.due_date);
                }
            }
            if (verbosity_level >= 2) {
                os << "Batch " << number_of_batches - 1
                    << "; number of jobs: " << batch_jobs.size()
                    << "; total weighted tardiness: " << total_weighted_tardiness
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
                << "Total weighted tardiness:      " << total_weighted_tardiness << std::endl
                ;
        }
        return {feasible, total_weighted_tardiness};
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

    /** Batch capacity. */
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
            Time release_date,
            Time due_date,
            Size size,
            Weight weight)
    {
        Job job;
        job.processing_time = processing_time;
        job.release_date = release_date;
        job.due_date = due_date;
        job.size = size;
        job.weight = weight;
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
        if (format == "" || format == "queiroga2020") {
            read_queiroga2020(file);
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

    /** Read an instance from a file in 'queiroga2020' format. */
    void read_queiroga2020(std::ifstream& file)
    {
        JobId number_of_jobs = -1;
        Size capacity = -1;
        file >> number_of_jobs >> capacity;
        set_capacity(capacity);

        Time processing_time;
        Time release_date;
        Time due_date;
        Size size;
        Weight weight;
        for (JobId job_id = 0; job_id < number_of_jobs; ++job_id) {
            file
                >> processing_time
                >> due_date
                >> size
                >> weight
                >> release_date;
            add_job(processing_time,
                    release_date,
                    due_date,
                    size,
                    weight);
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
