#pragma once

#include "optimizationtools/utils.hpp"
#include "optimizationtools/sorted_on_demand_array.hpp"
#include "optimizationtools/indexed_set.hpp"

/**
 * Single machine scheduling problem with sequence-dependent setup times, Total
 * weighted Tardiness.
 *
 * Input:
 * - n jobs with (j = 1..n)
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
 * Tree search:
 * - forward branching
 *
 */

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
            zero_weight_job_number_--;
        jobs_[j].weight = weight;
        if (jobs_[j].weight == 0)
            zero_weight_job_number_++;
    }
    void set_setup_time(JobId j1, JobId j2, Time d)
    {
        if (j1 == -1)
            j1 = job_number();
        setup_times_[j1][j2] = d;
    }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            std::cerr << "\033[31m" << "ERROR, unable to open file \"" << instance_path << "\"" << "\033[0m" << std::endl;
            assert(false);
            return;
        }
        if (format == "" || format == "cicirello2005") {
            read_cicirello2005(file);
        } else {
            std::cerr << "\033[31m" << "ERROR, unknown instance format \"" << format << "\"" << "\033[0m" << std::endl;
        }
        file.close();
    }

    virtual ~Instance() { }

    inline JobId job_number() const { return jobs_.size(); }
    inline JobId zero_weight_job_number() const { return zero_weight_job_number_; }
    inline const Job& job(JobId j) const { return jobs_[j]; }
    inline Time setup_time(JobId j1, JobId j2) const { return setup_times_[j1][j2]; }

    std::pair<bool, Time> check(std::string certificate_path)
    {
        std::ifstream file(certificate_path);
        if (!file.good()) {
            std::cerr << "\033[31m" << "ERROR, unable to open file \"" << certificate_path << "\"" << "\033[0m" << std::endl;
            assert(false);
            return {false, 0};
        }

        JobId n = job_number();
        JobId j = -1;
        JobId j_prec = n;
        optimizationtools::IndexedSet jobs(n);
        JobPos duplicates = 0;
        Time current_time = 0;
        Weight total_weighted_tardiness = 0;
        while (file >> j) {
            if (jobs.contains(j)) {
                duplicates++;
                std::cout << "Job " << j << " is already scheduled." << std::endl;
            }
            jobs.add(j);
            current_time += setup_time(j_prec, j);
            current_time += job(j).processing_time;
            if (current_time > job(j).due_date)
                total_weighted_tardiness
                    += job(j).weight
                    * (current_time - job(j).due_date);
            std::cout << "Job: " << j
                << "; Due date: " << job(j).due_date
                << "; Weight: " << job(j).weight
                << "; Setup time: " << setup_time(j_prec, j)
                << "; Processing time: " << job(j).processing_time
                << "; Time: " << current_time
                << "; Total weighted tardiness: " << total_weighted_tardiness
                << std::endl;
            j_prec = j;
        }
        bool feasible
            = (jobs.size() == n)
            && (duplicates == 0);

        std::cout << "---" << std::endl;
        std::cout << "Job number:                " << jobs.size() << " / " << n  << std::endl;
        std::cout << "Duplicates:                " << duplicates << std::endl;
        std::cout << "Feasible:                  " << feasible << std::endl;
        std::cout << "Total weighted tardiness:  " << total_weighted_tardiness << std::endl;
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
    JobPos zero_weight_job_number_ = 0;

};

std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "job number: " << instance.job_number() << std::endl;
    for (JobId j = 0; j < instance.job_number(); ++j)
        os << "job: " << j
            << "; processing time: " << instance.job(j).processing_time
            << "; due date: " << instance.job(j).due_date
            << "; weight: " << instance.job(j).weight
            << std::endl;
    for (JobId j1 = 0; j1 <= instance.job_number(); ++j1) {
        os << "job " << j1 << ":";
        for (JobId j2 = 0; j2 < instance.job_number(); ++j2)
            os << " " << instance.setup_time(j1, j2);
        os << std::endl;
    }
    return os;
}

}

}

