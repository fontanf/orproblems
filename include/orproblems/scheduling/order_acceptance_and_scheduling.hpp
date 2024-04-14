/**
 * Single machine order acceptance and scheduling problem with
 * sequence-dependent setup times
 *
 * Input:
 * - n jobs; for each job j = 1..n
 *   - a release date rⱼ
 *   - a due date dⱼ
 *   - a deadline đⱼ
 *   - a processing time pⱼ
 *   - a weight wⱼ
 *   - a profit vⱼ
 * - an n×n symmetric matrix s containing the setup times between each
 *   pair of jobs
 * Problem:
 * - find a sequence of jobs starting with job 1 and ending with job n such
 *   that:
 *   - each scheduled job starts after its release date
 *     !!! The start date of a job is before its setup time !!!
 *   - each scheduled job terminates before its deadline
 * Objective:
 * - maximize the profit of the scheduled jobs minus their weighted tardiness
 *
 */

#pragma once

#include "optimizationtools/utils/utils.hpp"
#include "optimizationtools/containers/indexed_set.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>

namespace orproblems
{
namespace order_acceptance_and_scheduling
{

using JobId = int64_t;
using JobPos = int64_t;
using Time = int64_t;
using Weight = double;
using Profit = double;

/**
 * Structure for a job.
 */
struct Job
{
    /** Release date of the job. */
    Time release_date;

    /** Due date of the job. */
    Time due_date;

    /** Deadline of the job. */
    Time deadline;

    /** Processing-time of the job. */
    Time processing_time;

    /** Weight of the job. */
    Weight weight;

    /** Profit of the job. */
    Profit profit;
};

/**
 * Instance class for a 'order_acceptance_and_scheduling' problem.
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
                << std::setw(12) << "Rel. date"
                << std::setw(12) << "Due date"
                << std::setw(12) << "Deadline"
                << std::setw(12) << "Weight"
                << std::setw(12) << "Profit"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "----------"
                << std::setw(12) << "---------"
                << std::setw(12) << "--------"
                << std::setw(12) << "--------"
                << std::setw(12) << "------"
                << std::setw(12) << "------"
                << std::endl;
            for (JobId job_id = 0; job_id < number_of_jobs(); ++job_id) {
                const Job& job = this->job(job_id);
                os
                    << std::setw(12) << job_id
                    << std::setw(12) << job.processing_time
                    << std::setw(12) << job.release_date
                    << std::setw(12) << job.due_date
                    << std::setw(12) << job.deadline
                    << std::setw(12) << job.weight
                    << std::setw(12) << job.profit
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
            for (JobId job_id_1 = 0;
                    job_id_1 < number_of_jobs();
                    ++job_id_1) {
                for (JobId job_id_2 = job_id_1 + 1;
                        job_id_2 < number_of_jobs();
                        ++job_id_2) {
                    os
                        << std::setw(12) << job_id_1
                        << std::setw(12) << job_id_2
                        << std::setw(12) << setup_time(job_id_1, job_id_2)
                        << std::endl;
                }
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
            os << std::endl
                << std::setw(12) << "Job"
                << std::setw(12) << "Time"
                << std::setw(12) << "Profit"
                << std::setw(12) << "TWT"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "----"
                << std::setw(12) << "------"
                << std::setw(12) << "---"
                << std::endl;
        }

        JobId job_id = -1;
        JobId job_id_pred = 0;
        optimizationtools::IndexedSet jobs(number_of_jobs());
        JobPos duplicates = 0;
        JobPos number_of_deadline_violations = 0;
        Time current_time = 0;
        Profit profit = 0.0;
        Weight total_weighted_tardiness = 0.0;
        while (file >> job_id) {
            const Job& job = this->job(job_id);

            // Check duplicates.
            if (jobs.contains(job_id)) {
                duplicates++;
                if (verbosity_level >= 2) {
                    os << "Job " << job_id
                        << " has already been scheduled." << std::endl;
                }
            }
            jobs.add(job_id);

            current_time = std::max(current_time, job.release_date)
                + setup_time(job_id_pred, job_id) + job.processing_time;
            profit += job.profit;
            if (current_time > job.due_date)
                total_weighted_tardiness += job.weight * (current_time - job.due_date);

            // Check deadline.
            if (current_time > job.deadline) {
                number_of_deadline_violations++;
                if (verbosity_level >= 2) {
                    os << "Job " << job_id << " ends after its deadline: "
                        << current_time << " / " << job.deadline
                        << "." << std::endl;
                }
            }

            if (verbosity_level >= 2) {
                os
                    << std::setw(12) << job_id
                    << std::setw(12) << current_time
                    << std::setw(12) << profit
                    << std::setw(12) << total_weighted_tardiness
                    << std::endl;
            }

            job_id_pred = job_id;
        }

        bool feasible
            = (duplicates == 0)
            && (number_of_deadline_violations == 0)
            && (!jobs.contains(0))
            && (!jobs.contains(number_of_jobs() - 1));

        if (verbosity_level >= 2)
            os << std::endl;
        if (verbosity_level >= 1) {
            os
                << "Number of jobs:                 " << jobs.size() << " / " << number_of_jobs() - 2 << std::endl
                << "Number of duplicates:           " << duplicates << std::endl
                << "Number of deadline violations:  " << number_of_deadline_violations << std::endl
                << "Feasible:                       " << feasible << std::endl
                << "Profit:                         " << profit << std::endl
                << "Total weighted tardiness:       " << total_weighted_tardiness << std::endl
                << "Objective:                      " << profit - total_weighted_tardiness << std::endl
                ;
        }
        return {feasible, profit - total_weighted_tardiness};
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
     * This method resets all the jobs.
     */
    void set_number_of_jobs(JobId number_of_jobs)
    {
        instance_.jobs_ = std::vector<Job>(number_of_jobs);
        instance_.setup_times_ = std::vector<std::vector<Time>>(
                number_of_jobs,
                std::vector<Time>(number_of_jobs));
    }

