/**
 * Simple Assembly Line Balancing Problem of Type 1.
 *
 * Input:
 * - n jobs; for each job j = 1..n, a processing time pⱼ
 * - a cycle time c (station capacity)
 * - a directed acyclic graph G such that each node corresponds to a job
 * Problem:
 * - Find an assignment of jobs to stations such that:
 *   - each job is assigned to exactly one station
 *   - the sum of the processing times of the jobs assigned to each station
 *     does not exceed the cycle time
 *   - if there exists an arc from j₁ to j₂ in G, then j₁ must not be assigned
 *     to a station located after the station assigned to j₂
 * Objective:
 * - Minimize the number of stations
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

namespace simpleassemblylinebalancing1
{

using JobId = int64_t;
using JobPos = int64_t;
using StationId = int64_t;
using Time = int64_t;

/**
 * Structure for a job.
 */
struct Job
{
    /** Procesing-time of the job. */
    Time processing_time;

    /** Predecessors of the job. */
    std::vector<JobId> predecessors;

    /** Successors of the job. */
    std::vector<JobId> successors;
};

/**
 * Instance class for a 'simpleassemblylinebalancing1' problem.
 */
class Instance
{

public:


    /*
     * Constructors and destructor
     */

    /** Constructor to build an instance manually. */
    Instance() { }

    /** Add a job. */
    void add_job(Time p)
    {
        Job job;
        job.processing_time = p;
        jobs_.push_back(job);
        processing_time_sum_ += p;
    }

    /**
     * Add a precedence constraint between two jobs.
     *
     * 'job_id_2' preceeds 'job_id_1'.
     */
    void add_predecessor(
            JobId job_id_1,
            JobId job_id_2)
    {
        jobs_[job_id_1].predecessors.push_back(job_id_2);
        jobs_[job_id_2].successors.push_back(job_id_1);
        number_of_precedences_++;
    }

    /** Set the cycle time. */
    void set_cycle_time(Time cycle_time) { cycle_time_ = cycle_time; }

