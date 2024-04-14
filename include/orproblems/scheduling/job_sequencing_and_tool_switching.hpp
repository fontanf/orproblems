/**
 * Job sequencing and tool switching
 *
 * Input:
 * - A magazine capacity C
 * - m tools
 * - n jobs; for each job j, j = 1..n, a list of required tools Tⱼ
 * Problem:
 * - Find a schedule of jobs and a tool loading strategy such that:
 *   - When a job is performed, all its required tools are in the magazine
 *   - The simultaneous number of tools in the magazine never exceed its
 *     capacity
 * Objective:
 * - Minimizes the total number of switches, calculated as the number of times a
 * tool is replaced by another
 *
 */

#pragma once

#include "optimizationtools//containers/indexed_binary_heap.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

namespace orproblems
{
namespace job_sequencing_and_tool_switching
{

using JobId = int64_t;
using JobPos = int64_t;
using ToolId = int64_t;

/**
 * Instance class for a 'job_sequencing_and_tool_switching' problem.
 */
class Instance
{

public:

    /*
     * Getters
     */

    /** Get the number of jobs. */
    inline JobId number_of_jobs() const { return job_tools_.size(); }

    /** Get the number of tools. */
    inline ToolId number_of_tools() const { return tool_jobs_.size(); }

    /** Get the tools of a job. */
    inline const std::vector<ToolId>& tools(JobId job_id) const { return job_tools_[job_id]; }

    /** Get the jobs requiring a tool. */
    inline const std::vector<JobId>& jobs(ToolId tool_id) const { return tool_jobs_[tool_id]; }

    /** Get the magazine capacity. */
    inline ToolId magazine_capacity() const { return magazine_capacity_; }

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
                << "Number of jobs:     " << number_of_jobs() << std::endl
                << "Number of tools:    " << number_of_tools() << std::endl
                << "Magazine capacity:  " << magazine_capacity() << std::endl
                ;
        }

        if (verbosity_level >= 2) {
            os << std::endl
                << std::setw(12) << "Job"
                << std::setw(12) << "# tools"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "-------"
                << std::endl;
            for (JobId job_id = 0; job_id < number_of_jobs(); ++job_id) {
                os
                    << std::setw(12) << job_id
                    << std::setw(12) << tools(job_id).size()
                    << std::endl;
            }

            os << std::endl
                << std::setw(12) << "Tool"
                << std::setw(12) << "# jobs"
                << std::endl
                << std::setw(12) << "----"
                << std::setw(12) << "------"
                << std::endl;
            for (ToolId tool_id = 0; tool_id < number_of_tools(); ++tool_id) {
                os
                    << std::setw(12) << tool_id
                    << std::setw(12) << jobs(tool_id).size()
                    << std::endl;
            }
        }

        if (verbosity_level >= 3) {
            os << std::endl
                << std::setw(12) << "Job"
                << std::setw(12) << "Tool"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "----"
                << std::endl;
            for (JobId job_id = 0; job_id < number_of_jobs(); ++job_id) {
                for (ToolId tool_id: tools(job_id)) {
                    os
                        << std::setw(12) << job_id
                        << std::setw(12) << tool_id
                        << std::endl;
                }
            }
        }
    }

