/**
 * Single machine scheduling problem with sequence-dependent setup times, total
 * weighted tardiness
 *
 * Input:
 * - n jobs; for each job j = 1..n
 *   - a due date dⱼ
 *   - a processing time pⱼ
 *   - a weight wⱼ
 * - an n×n matrix s containing the setup times between each pair of jobs
 * Problem:
 * - Find a sequance of jobs such that:
 *   - each job is scheduled exactly once
 * Objective:
 * - Minimize the total weighted tardiness of the schedule
 *
 */

#pragma once

#include "optimizationtools/utils/utils.hpp"
#include "optimizationtools/containers/sorted_on_demand_array.hpp"
#include "optimizationtools/containers/indexed_set.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>

namespace orproblems
{
namespace schedulingwithsdsttwt
{

using JobId = int64_t;
using JobPos = int64_t;
using Time = int64_t;
using Weight = double;

/**
 * Structure for a job.
 */
struct Job
{
    /** Processing-time of the job. */
    Time processing_time = 0;

    /** Due date of the job. */
    Time due_date = 0;

    /** Weight of the job. */
    Weight weight = 1;
};

/**
 * Instance class for a 'schedulingwithsdsttwt' problem.
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

    /** Get the number of jobs with a null weight. */
    inline JobId number_of_zero_weight_jobs() const { return number_of_zero_weight_jobs_; }

    /** Get the setup time between two jobs. */
    inline Time setup_time(
            JobId job_id_1,
            JobId job_id_2) const
    {
        return setup_times_[job_id_1][job_id_2];
    }

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
        }

        if (verbosity_level >= 2) {
            os << std::endl
                << std::setw(12) << "Job"
                << std::setw(12) << "Proc. time"
                << std::setw(12) << "Due date"
                << std::setw(12) << "Weight"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "----------"
                << std::setw(12) << "--------"
                << std::setw(12) << "------"
                << std::endl;
            for (JobId job_id = 0; job_id < number_of_jobs(); ++job_id) {
                const Job& job = this->job(job_id);
                os
                    << std::setw(12) << job_id
                    << std::setw(12) << job.processing_time
                    << std::setw(12) << job.due_date
                    << std::setw(12) << job.weight
                    << std::endl;
            }
        }

