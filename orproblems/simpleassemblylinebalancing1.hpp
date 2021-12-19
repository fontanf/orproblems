#pragma once

#include "optimizationtools/utils.hpp"
#include "optimizationtools/indexed_set.hpp"

#include <iostream>
#include <fstream>

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

namespace orproblems
{

namespace simpleassemblylinebalancing1
{

typedef int64_t JobId;
typedef int64_t JobPos;
typedef int64_t StationId;
typedef int64_t Time;

struct Job
{
    JobId id;
    Time processing_time;
    std::vector<JobId> predecessors;
    std::vector<JobId> successors;
};

class Instance
{

public:

    Instance() { }
    void add_job(Time p)
    {
        Job job;
        job.id = jobs_.size();
        job.processing_time = p;
        jobs_.push_back(job);
        processing_time_sum_ += p;
    }
    void add_predecessor(JobId j1, JobId j2)
    {
        assert(j1 >= 0);
        assert(j2 >= 0);
        assert(j1 < number_of_jobs());
        assert(j2 < number_of_jobs());
        jobs_[j1].predecessors.push_back(j2);
        jobs_[j2].successors.push_back(j1);
    }
    void set_cycle_time(Time cycle_time) { cycle_time_ = cycle_time; }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
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

    virtual ~Instance() { }

    inline JobId number_of_jobs() const { return jobs_.size(); }
    inline const Job& job(JobId j) const { return jobs_[j]; }
    inline Time cycle_time() const { return cycle_time_; }
    inline Time processing_time_sum() const { return processing_time_sum_; }

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
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");

        JobId n = number_of_jobs();
        JobPos s = -1;
        optimizationtools::IndexedSet jobs(n);
        JobPos duplicates = 0;
        JobPos number_of_precedence_violations = 0;
        StationId number_of_overloaded_stations = 0;
        StationId number_of_stations = 0;
        while (file >> s) {
            JobId j = -1;
            Time t = 0;
            number_of_stations++;
            if (verbose == 2)
                std::cout << "Station: " << number_of_stations - 1 << "; Jobs";
            for (JobPos j_pos = 0; j_pos < s; ++j_pos) {
                file >> j;
                // Check duplicates.
                if (jobs.contains(j)) {
                    duplicates++;
                    if (verbose == 2)
                        std::cout << std::endl << "Job " << j << " already scheduled." << std::endl;
                }
                // Check predecessors.
                for (JobId j_pred: job(j).predecessors) {
                    if (!jobs.contains(j_pred)) {
                        number_of_precedence_violations++;
                        if (verbose == 2)
                            std::cout << std::endl << "Job " << j << " depends on job "
                                << j_pred << " which has not been scheduled yet."
                                << std::endl;
                    }
                }
                if (verbose == 2)
                    std::cout << " " << j;
                jobs.add(j);
                t += job(j).processing_time;
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
            && (duplicates == 0)
            && (number_of_precedence_violations == 0)
            && (number_of_overloaded_stations == 0);
        if (verbose == 2)
            std::cout << "---" << std::endl;
        if (verbose >= 1) {
            std::cout << "Number of jobs:                   " << jobs.size() << " / " << n  << std::endl;
            std::cout << "Duplicates:                       " << duplicates << std::endl;
            std::cout << "Number of precedence violations:  " << number_of_precedence_violations << std::endl;
            std::cout << "Number of overloaded stations:    " << number_of_overloaded_stations << std::endl;
            std::cout << "Feasible:                         " << feasible << std::endl;
            std::cout << "Number of stations:               " << number_of_stations << std::endl;
        }
        return {feasible, number_of_stations};
    }

private:

    void read_scholl1993(std::ifstream& file)
    {
        JobId n = -1;
        file >> n;
        Time p = -1;
        for (JobId j = 0; j < n; ++j) {
            file >> p;
            add_job(p);
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

    void read_otto2013(std::ifstream& file)
    {
        std::string tmp;
        std::vector<std::string> line;
        JobId n = -1;
        JobId j_tmp = -1;
        double d_tmp = -1;
        while (getline(file, tmp)) {
            line = optimizationtools::split(tmp, ' ');
            if (line.size() == 0) {
            } else if (tmp.rfind("<number of tasks>", 0) == 0) {
                file >> n;
            } else if (tmp.rfind("<cycle time>", 0) == 0) {
                Time cycle_time = -1;
                file >> cycle_time;
                set_cycle_time(cycle_time);
            } else if (tmp.rfind("<order strength>", 0) == 0) {
                file >> d_tmp;
            } else if (tmp.rfind("<task times>", 0) == 0) {
                Time p = -1;
                for (JobId j = 0; j < n; ++j) {
                    file >> j_tmp >> p;
                    add_job(p);
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

    std::vector<Job> jobs_;
    Time cycle_time_ = 0;
    Time processing_time_sum_ = 0;

};

static inline std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "cycle time " << instance.cycle_time() << std::endl;
    os << "number of jobs " << instance.number_of_jobs() << std::endl;
    for (JobId j = 0; j < instance.number_of_jobs(); ++j) {
        os << "job " << j
            << " p " << instance.job(j).processing_time
            << " pred";
        for (JobId j2: instance.job(j).predecessors)
            os << " " << j2;
        os << std::endl;
    }
    return os;
}

}

}

