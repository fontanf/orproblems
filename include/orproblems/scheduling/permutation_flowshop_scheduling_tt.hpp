/**
 * Permutation flow shop scheduling problem, total tardiness
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

#include "optimizationtools/containers/indexed_set.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>

namespace orproblems
{
namespace permutation_flowshop_scheduling_tt
{

using JobId = int64_t;
using JobPos = int64_t;
using MachineId = int64_t;
using Time = int64_t;

/**
 * Structure for a job.
 */
struct Job
{
    /** Processing-times on each machine. */
    std::vector<Time> processing_times;

    /** Due date of the job. */
    Time due_date;
};

/**
 * Instance class for a 'permutation_flowshop_scheduling_tt' problem.
 */
class Instance
{

public:

    /*
     * Getters
     */

    /** Get the number of machines. */
    inline MachineId number_of_machines() const { return number_of_machines_; }

    /** Get the number of jobs. */
    inline JobId number_of_jobs() const { return jobs_.size(); }

    /** Get a job. */
    inline const Job& job(JobId job_id) const { return jobs_[job_id]; }

    /*
     * Outputs
     */

    /** Print the instance. */
    void format(
            std::ostream& os,
            int verbosity_level = 1) const
    {
        if (verbosity_level >= 1) {
            os
                << "Number of machines:   " << number_of_machines() << std::endl
                << "Number of jobs:       " << number_of_jobs() << std::endl
                ;
        }

        if (verbosity_level >= 2) {
            os << std::endl
                << std::setw(12) << "Job"
                << std::setw(12) << "Due date"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "--------"
                << std::endl;
            for (JobId job_id = 0; job_id < number_of_jobs(); ++job_id) {
                const Job& job = this->job(job_id);
                os
                    << std::setw(12) << job_id
                    << std::setw(12) << job.due_date
                    << std::endl;
            }
        }

        if (verbosity_level >= 3) {
            os << std::endl
                << std::setw(12) << "Job"
                << std::setw(12) << "Machine"
                << std::setw(12) << "Proc. time"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "-------"
                << std::setw(12) << "----------"
                << std::endl;
            for (JobId job_id = 0; job_id < number_of_jobs(); ++job_id) {
                const Job& job = this->job(job_id);
                for (MachineId machine_id = 0;
                        machine_id < number_of_machines();
                        ++machine_id) {
                    os
                        << std::setw(12) << job_id
                        << std::setw(12) << machine_id
                        << std::setw(12) << job.processing_times[machine_id]
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
            os << std::endl << std::right
                << std::setw(12) << "Job"
                << std::setw(12) << "TT"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "--"
                << std::endl;
        }

        std::vector<Time> times(number_of_machines(), 0);
        JobId job_id = 0;
        optimizationtools::IndexedSet jobs(number_of_jobs());
        JobPos number_of_duplicates = 0;
        Time total_tardiness = 0;
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

            times[0] = times[0] + job.processing_times[0];
            for (MachineId machine_id = 1;
                    machine_id < number_of_machines();
                    ++machine_id) {
                if (times[machine_id - 1] > times[machine_id]) {
                    times[machine_id] = times[machine_id - 1]
                        + job.processing_times[machine_id];
                } else {
                    times[machine_id] = times[machine_id]
                        + job.processing_times[machine_id];
                }
            }
            if (times[number_of_machines() - 1] > job.due_date)
                total_tardiness += (times[number_of_machines() - 1] - job.due_date);

            if (verbosity_level >= 2) {
                os
                    << std::setw(12) << job_id
                    << std::setw(12) << total_tardiness
                    << std::endl;
            }
        }

        bool feasible
            = (jobs.size() == number_of_jobs())
            && (number_of_duplicates == 0);

        if (verbosity_level >= 2)
            os << std::endl;
        if (verbosity_level >= 1) {
            os
                << "Number of jobs:         " << jobs.size() << " / " << number_of_jobs() << std::endl
                << "Number of duplicates:   " << number_of_duplicates << std::endl
                << "Feasible:               " << feasible << std::endl
                << "Total tardiness:        " << total_tardiness << std::endl
                ;
        }
        return {feasible, total_tardiness};
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

    /** Number of machines. */
    MachineId number_of_machines_ = 1;

    /** Jobs. */
    std::vector<Job> jobs_;

    friend class InstanceBuilder;
};

class InstanceBuilder
{

public:

    /** Constructor. */
    InstanceBuilder() { }

    /**
     * Set the number of machines.
     *
     * This method resets all the jobs.
     */
    void set_number_of_machines(MachineId number_of_machines)
    {
        instance_.jobs_.clear();
        instance_.number_of_machines_ = number_of_machines;
    }

    /** Add jobs. */
    void add_jobs(JobId number_of_jobs)
    {
        Job job;
        job.processing_times = std::vector<Time>(instance_.number_of_machines(), 0);
        instance_.jobs_.insert(
                instance_.jobs_.end(),
                number_of_jobs,
                job);
    }

    /** Set the due date of a job. */
    void set_due_date(
            JobId job_id,
            Time due_date)
    {
        instance_.jobs_[job_id].due_date = due_date;
    }

    /** Set the processing-time of a job on a machine. */
    void set_processing_time(
            JobId job_id,
            MachineId machine_id,
            Time processing_time)
    {
        instance_.jobs_[job_id].processing_times[machine_id] = processing_time;
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

        if (format == "" || format == "vallada2008") {
            read_vallada2008(file);
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

    /** Read an instance from a file in 'vallada2008' format. */
    void read_vallada2008(std::ifstream& file)
    {
        JobId number_of_jobs;
        MachineId number_of_machines;
        file >> number_of_jobs >> number_of_machines;
        set_number_of_machines(number_of_machines);
        add_jobs(number_of_jobs);

        for (JobId job_id = 0; job_id < number_of_jobs; ++job_id) {
            Time processing_time = -1;
            MachineId machine_id_tmp = -1;
            for (MachineId machine_id = 0;
                    machine_id < number_of_machines;
                    ++machine_id) {
                file >> machine_id_tmp >> processing_time;
                set_processing_time(job_id, machine_id, processing_time);
            }
        }

        std::string tmp;
        file >> tmp;
        for (JobId job_id = 0; job_id < number_of_jobs; ++job_id) {
            Time due_date = -1;
            file >> tmp >> due_date >> tmp >> tmp;
            set_due_date(job_id, due_date);
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