        if (verbosity_level >= 3) {
            os << std::endl
                << std::setw(12) << "Job 1"
                << std::setw(12) << "Job 2"
                << std::setw(12) << "Setup"
                << std::endl
                << std::setw(12) << "-----"
                << std::setw(12) << "-----"
                << std::setw(12) << "-----"
                << std::endl;
            for (JobId job_id_1 = 0; job_id_1 <= number_of_jobs(); ++job_id_1) {
                for (JobId job_id_2 = 0; job_id_2 < number_of_jobs(); ++job_id_2)
                    os
                        << std::setw(12) << job_id_1
                        << std::setw(12) << job_id_2
                        << std::setw(12) << setup_time(job_id_1, job_id_2)
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

        if (verbosity_level >= 2) {
            os << std::endl << std::right
                << std::setw(12) << "Job"
                << std::setw(12) << "Proc. time"
                << std::setw(12) << "Due date"
                << std::setw(12) << "Weight"
                << std::setw(12) << "Setup time"
                << std::setw(12) << "Time"
                << std::setw(12) << "TWT"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "----------"
                << std::setw(12) << "--------"
                << std::setw(12) << "------"
                << std::setw(12) << "----------"
                << std::setw(12) << "----"
                << std::setw(12) << "---"
                << std::endl;
        }

        JobId job_id = -1;
        JobId job_id_prev = number_of_jobs();
        optimizationtools::IndexedSet jobs(number_of_jobs());
        JobPos number_of_duplicates = 0;
        Time current_time = 0;
        Weight total_weighted_tardiness = 0;
        while (file >> job_id) {
            const Job& job = this->job(job_id);

            // Check duplicates.
            if (jobs.contains(job_id)) {
                number_of_duplicates++;
                if (verbosity_level >= 2) {
                    os << "Job " << job_id
                        << " has already been scheduled." << std::endl;
                }
            }
            jobs.add(job_id);

            current_time += setup_time(job_id_prev, job_id);
            current_time += job.processing_time;
            if (current_time > job.due_date)
                total_weighted_tardiness
                    += job.weight
                    * (current_time - job.due_date);
            if (verbosity_level >= 2) {
                os
                    << std::setw(12) << job_id
                    << std::setw(12) << job.processing_time
                    << std::setw(12) << job.due_date
                    << std::setw(12) << job.weight
                    << std::setw(12) << setup_time(job_id_prev, job_id)
                    << std::setw(12) << current_time
                    << std::setw(12) << total_weighted_tardiness
                    << std::endl;
            }
            job_id_prev = job_id;
        }

        bool feasible
            = (jobs.size() == number_of_jobs())
            && (number_of_duplicates == 0);

        if (verbosity_level >= 2)
            os << std::endl;
        if (verbosity_level >= 1) {
            os
                << "Number of jobs:            " << jobs.size() << " / " << number_of_jobs()  << std::endl
                << "Number of duplicates:      " << number_of_duplicates << std::endl
                << "Feasible:                  " << feasible << std::endl
                << "Total weighted tardiness:  " << total_weighted_tardiness << std::endl
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

    /** Setup times. */
    std::vector<std::vector<Time>> setup_times_;

    /** Number of jobs with a null weight. */
    JobPos number_of_zero_weight_jobs_ = 0;

    friend class InstanceBuilder;
};

class InstanceBuilder
{

public:

    /** Constructor. */
    InstanceBuilder() { }

    /**
     * Set the number of jobs.
     *
     * This method resets the instance.
     */
    void set_number_of_jobs(JobId number_of_jobs)
    {
        instance_.jobs_ = std::vector<Job>(number_of_jobs),
        instance_.setup_times_ = std::vector<std::vector<Time>>(
                number_of_jobs + 1,
                std::vector<Time>(number_of_jobs + 1, 0));
    }

    /** Set the processing-time of a job. */
    void set_processing_time(
            JobId job_id,
            Time processing_time)
    {
        instance_.jobs_[job_id].processing_time = processing_time;
    }

    /** Set the due date of a job. */
    void set_due_date(
            JobId job_id,
            Time due_date)
    {
        instance_.jobs_[job_id].due_date = due_date;
    }

    /** Set the weight of a job. */
    void set_weight(
            JobId job_id,
            Weight weight)
    {
        instance_.jobs_[job_id].weight = weight;
    }

    /** Set the setup time between two jobs. */
    void set_setup_time(
            JobId job_id_1,
            JobId job_id_2,
            Time setup_time)
    {
        if (job_id_1 == -1)
            job_id_1 = instance_.number_of_jobs();
        instance_.setup_times_[job_id_1][job_id_2] = setup_time;
    }

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

        if (format == "" || format == "cicirello2005") {
            read_cicirello2005(file);
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
        // Compute the number of jobs with a null weight.
        instance_.number_of_zero_weight_jobs_ = 0;
        for (JobId job_id = 0;
                job_id < instance_.number_of_jobs();
                ++job_id) {
            const Job& job = instance_.job(job_id);
            if (job.weight == 0)
                instance_.number_of_zero_weight_jobs_++;
        }

        return std::move(instance_);
    }

private:

    /*
     * Private methods
     */

    /** Read an instance from a file in 'cicirello2005' format. */
    void read_cicirello2005(std::ifstream& file)
    {
        std::string tmp;
        JobId number_of_jobs = -1;

        file >> tmp >> tmp >> tmp;
        file >> tmp >> tmp >> number_of_jobs;

        set_number_of_jobs(number_of_jobs);

        file >> tmp >> tmp >> tmp;
        file >> tmp >> tmp;
        file >> tmp >> tmp;
        file >> tmp >> tmp;
        file >> tmp >> tmp;
        file >> tmp >> tmp;
        file >> tmp >> tmp;
        file >> tmp >> tmp;
        file >> tmp >> tmp;
        file >> tmp >> tmp;
        file >> tmp >> tmp;
        file >> tmp >> tmp >> tmp;
        file >> tmp >> tmp >> tmp;

        file >> tmp >> tmp;
        Time p = -1;
        for (JobId job_id = 0; job_id < number_of_jobs; ++job_id) {
            file >> p;
            set_processing_time(job_id, p);
        }

        file >> tmp;
        Weight weight = -1;
        for (JobId job_id = 0; job_id < number_of_jobs; ++job_id) {
            file >> weight;
            set_weight(job_id, weight);
        }

        file >> tmp;
        Time due_date = -1;
        for (JobId job_id = 0; job_id < number_of_jobs; ++job_id) {
            file >> due_date;
            set_due_date(job_id, due_date);
        }

        file >> tmp >> tmp;
        Time setup_time = -1;
        for (JobId job_id_1 = -1; job_id_1 < number_of_jobs; ++job_id_1) {
            for (JobId job_id_2 = 0; job_id_2 < number_of_jobs; ++job_id_2) {
                if (job_id_1 == job_id_2)
                    continue;
                file >> tmp >> tmp >> setup_time;
                set_setup_time(job_id_1, job_id_2, setup_time);
            }
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
