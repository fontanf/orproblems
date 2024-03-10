/**
 * Permutation flow shop scheduling problem, total completion time
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
 * - Minimize the total completion time of the jobs
 *
 */

#pragma once

#include "optimizationtools/containers/indexed_set.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>

namespace orproblems
{
namespace permutation_flowshop_scheduling_tct
{

using JobId = int64_t;
using JobPos = int64_t;
using MachineId = int64_t;
using Time = int64_t;

/**
 * Instance class for a 'permutation_flowshop_scheduling_tct' problem.
 */
class Instance
{

public:

    /*
     * Getters
     */

    /** Get the number of jobs. */
    inline JobId number_of_jobs() const { return processing_times_.size(); }

    /** Get the number of machines. */
    inline MachineId number_of_machines() const { return processing_times_[0].size(); }

    /** Get the processing-time of a job on a machine. */
    inline Time processing_time(
            JobId job_id,
            MachineId machine_id) const
    {
        return processing_times_[job_id][machine_id];
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
            os
                << "Number of machines:   " << number_of_machines() << std::endl
                << "Number of jobs:       " << number_of_jobs() << std::endl
                ;
        }

        if (verbosity_level >= 2) {
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
                for (MachineId machine_id = 0;
                        machine_id < number_of_machines();
                        ++machine_id) {
                    os
                        << std::setw(12) << job_id
                        << std::setw(12) << machine_id
                        << std::setw(12) << processing_time(job_id, machine_id)
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
                << std::setw(12) << "TCT"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "---"
                << std::endl;
        }

        std::vector<Time> times(number_of_machines(), 0);
        JobId job_id = -1;
        optimizationtools::IndexedSet jobs(number_of_jobs());
        JobPos number_of_duplicates = 0;
        Time total_completion_time = 0;
        while (file >> job_id) {
            // Check duplicates.
            if (jobs.contains(job_id)) {
                number_of_duplicates++;
                if (verbosity_level >= 2) {
                    os << "Job " << job_id
                        << " has already been scheduled." << std::endl;
                }
            }
            jobs.add(job_id);

            times[0] = times[0] + processing_time(job_id, 0);
            for (MachineId machine_id = 1;
                    machine_id < number_of_machines();
                    ++machine_id) {
                if (times[machine_id - 1] > times[machine_id]) {
                    times[machine_id] = times[machine_id - 1]
                        + processing_time(job_id, machine_id);
                } else {
                    times[machine_id] = times[machine_id]
                        + processing_time(job_id, machine_id);
                }
            }
            total_completion_time += times[number_of_machines() - 1];

            if (verbosity_level >= 2) {
                os
                    << std::setw(12) << job_id
                    << std::setw(12) << total_completion_time
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
                << "Number of jobs:         " << jobs.size() << " / " << number_of_jobs()  << std::endl
                << "Number of duplicates:   " << number_of_duplicates << std::endl
                << "Feasible:               " << feasible << std::endl
                << "Total completion time:  " << total_completion_time << std::endl
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

    /** Number of machines. */
    MachineId number_of_machines_ = 1;

    /** Processing-times. */
    std::vector<std::vector<Time>> processing_times_;

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
        instance_.processing_times_.clear();
        instance_.number_of_machines_ = number_of_machines;
    }

    /** Add jobs. */
    void add_jobs(JobId number_of_jobs)
    {
        instance_.processing_times_.insert(
                instance_.processing_times_.end(),
                number_of_jobs,
                std::vector<Time>(instance_.number_of_machines(), 0));
    }

    /** Set the processing-time of a job on a machine. */
    void set_processing_time(
            JobId job_id,
            MachineId machine_id,
            Time processing_time)
    {
        instance_.processing_times_[job_id][machine_id] = processing_time;
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
        if (format == "" || format == "default") {
            read_default(file);
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

    /** Read an instance from a file in 'default' format. */
    void read_default(std::ifstream& file)
    {
        JobId number_of_jobs;
        MachineId number_of_machines;
        file >> number_of_jobs;
        file >> number_of_machines;
        set_number_of_machines(number_of_machines);
        add_jobs(number_of_jobs);

        Time processing_time;
        for (MachineId machine_id = 0;
                machine_id < number_of_machines;
                machine_id++) {
            for (JobId job_id = 0; job_id < number_of_jobs; job_id++) {
                file >> processing_time;
                set_processing_time(job_id, machine_id, processing_time);
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