    /** Set the release date of a job. */
    void set_job_release_date(
            JobId job_id,
            Time release_date)
    {
        instance_.jobs_[job_id].release_date = release_date;
    }

    /** Set the due date of a job. */
    void set_job_due_date(
            JobId job_id,
            Time due_date)
    {
        instance_.jobs_[job_id].due_date = due_date;
    }

    /** Set the deadline of a job. */
    void set_job_deadline(
            JobId job_id,
            Time deadline)
    {
        instance_.jobs_[job_id].deadline = deadline;
    }

    /** Set the processing time of a job. */
    void set_job_processing_time(
            JobId job_id,
            Time processing_time)
    {
        instance_.jobs_[job_id].processing_time = processing_time;
    }

    /** Set the weight of a job. */
    void set_job_weight(
            JobId job_id,
            Weight weight)
    {
        instance_.jobs_[job_id].weight = weight;
    }

    /** Set the profit of a job. */
    void set_job_profit(
            JobId job_id,
            Profit profit)
    {
        instance_.jobs_[job_id].profit = profit;
    }

    /** Set the setup time between two jobs. */
    void set_setup_time(
            JobId job_id_1,
            JobId job_id_2,
            Time setup_time)
    {
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
        if (format == "" || format == "cesaret2012") {
            read_cesaret2012(file);
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

    /** Read an instance from a file in 'cesaret2012' format. */
    void read_cesaret2012(std::ifstream& file)
    {
        std::string tmp;
        std::vector<std::string> line;

        getline(file, tmp);
        line = optimizationtools::split(tmp, ',');
        JobId number_of_jobs = line.size();
        set_number_of_jobs(number_of_jobs);
        for (JobId job_id = 0; job_id < number_of_jobs; ++job_id)
            set_job_release_date(job_id, std::stol(line[job_id]));
        getline(file, tmp);
        line = optimizationtools::split(tmp, ',');
        for (JobId job_id = 0; job_id < number_of_jobs; ++job_id)
            set_job_processing_time(job_id, std::stol(line[job_id]));
        getline(file, tmp);
        line = optimizationtools::split(tmp, ',');
        for (JobId job_id = 0; job_id < number_of_jobs; ++job_id)
            set_job_due_date(job_id, std::stol(line[job_id]));
        getline(file, tmp);
        line = optimizationtools::split(tmp, ',');
        for (JobId job_id = 0; job_id < number_of_jobs; ++job_id)
            set_job_deadline(job_id, std::stol(line[job_id]));
        getline(file, tmp);
        line = optimizationtools::split(tmp, ',');
        for (JobId job_id = 0; job_id < number_of_jobs; ++job_id)
            set_job_profit(job_id, std::stod(line[job_id]));
        getline(file, tmp);
        line = optimizationtools::split(tmp, ',');
        for (JobId job_id = 0; job_id < number_of_jobs; ++job_id)
            set_job_weight(job_id, std::stod(line[job_id]));
        for (JobId job_id_1 = 0; job_id_1 < number_of_jobs; ++job_id_1) {
            getline(file, tmp);
            line = optimizationtools::split(tmp, ',');
            for (JobId job_id_2 = 0; job_id_2 < number_of_jobs; ++job_id_2)
                set_setup_time(job_id_1, job_id_2, std::stol(line[job_id_2]));
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
