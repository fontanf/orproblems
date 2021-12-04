#pragma once

#include "optimizationtools/utils.hpp"
#include "optimizationtools/sorted_on_demand_array.hpp"
#include "optimizationtools/indexed_set.hpp"

/**
 * Single machine order acceptance and scheduling problem with
 * sequence-dependent setup times.
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

namespace orproblems
{

namespace orderacceptanceandscheduling
{

typedef int64_t JobId;
typedef int64_t JobPos;
typedef int64_t Time;
typedef double Weight;
typedef double Profit;

struct Job
{
    JobId id;
    Time release_date;
    Time due_date;
    Time deadline;
    Time processing_time;
    Weight weight;
    Profit profit;
};

class Instance
{

public:

    Instance(JobId n):
        jobs_(n),
        setup_times_(n, std::vector<Time>(n))
    {
        for (JobId j = 0; j < n; ++j)
            jobs_[j].id = j;
    }
    void set_job(
            JobId j,
            Time release_date,
            Time due_date,
            Time deadline,
            Time processing_time,
            Weight weight,
            Profit profit)
    {
        jobs_[j].release_date = release_date;
        jobs_[j].due_date = due_date;
        jobs_[j].deadline = deadline;
        jobs_[j].processing_time = processing_time;
        jobs_[j].weight = weight;
        jobs_[j].profit = profit;
    }
    void set_setup_time(JobId j1, JobId j2, Time setup_time)
    {
        setup_times_[j1][j2] = setup_time;
    }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        if (format == "" || format == "cesaret2012") {
            read_cesaret2012(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    virtual ~Instance() { }

    inline JobId number_of_jobs() const { return jobs_.size(); }
    inline const Job& job(JobId j) const { return jobs_[j]; }
    inline Time setup_time(JobId j1, JobId j2) const { return setup_times_[j1][j2]; }

    std::pair<bool, Time> check(
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
        JobId j = -1;
        JobId j_prec = 0;
        optimizationtools::IndexedSet jobs(n);
        JobPos duplicates = 0;
        JobPos number_of_deadline_violations = 0;
        Time current_time = 0;
        Profit profit = 0;
        Weight total_weighted_tardiness = 0;
        while (file >> j) {
            if (jobs.contains(j)) {
                duplicates++;
                if (verbose == 2)
                    std::cout << "Job " << j << " is already scheduled." << std::endl;
            }
            jobs.add(j);
            current_time = std::max(current_time, job(j).release_date)
                + setup_time(j_prec, j) + job(j).processing_time;
            profit += job(j).profit;
            if (current_time > job(j).due_date)
                total_weighted_tardiness += (current_time - job(j).due_date);
            if (current_time > job(j).deadline) {
                number_of_deadline_violations++;
                if (verbose == 2)
                    std::cout << "Job " << j << " ends after its deadline: "
                        << current_time << " / " << job(j).deadline << "." << std::endl;
            }
            if (verbose == 2)
                std::cout << "Job: " << j
                    << "; Time: " << current_time
                    << "; Profit: " << profit
                    << "; Total weighted tardiness: " << total_weighted_tardiness
                    << std::endl;
        }

        bool feasible
            = (duplicates == 0)
            && (number_of_deadline_violations == 0);
        if (verbose == 2)
            std::cout << "---" << std::endl;
        if (verbose >= 1) {
            std::cout << "Job number:                 " << jobs.size() << " / " << n  << std::endl;
            std::cout << "Duplicates:                 " << duplicates << std::endl;
            std::cout << "Deadline violation number:  " << duplicates << std::endl;
            std::cout << "Feasible:                   " << feasible << std::endl;
            std::cout << "Profit:                     " << profit << std::endl;
            std::cout << "Total weighted tardiness:   " << total_weighted_tardiness << std::endl;
            std::cout << "Objective:                  " << profit - total_weighted_tardiness << std::endl;
        }
        return {feasible, profit - total_weighted_tardiness};
    }

private:

    void read_cesaret2012(std::ifstream& file)
    {
        std::string tmp;
        std::vector<std::string> line;

        getline(file, tmp);
        line = optimizationtools::split(tmp, ',');
        JobId n = line.size();
        jobs_.resize(n);
        setup_times_.resize(n, std::vector<Time>(n));
        for (JobId j = 0; j < n; ++j)
            jobs_[j].release_date = std::stol(line[j]);
        getline(file, tmp);
        line = optimizationtools::split(tmp, ',');
        for (JobId j = 0; j < n; ++j)
            jobs_[j].processing_time = std::stol(line[j]);
        getline(file, tmp);
        line = optimizationtools::split(tmp, ',');
        for (JobId j = 0; j < n; ++j)
            jobs_[j].due_date = std::stol(line[j]);
        getline(file, tmp);
        line = optimizationtools::split(tmp, ',');
        for (JobId j = 0; j < n; ++j)
            jobs_[j].deadline = std::stol(line[j]);
        getline(file, tmp);
        line = optimizationtools::split(tmp, ',');
        for (JobId j = 0; j < n; ++j)
            jobs_[j].profit = std::stod(line[j]);
        getline(file, tmp);
        line = optimizationtools::split(tmp, ',');
        for (JobId j = 0; j < n; ++j)
            jobs_[j].weight = std::stod(line[j]);
        for (JobId j1 = 0; j1 < n; ++j1) {
            getline(file, tmp);
            line = optimizationtools::split(tmp, ',');
            for (JobId j2 = 0; j2 < n; ++j2)
                setup_times_[j1][j2] = std::stol(line[j2]);
        }
    }

    std::vector<Job> jobs_;
    std::vector<std::vector<Time>> setup_times_;

};

static inline std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "number of jobs: " << instance.number_of_jobs() << std::endl;
    for (JobId j = 0; j < instance.number_of_jobs(); ++j)
        os << "job: " << j
            << "; processing time: " << instance.job(j).processing_time
            << "; release date: " << instance.job(j).release_date
            << "; due date: " << instance.job(j).due_date
            << "; deadline: " << instance.job(j).deadline
            << "; weight: " << instance.job(j).weight
            << "; profit: " << instance.job(j).profit
            << std::endl;
    for (JobId j1 = 0; j1 <= instance.number_of_jobs(); ++j1) {
        os << "job " << j1 << ":";
        for (JobId j2 = 0; j2 < instance.number_of_jobs(); ++j2)
            os << " " << instance.setup_time(j1, j2);
        os << std::endl;
    }
    return os;
}

}

}