    /** Build an instance from a file. */
    Instance(
            std::string instance_path,
            std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        }
        if (format == "" || format == "scholl1993") {
            read_scholl1993(file);
        } else if (format == "otto2013") {
            read_otto2013(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    /*
     * Getters
     */

    /** Get the number of jobs. */
    inline JobId number_of_jobs() const { return jobs_.size(); }

    /** Get a job. */
    inline const Job& job(JobId job_id) const { return jobs_[job_id]; }

    /** Get the cycle time. */
    inline Time cycle_time() const { return cycle_time_; }

    /** Get the sum of all processing times. */
    inline Time processing_time_sum() const { return processing_time_sum_; }

    /** Print the instance. */
    std::ostream& print(
            std::ostream& os,
            int verbose = 1) const
    {
        if (verbose >= 1) {
            os
                << "Number of jobs:             " << number_of_jobs() << std::endl
                << "Cycle time:                 " << cycle_time() << std::endl
                << "Processing time sum:        " << processing_time_sum() << std::endl
                << "Processing time ratio:      " << (double)processing_time_sum() / cycle_time() << std::endl
                << "Average # of predecessors:  " << (double)number_of_precedences_ / number_of_jobs() << std::endl
            ;
        }

        if (verbose >= 2) {
            os << std::endl
                << std::setw(12) << "Job"
                << std::setw(12) << "Proc. time"
                << std::setw(12) << "# of pred."
                << std::setw(12) << "# of succ."
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "----------"
                << std::setw(12) << "----------"
                << std::setw(12) << "----------"
                << std::endl;
            for (JobId job_id = 0;
                    job_id < number_of_jobs();
                    ++job_id) {
                const Job& job = this->job(job_id);
                os
                    << std::setw(12) << job_id
                    << std::setw(12) << job.processing_time
                    << std::setw(12) << job.predecessors.size()
                    << std::setw(12) << job.successors.size()
                    << std::endl;
            }
        }

        if (verbose >= 3) {
            os << std::endl
                << std::setw(12) << "Job"
                << std::setw(12) << "Pred."
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "-----"
                << std::endl;
            for (JobId job_id = 0;
                    job_id < number_of_jobs();
                    ++job_id) {
                const Job& job = this->job(job_id);
                for (JobId job_id_pred: job.predecessors) {
                    os
                        << std::setw(12) << job_id
                        << std::setw(12) << job_id_pred
                        << std::endl;
                }
            }
        }

        return os;
    }

    /** Check a certificate. */
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

        if (verbose >= 2) {
            os << std::endl
                << std::setw(12) << "Job"
                << std::setw(12) << "Station"
                << std::setw(12) << "Time"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "-------"
                << std::setw(12) << "----"
                << std::endl;
        }

        JobPos station_number_of_jobs = -1;
        optimizationtools::IndexedSet jobs(number_of_jobs());
        JobPos number_of_duplicates = 0;
        JobPos number_of_precedence_violations = 0;
        StationId number_of_overloaded_stations = 0;
        StationId number_of_stations = 0;
        while (file >> station_number_of_jobs) {
            JobId job_id = -1;
            Time time = 0;
            number_of_stations++;
            for (JobPos job_pos = 0; job_pos < station_number_of_jobs; ++job_pos) {
                file >> job_id;

                // Check duplicates.
                if (jobs.contains(job_id)) {
                    number_of_duplicates++;
                    if (verbose >= 2) {
                        os << "Job " << job_id
                            << " has already been scheduled." << std::endl;
                    }
                }
                jobs.add(job_id);

                // Check predecessors.
                for (JobId job_id_pred: job(job_id).predecessors) {
                    if (!jobs.contains(job_id_pred)) {
                        number_of_precedence_violations++;
                        if (verbose >= 2) {
                            std::cout << "Job " << job_id
                                << " depends on job " << job_id_pred
                                << " which has not been scheduled yet."
                                << std::endl;
                        }
                    }
                }

                time += job(job_id).processing_time;

                if (verbose >= 2) {
                    os
                        << std::setw(12) << number_of_stations - 1
                        << std::setw(12) << job_id
                        << std::setw(12) << time
                        << std::endl;
                }
            }

            if (time > cycle_time()) {
                number_of_overloaded_stations++;
                if (verbose >= 2)
                    os << "Station " << number_of_stations - 1
                        << " is overloaded."
                        << std::endl;
            }
        }

        bool feasible
            = (jobs.size() == number_of_jobs())
            && (number_of_duplicates == 0)
            && (number_of_precedence_violations == 0)
            && (number_of_overloaded_stations == 0);
        if (verbose >= 2)
            os << std::endl;
        if (verbose >= 1) {
            os
                << "Number of jobs:                   " << jobs.size() << " / " << number_of_jobs() << std::endl
                << "Number of duplicates:             " << number_of_duplicates << std::endl
                << "Number of precedence violations:  " << number_of_precedence_violations << std::endl
                << "Number of overloaded stations:    " << number_of_overloaded_stations << std::endl
                << "Feasible:                         " << feasible << std::endl
                << "Number of stations:               " << number_of_stations << std::endl
                ;
        }
        return {feasible, number_of_stations};
    }

    std::pair<bool, StationId> check(
            std::string certificate_path,
            int verbose = 1) const
    {
        // Initial display.
        if (verbose >= 1) {
            std::cout
                << "Checker" << std::endl
                << "-------" << std::endl;
        }

        std::ifstream file(certificate_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");
        }

        JobId n = number_of_jobs();
        JobPos s = -1;
        optimizationtools::IndexedSet jobs(n);
        JobPos number_of_duplicates = 0;
        JobPos number_of_precedence_violations = 0;
        StationId number_of_overloaded_stations = 0;
        StationId number_of_stations = 0;
        while (file >> s) {
            JobId job_id = -1;
            Time t = 0;
            number_of_stations++;
            if (verbose == 2)
                std::cout << "Station: " << number_of_stations - 1 << "; Jobs";
            for (JobPos j_pos = 0; j_pos < s; ++j_pos) {
                file >> job_id;

                // Check duplicates.
                if (jobs.contains(job_id)) {
                    number_of_duplicates++;
                    if (verbose >= 2)
                        std::cout << "Job " << job_id
                            << " has already been scheduled." << std::endl;
                }
                jobs.add(job_id);

                // Check predecessors.
                for (JobId j_pred: job(job_id).predecessors) {
                    if (!jobs.contains(j_pred)) {
                        number_of_precedence_violations++;
                        if (verbose == 2)
                            std::cout << std::endl << "Job " << job_id << " depends on job "
                                << j_pred << " which has not been scheduled yet."
                                << std::endl;
                    }
                }
                if (verbose == 2)
                    std::cout << " " << job_id;
                t += job(job_id).processing_time;
            }
            if (verbose == 2)
                std::cout << "; Cycle time: " << t << " / " << cycle_time() << std::endl;
            if (t > cycle_time()) {
                number_of_overloaded_stations++;
                if (verbose == 2)
                    std::cout << "Station " << number_of_stations - 1 << " is overloaded." << std::endl;
            }
        }

        bool feasible
            = (jobs.size() == n)
            && (number_of_duplicates == 0)
            && (number_of_precedence_violations == 0)
            && (number_of_overloaded_stations == 0);
        if (verbose == 2)
            std::cout << "---" << std::endl;
        if (verbose >= 1) {
            std::cout << "Number of jobs:                   " << jobs.size() << " / " << n  << std::endl;
            std::cout << "Number of duplicates:             " << number_of_duplicates << std::endl;
            std::cout << "Number of precedence violations:  " << number_of_precedence_violations << std::endl;
            std::cout << "Number of overloaded stations:    " << number_of_overloaded_stations << std::endl;
            std::cout << "Feasible:                         " << feasible << std::endl;
            std::cout << "Number of stations:               " << number_of_stations << std::endl;
        }
        return {feasible, number_of_stations};
    }

private:

    /*
     * Private methods
     */

    /** Read an instance from a file in 'scholl1993' format. */
    void read_scholl1993(std::ifstream& file)
    {
        JobId number_of_jobs = -1;
        file >> number_of_jobs;
        Time processing_time = -1;
        for (JobId job_id = 0; job_id < number_of_jobs; ++job_id) {
            file >> processing_time;
            add_job(processing_time);
        }

        Time cycle_time = -1;
        file >> cycle_time;
        set_cycle_time(cycle_time);

        std::string tmp;
        std::vector<std::string> line;
        getline(file, tmp);
        for (;;) {
            getline(file, tmp);
            line = optimizationtools::split(tmp, ',');
            if (std::stol(line[0]) == -1)
                break;
            add_predecessor(std::stol(line[1]) - 1, std::stol(line[0]) - 1);
        }
    }

    /** Read an instance from a file in 'otto2013' format. */
    void read_otto2013(std::ifstream& file)
    {
        std::string tmp;
        std::vector<std::string> line;
        JobId number_of_jobs = -1;
        JobId job_id_tmp = -1;
        double d_tmp = -1;
        while (getline(file, tmp)) {
            line = optimizationtools::split(tmp, ' ');
            if (line.size() == 0) {
            } else if (tmp.rfind("<number of tasks>", 0) == 0) {
                file >> number_of_jobs;
            } else if (tmp.rfind("<cycle time>", 0) == 0) {
                Time cycle_time = -1;
                file >> cycle_time;
                set_cycle_time(cycle_time);
            } else if (tmp.rfind("<order strength>", 0) == 0) {
                file >> d_tmp;
            } else if (tmp.rfind("<task times>", 0) == 0) {
                Time processing_time = -1;
                for (JobId job_id = 0; job_id < number_of_jobs; ++job_id) {
                    file >> job_id_tmp >> processing_time;
                    add_job(processing_time);
                }
            } else if (tmp.rfind("<precedence relations>", 0) == 0) {
                for (;;) {
                    getline(file, tmp);
                    if (tmp.size() <= 1)
                        break;
                    line = optimizationtools::split(tmp, ',');
                    add_predecessor(std::stol(line[1]) - 1, std::stol(line[0]) - 1);
                }
            } else if (tmp.rfind("<end>", 0) == 0) {
                break;
            }
        }
    }

    /*
     * Private attributes
     */

    /** Jobs. */
    std::vector<Job> jobs_;

    /** Cycle time. */
    Time cycle_time_ = 0;

    /*
     * Computed attributes
     */

    /** Sum of all processing times. */
    Time processing_time_sum_ = 0;

    /** Number of precedences. */
    JobPos number_of_precedences_ = 0;

};

}

}

