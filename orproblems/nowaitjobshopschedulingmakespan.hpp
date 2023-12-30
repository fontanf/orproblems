/**
 * No-wait job shop scheduling problem, makespan
 *
 * Input:
 * - m machines
 * - n jobs TODO
 * Problem:
 * - TODO
 * Objective:
 * - Minimize the makespan of the schedule
 *
 */

#pragma once

#include "optimizationtools/containers/indexed_set.hpp"

#include "interval_tree.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>

namespace orproblems
{
namespace nowaitjobshopschedulingmakespan
{

using JobId = int64_t;
using JobPos = int64_t;
using OperationId = int64_t;
using MachineId = int64_t;
using Time = int64_t;

/**
 * Structure for an operation.
 */
struct Operation
{
    /** Machine. */
    MachineId machine_id = -1;

    /* Processing time. */
    Time processing_time = -1;
};

/**
 * Instance class for a 'nowaitjobshopschedulingmakespan' problem.
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
    inline JobId number_of_jobs() const { return operations_.size(); }

    /** Get the number of operations. */
    inline JobId number_of_operations() const { return number_of_operations_; }

    /** Get the number of operations of a job. */
    inline OperationId number_of_operations(JobId job_id) const { return operations_[job_id].size(); }

    /** Get an operation. */
    inline const Operation& operation(
            JobId job_id,
            OperationId operation_pos) const
    {
        return operations_[job_id][operation_pos];
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
                << "Number of machines:    " << number_of_machines() << std::endl
                << "Number of jobs:        " << number_of_jobs() << std::endl
                << "Number of operations:  " << number_of_operations() << std::endl
                ;
        }

        // Print jobs.
        if (verbosity_level >= 2) {
            os << std::endl
                << std::setw(12) << "Job"
                << std::setw(12) << "# op."
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "-----"
                << std::endl;
            for (JobId job_id = 0; job_id < number_of_jobs(); ++job_id) {
                os
                    << std::setw(12) << job_id
                    << std::setw(12) << number_of_operations(job_id)
                    << std::endl;
            }
        }

        // Print operations.
        if (verbosity_level >= 3) {
            os << std::endl
                << std::setw(12) << "Job"
                << std::setw(12) << "Operation"
                << std::setw(12) << "Machine"
                << std::setw(12) << "Proc. time"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "---------"
                << std::setw(12) << "-------"
                << std::setw(12) << "----------"
                << std::endl;
            for (JobId job_id = 0; job_id < number_of_jobs(); ++job_id) {
                for (OperationId operation_id = 0;
                        operation_id < number_of_operations(job_id);
                        ++operation_id) {
                    os
                        << std::setw(12) << job_id
                        << std::setw(12) << operation_id
                        << std::setw(12) << operation(job_id, operation_id).machine_id
                        << std::setw(12) << operation(job_id, operation_id).processing_time
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
        // Initial display.
        if (verbosity_level >= 1) {
            os
                << "Checker" << std::endl
                << "-------" << std::endl;
        }

        std::ifstream file(certificate_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");
        }

        if (verbosity_level >= 2) {
            os << std::endl << std::right
                << std::setw(12) << "Job"
                << std::setw(12) << "Operation"
                << std::setw(12) << "Start"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "---------"
                << std::setw(12) << "-----"
                << std::endl;
        }

        std::vector<lib_interval_tree::interval_tree_t<Time>> intervals(number_of_machines());
        JobId job_id = 0;
        Time start_time = 0;
        OperationId number_of_overlaps = 0;
        OperationId number_of_negative_starts = 0;
        while (file >> start_time) {
            if (start_time < 0)
                number_of_negative_starts++;
            Time current_time = start_time;
            for (OperationId operation_id = 0;
                    operation_id < number_of_operations(job_id);
                    ++operation_id) {
                const Operation& operation = this->operation(job_id, operation_id);

                Time completion_time = current_time + operation.processing_time;
                if (intervals[operation.machine_id].overlap_find({current_time, completion_time}, true)
                        != intervals[operation.machine_id].end())
                    number_of_overlaps++;
                intervals[operation.machine_id].insert_overlap({current_time, completion_time});

                if (verbosity_level >= 2) {
                    os
                        << std::setw(12) << job_id
                        << std::setw(12) << operation_id
                        << std::setw(12) << current_time
                        << std::endl;
                }

                current_time = completion_time;
            }
            job_id += 1;
        }

        // Compute makespan.
        Time makespan = 0;
        for (MachineId machine_id = 0;
                machine_id < number_of_machines();
                ++machine_id) {
            for (const auto& interval: intervals[machine_id])
                makespan = std::max(makespan, interval.high());
        }

        bool feasible
            = (job_id == number_of_jobs())
            && (number_of_overlaps == 0)
            && (number_of_negative_starts == 0);

        if (verbosity_level >= 2)
            os << std::endl;
        if (verbosity_level >= 1) {
            os
                << "Number of jobs:             " << job_id << " / " << number_of_jobs()  << std::endl
                << "Number of negative starts:  " << number_of_negative_starts << std::endl
                << "Number of overlaps:         " << number_of_overlaps << std::endl
                << "Feasible:                   " << feasible << std::endl
                << "Makespan:                   " << makespan << std::endl
                ;
        }
        return {feasible, makespan};
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
    MachineId number_of_machines_ = 0;

    /** Operations. */
    std::vector<std::vector<Operation>> operations_;

    /*
     * Computed attributes
     */

    /** Number of machines. */
    OperationId number_of_operations_ = 0;

    friend class InstanceBuilder;
};

class InstanceBuilder
{

public:

    /** Constructor. */
    InstanceBuilder() { }

    /** Set the number of machines. */
    void set_number_of_machines(MachineId number_of_machines)
    {
        instance_.number_of_machines_ = number_of_machines;
    }

    /** Add a job. */
    void add_job() { instance_.operations_.push_back({}); }

    /** Add an operation. */
    void add_operation(
            JobId job_id,
            MachineId machine_id,
            Time processing_time)
    {
        Operation operation;
        operation.machine_id = machine_id;
        operation.processing_time = processing_time;
        instance_.operations_[job_id].push_back(operation);
    }

    void read(
            const std::string& instance_path,
            const std::string& format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        }

        if (format == "" || format == "default" || format == "tamy0612") {
            read_tamy0612(file);
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
        // Compute number of operations.
        instance_.number_of_operations_ = 0;
        for (JobId job_id = 0; job_id < instance_.number_of_jobs(); ++job_id)
            instance_.number_of_operations_ += instance_.number_of_operations(job_id);

        return std::move(instance_);
    }

private:

    /*
     * Private methods
     */

    void read_tamy0612(std::ifstream& file)
    {
        std::string tmp;
        do {
            getline(file, tmp);
        } while (tmp[0] == '#');
        std::stringstream ss(tmp);

        JobId number_of_jobs = -1;
        MachineId number_of_machines = -1;
        ss >> number_of_jobs;
        ss >> number_of_machines;
        set_number_of_machines(number_of_machines);

        Time processing_time = -1;
        MachineId machine_id = -1;
        for (JobId job_id = 0; job_id < number_of_jobs; ++job_id) {
            add_job();
            do {
                getline(file, tmp);
            } while (tmp[0] == '#');
            std::stringstream ss(tmp);
            for (MachineId machine_id_tmp = 0;
                    machine_id_tmp < number_of_machines;
                    ++machine_id_tmp) {
                ss >> machine_id >> processing_time;
                add_operation(
                        job_id,
                        machine_id,
                        processing_time);
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
