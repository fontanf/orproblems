/**
 * Single machine scheduling problem with sequence-dependent setup times, Total
 * weighted tardiness.
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

typedef int64_t JobId;
typedef int64_t JobPos;
typedef int64_t Time;
typedef double Weight;

struct Job
{
    Time processing_time = 0;
    Time due_date = 0;
    Weight weight = 1;
};

class Instance
{

public:

    Instance(JobId n):
        jobs_(n),
        setup_times_(n + 1, std::vector<Time>(n, -1))
    {
        for (JobId j = 0; j < n; ++j)
            setup_times_[j][j] = 0;
    }
    void set_processing_time(JobId j, Time processing_time) { jobs_[j].processing_time = processing_time; }
    void set_due_date(JobId j, Time due_date) { jobs_[j].due_date = due_date; }
    void set_weight(JobId j, Weight weight)
    {
        if (jobs_[j].weight == 0)
            number_of_zero_weight_jobs_--;
        jobs_[j].weight = weight;
        if (jobs_[j].weight == 0)
            number_of_zero_weight_jobs_++;
    }
    void set_setup_time(JobId j1, JobId j2, Time d)
    {
        if (j1 == -1)
            j1 = number_of_jobs();
        setup_times_[j1][j2] = d;
    }

    Instance(std::string instance_path, std::string format = "")
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

    virtual ~Instance() { }

    inline JobId number_of_jobs() const { return jobs_.size(); }
    inline JobId number_of_zero_weight_jobs() const { return number_of_zero_weight_jobs_; }
    inline const Job& job(JobId j) const { return jobs_[j]; }
    inline Time setup_time(JobId j1, JobId j2) const { return setup_times_[j1][j2]; }

    std::ostream& print(
            std::ostream& os,
            int verbose = 1) const
    {
        if (verbose >= 1) {
            os << "Number of jobs:  " << number_of_jobs() << std::endl;
        }
        if (verbose >= 2) {
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
            for (JobId j = 0; j < number_of_jobs(); ++j) {
                os << std::setw(12) << j
                    << std::setw(12) << job(j).processing_time
                    << std::setw(12) << job(j).due_date
                    << std::setw(12) << job(j).weight
                    << std::endl;
            }
            os << std::endl
                << "Setup times:" << std::endl;
            for (JobId j1 = 0; j1 <= number_of_jobs(); ++j1) {
                for (JobId j2 = 0; j2 < number_of_jobs(); ++j2)
                    os << " " << setup_time(j1, j2);
                os << std::endl;
            }
        }
        return os;
    }

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

        JobId n = number_of_jobs();
        JobId j = -1;
        JobId j_prec = n;
        optimizationtools::IndexedSet jobs(n);
        JobPos duplicates = 0;
        Time current_time = 0;
        Weight total_weighted_tardiness = 0;
        while (file >> j) {
            if (jobs.contains(j)) {
                duplicates++;
                if (verbose >= 2)
                    std::cout << "Job " << j << " is already scheduled." << std::endl;
            }
            jobs.add(j);
            current_time += setup_time(j_prec, j);
            current_time += job(j).processing_time;
            if (current_time > job(j).due_date)
                total_weighted_tardiness
                    += job(j).weight
                    * (current_time - job(j).due_date);
            if (verbose >= 2) {
                os
                    << std::setw(12) << j
                    << std::setw(12) << job(j).processing_time
                    << std::setw(12) << job(j).due_date
                    << std::setw(12) << job(j).weight
                    << std::setw(12) << setup_time(j_prec, j)
                    << std::setw(12) << current_time
                    << std::setw(12) << total_weighted_tardiness
                    << std::endl;
            }
            j_prec = j;
        }

        bool feasible
            = (jobs.size() == n)
            && (duplicates == 0);
        if (verbose >= 2)
            std::cout << std::endl;
        if (verbose >= 1) {
            std::cout << "Number of jobs:            " << jobs.size() << " / " << n  << std::endl;
            std::cout << "Number of duplicates:      " << duplicates << std::endl;
            std::cout << "Feasible:                  " << feasible << std::endl;
            std::cout << "Total weighted tardiness:  " << total_weighted_tardiness << std::endl;
        }
        return {feasible, total_weighted_tardiness};
    }

private:

    void read_cicirello2005(std::ifstream& file)
    {
        std::string tmp;
        JobId n = -1;
        file >> tmp >> tmp >> tmp;
        file >> tmp >> tmp >> n;

        jobs_ = std::vector<Job>(n);
        setup_times_ = std::vector<std::vector<Time>>(n + 1, std::vector<Time>(n, -1));
        for (JobId j = 0; j < n; ++j)
            setup_times_[j][j] = 0;

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
        for (JobId j = 0; j < n; ++j) {
            file >> p;
            set_processing_time(j, p);
        }

        file >> tmp;
        Weight w = -1;
        for (JobId j = 0; j < n; ++j) {
            file >> w;
            set_weight(j, w);
        }

        file >> tmp;
        Time d = -1;
        for (JobId j = 0; j < n; ++j) {
            file >> d;
            set_due_date(j, d);
        }

        file >> tmp >> tmp;
        Time st = -1;
        for (JobId j1 = -1; j1 < n; ++j1) {
            for (JobId j2 = 0; j2 < n; ++j2) {
                if (j1 == j2)
                    continue;
                file >> tmp >> tmp >> st;
                set_setup_time(j1, j2, st);
            }
        }
    }

    std::vector<Job> jobs_;
    std::vector<std::vector<Time>> setup_times_;
    JobPos number_of_zero_weight_jobs_ = 0;

};

}

}