    /** Check a certificate. */
    std::pair<bool, ToolId> check(
            const std::string& certificate_path,
            std::ostream& os,
            int verbosity_level = 1) const
    {
        std::ifstream file(certificate_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");
        }

        std::vector<JobId> solution_jobs;
        std::vector<uint8_t> is_job_scheduled(number_of_jobs(), 0);
        JobPos number_of_duplicates = 0;
        JobId job_id = 0;
        JobPos job_pos = 0;
        // For each tool, the list of positions it is required.
        std::vector<std::vector<JobPos>> tools_positions(number_of_tools());
        while (file >> job_id) {

            // Check duplicates.
            if (is_job_scheduled[job_id]) {
                number_of_duplicates++;
                if (verbosity_level >= 2) {
                    os << "Job " << job_id
                        << " has already been scheduled." << std::endl;
                }
            }

            is_job_scheduled[job_id] = 1;
            solution_jobs.push_back(job_id);

            for (ToolId tool_id: tools(job_id))
                tools_positions[tool_id].push_back(job_pos);

            job_pos++;
        }
        for (ToolId tool_id = 0; tool_id < number_of_tools(); ++tool_id)
            std::reverse(tools_positions[tool_id].begin(), tools_positions[tool_id].end());

        if (verbosity_level >= 2) {
            os << std::endl << std::right
                << std::setw(12) << "Job"
                << std::setw(12) << "# switches"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "----------"
                << std::endl;
        }

        ToolId number_of_switches = 0;
        optimizationtools::IndexedBinaryHeap<JobPos> magazine(number_of_tools());
        for (JobId job_id: solution_jobs) {

            // Add the tools of the current job in the magasin.
            // Set the key to ensure that they remain there during the next
            // step.
            for (ToolId tool_id: tools(job_id)) {
                if (!magazine.contains(tool_id))
                    number_of_switches++;
                magazine.update_key(tool_id, 0);
            }

            // Remove tools from the magazine until the magazine magazine_capacity
            // constraint is satisfied.
            while (magazine.size() > magazine_capacity())
                magazine.pop();

            // Set the right key for the tools of the current job.
            for (ToolId tool_id: tools(job_id)) {
                tools_positions[tool_id].pop_back();
                // If the tool is not neaded anymore, remove it from the heap.
                if (tools_positions[tool_id].empty()) {
                    magazine.update_key(tool_id, -number_of_jobs());
                    magazine.pop();
                } else {
                    // Otherwise, the its right key value.
                    magazine.update_key(tool_id, -tools_positions[tool_id].back());
                }
            }

            if (verbosity_level >= 2) {
                os
                    << std::setw(12) << job_id
                    << std::setw(12) << number_of_switches
                    << std::endl;
            }
        }

        bool feasible
            = ((JobId)solution_jobs.size() == number_of_jobs())
            && (number_of_duplicates == 0);

        if (verbosity_level >= 2)
            os << std::endl;
        if (verbosity_level >= 1) {
            os
                << "Number of jobs:        " << solution_jobs.size() << " / " << number_of_jobs()  << std::endl
                << "Number of duplicates:  " << number_of_duplicates << std::endl
                << "Feasible:              " << feasible << std::endl
                << "Number of switches:    " << number_of_switches << std::endl
                ;
        }
        return {feasible, number_of_switches};
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
    std::vector<std::vector<ToolId>> job_tools_;

    /** Tools. */
    std::vector<std::vector<JobId>> tool_jobs_;

    /** Magazine capacity. */
    ToolId magazine_capacity_ = 1;

    friend class InstanceBuilder;
};

class InstanceBuilder
{

public:

    /** Constructor. */
    InstanceBuilder() { }

    /** Add a job. */
    JobId add_job()
    {
        instance_.job_tools_.push_back({});
        return instance_.job_tools_.size() - 1;
    }

    /** Add a tool. */
    JobId add_tool()
    {
        instance_.tool_jobs_.push_back({});
        return instance_.tool_jobs_.size() - 1;
    }

    /** Add a tool requirement for a job. */
    void add_tool_requirement(
            JobId job_id,
            ToolId tool_id)
    {
        instance_.job_tools_[job_id].push_back(tool_id);
        instance_.tool_jobs_[tool_id].push_back(job_id);
    }

    /** Set magazine capacity. */
    void set_magazine_capacity(ToolId magazine_capacity)
    {
        instance_.magazine_capacity_ = magazine_capacity;
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
        ToolId number_of_tools;
        ToolId magazine_capacity;
        file >> number_of_jobs >> number_of_tools >> magazine_capacity;
        for (JobId job_id = 0; job_id < number_of_jobs; ++job_id)
            add_job();
        for (ToolId tool_id = 0; tool_id < number_of_tools; ++tool_id)
            add_tool();
        set_magazine_capacity(magazine_capacity);

        int value;
        for (ToolId tool_id = 0; tool_id < number_of_tools; ++tool_id) {
            for (JobId job_id = 0; job_id < number_of_jobs; ++job_id) {
                file >> value;
                if (value)
                    add_tool_requirement(job_id, tool_id);
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
