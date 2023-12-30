/**
 * Distributed permutation flow shop scheduling problem, total completion time
 *
 * Input:
 * - F factories
 * - m machines
 * - n jobs composed of m operations for each machine with pᵢⱼ the processing
 *   time of the operation of job j on machine i, j = 1..n, i = 1..m
 * Problem:
 * - Find a schedule of jobs for each factory such that:
 *   - all operations of all jobs are scheduled exactly once
 *   - for all job j = 1..n, i = 1..m - 1, operations (j, i + 1) starts after
 *     the end of operation (j, i)
 *   - the job sequence is the same on all machines of a factory
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
namespace distributedpfsstct
{

using JobId = int64_t;
using JobPos = int64_t;
using MachineId = int64_t;
using FactoryId = int64_t;
using Time = int64_t;

/**
 * Instance class for a 'distributedpfsstct' problem.
 */
class Instance
{

public:

    /*
     * Getters
     */

    /** Get the number of factories. */
    inline FactoryId number_of_factories() const { return number_of_factories_; }

    /** Get the number of machines. */
    inline MachineId number_of_machines() const { return number_of_machines_; }

    /** Get the number of jobs. */
    inline JobId number_of_jobs() const { return processing_times_.size(); }

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
                << "Number of factories:  " << number_of_factories() << std::endl
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
                << std::setw(12) << "Factory"
                << std::setw(12) << "Job"
                << std::setw(12) << "Time"
                << std::setw(12) << "TCT"
                << std::endl
                << std::setw(12) << "-------"
                << std::setw(12) << "---"
                << std::setw(12) << "----"
                << std::setw(12) << "---"
                << std::endl;
        }

        optimizationtools::IndexedSet jobs(number_of_jobs());
        JobPos number_of_duplicates = 0;
        JobPos factory_number_of_jobs = -1;
        Time total_completion_time = 0;
        for (FactoryId factory_id = 0;
                factory_id < number_of_factories();
                ++factory_id) {
            file >> factory_number_of_jobs;

            std::vector<Time> times(number_of_machines(), 0);
            JobId job_id = -1;
            for (JobPos pos = 0; pos < factory_number_of_jobs; ++pos) {
                file >> job_id;

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
                        << std::setw(12) << factory_id
                        << std::setw(12) << job_id
                        << std::setw(12) << times[number_of_machines() - 1]
                        << std::setw(12) << total_completion_time
                        << std::endl;
                }
            }
        }

        bool feasible
            = (jobs.size() == number_of_jobs())
            && (number_of_duplicates == 0);

        if (verbosity_level == 2)
            os << std::endl;
        if (verbosity_level >= 1) {
            os << "Number of jobs:         " << jobs.size() << " / " << number_of_jobs() << std::endl;
            os << "Number of duplicates:   " << number_of_duplicates << std::endl;
            os << "Feasible:               " << feasible << std::endl;
            os << "Total completion time:  " << total_completion_time << std::endl;
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

    /** Number of factories. */
    FactoryId number_of_factories_ = 1;

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

    /** Set the number of factories. */
    void set_number_of_factories(FactoryId number_of_factories) { instance_.number_of_factories_ = number_of_factories; }

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

        if (format == "" || format == "default" || format == "naderi2010") {
            read_naderi2010(file);
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

    /** Read an instance from a file in 'naderi2010' format. */
    void read_naderi2010(std::ifstream& file)
    {
        JobId number_of_jobs;
        MachineId number_of_machines;
        file >> number_of_jobs;
        file >> number_of_machines;
        file >> instance_.number_of_factories_;
        set_number_of_machines(number_of_machines);
        add_jobs(number_of_jobs);

        Time processing_time = -1;
        MachineId machine_id_tmp = -1;
        for (JobId job_id = 0; job_id < number_of_jobs; job_id++) {
            for (MachineId machine_id = 0;
                    machine_id < number_of_machines;
                    ++machine_id) {
                file >> machine_id_tmp >> processing_time;
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
