/**
 * Identical parallel machine scheduling problem with family setup times, Total
 * weighted completion time.
 *
 * Input:
 * - m machines
 * - o families; for each family k = 1..o, a setup time sₖ
 * - n jobs; for each job j = 1..n
 *   - a processing time pⱼ
 *   - a weight wⱼ
 *   - a family fⱼ
 * Problem:
 * - find a schedule for each machine such that:
 *   - each job is scheduled exactly once
 *   - if a job j2 is processed on a machine immediately after a job j1 and
 *     f(j2) != f(j1), then a setup of s(f(j2)) units of time must be performed
 *     before starting processing j2.
 * Objective:
 * - minimize the total weighted completion time of the schedule.
 *
 */

#pragma once

#include "optimizationtools/containers/indexed_set.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>

namespace orproblems
{

namespace parallelschedulingwithfamilysetuptimestwct
{

using JobId = int64_t;
using MachineId = int64_t;
using FamilyId = int64_t;
using Time = int64_t;
using Weight = int64_t;

/**
 * Structure for a family.
 */
struct Family
{
    /** Setup time of the family. */
    Time setup_time;

    /** Jobs of the family. */
    std::vector<JobId> job_ids;
};

/**
 * Structure for a job.
 */
struct Job
{
    /** Processing-time of the job. */
    Time processing_time;

    /** Weight of the job. */
    Weight weight;

    /** Family of the job. */
    FamilyId family_id;
};

/**
 * Instance class for a 'parallelschedulingwithfamilysetuptimestwct' problem.
 */
class Instance
{

public:

    /*
     * Constructors and destructor
     */

    /** Constructor to build an instance manually. */
    Instance(
            MachineId number_of_machines,
            FamilyId number_of_familiess):
        number_of_machines_(number_of_machines),
        families_(number_of_familiess)
    {
    }

    /** Set the setup time of a family. */
    void set_setup_time(
            FamilyId family_id,
            Time setup_time)
    {
        families_[family_id].setup_time = setup_time;
    }

    /** Add a job. */
    void add_job(
            Time processing_time,
            Weight weight,
            FamilyId family_id)
    {
        JobId id = jobs_.size();
        Job job;
        job.processing_time = processing_time;
        job.weight = weight;
        job.family_id = family_id;
        jobs_.push_back(job);
        families_[family_id].job_ids.push_back(id);
    }

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
        if (format == "" || format == "default") {
            read_default(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    /*
     * Getters
     */

    /** Get the number of machines. */
    MachineId number_of_machines() const { return number_of_machines_; }

    /** Get the number of families. */
    FamilyId number_of_families() const { return families_.size(); }

    /** Get a family. */
    const Family& family(FamilyId family_id) const { return families_[family_id]; }

    /** Get the number of jobs. */
    JobId number_of_jobs() const { return jobs_.size(); }

    /** Get a job. */
    const Job& job(JobId job_id) const { return jobs_[job_id]; }

    /** Print the instance. */
    std::ostream& print(
            std::ostream& os,
            int verbose = 1) const
    {
        if (verbose >= 1) {
            os << "Number of machines:  " << number_of_machines() << std::endl;
            os << "Number of families:  " << number_of_families() << std::endl;
            os << "Number of jobs:      " << number_of_jobs() << std::endl;
        }

        if (verbose >= 2) {
            os << std::endl
                << std::setw(12) << "Family"
                << std::setw(12) << "Setup"
                << std::setw(12) << "# jobs"
                << std::endl
                << std::setw(12) << "------"
                << std::setw(12) << "-----"
                << std::setw(12) << "------"
                << std::endl;
            for (FamilyId family_id = 0;
                    family_id < number_of_families();
                    ++family_id) {
                const Family& family = this->family(family_id);
                os
                    << std::setw(12) << family_id
                    << std::setw(12) << family.setup_time
                    << std::setw(12) << family.job_ids.size()
                    << std::endl;
            }
        }

        if (verbose >= 2) {
            os << std::endl
                << std::setw(12) << "Job"
                << std::setw(12) << "Proc. time"
                << std::setw(12) << "Weight"
                << std::setw(12) << "Family"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "----------"
                << std::setw(12) << "------"
                << std::setw(12) << "------"
                << std::endl;
            for (JobId job_id = 0;
                    job_id < number_of_jobs();
                    ++job_id) {
                const Job& job = this->job(job_id);
                os
                    << std::setw(12) << job_id
                    << std::setw(12) << job.processing_time
                    << std::setw(12) << job.weight
                    << std::setw(12) << job.family_id
                    << std::endl;
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
                << std::setw(12) << "Time"
                << std::setw(12) << "TWCT"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "----"
                << std::setw(12) << "----"
                << std::endl;
        }

        JobId job_id_pred = 0;
        JobId job_id = -1;
        optimizationtools::IndexedSet jobs(number_of_jobs());
        JobId number_of_duplicates = 0;
        Time time = 0;
        Time total_weighted_completion_time = 0;
        while (file >> job_id) {
            const Job& job = this->job(job_id);

            // Check duplicates.
            if (jobs.contains(job_id)) {
                number_of_duplicates++;
                if (verbose >= 2) {
                    os << "Job " << job_id
                        << " has already been scheduled." << std::endl;
                }
            }
            jobs.add(job_id);

            if (job.family_id != this->job(job_id_pred).family_id)
                time += this->family(job.family_id).setup_time;
            time += job.processing_time;
            total_weighted_completion_time += job.weight * time;

            if (verbose >= 2) {
                os
                    << std::setw(12) << job_id
                    << std::setw(12) << time
                    << std::setw(12) << total_weighted_completion_time
                    << std::endl;
            }

            job_id_pred = job_id;
        }

        bool feasible
            = (jobs.size() == number_of_jobs())
            && (number_of_duplicates == 0);
        if (verbose >= 2)
            os << std::endl;
        if (verbose >= 1) {
            os
                << "Number of jobs:                  " << jobs.size() << " / " << number_of_jobs()  << std::endl
                << "Number of duplicates:            " << number_of_duplicates << std::endl
                << "Feasible:                        " << feasible << std::endl
                << "Total weighted completion time:  " << total_weighted_completion_time << std::endl
                ;
        }
        return {feasible, total_weighted_completion_time};
    }

private:

    /*
     * Private methods
     */

    /** Read an instance from a file in 'default' format. */
    void read_default(std::ifstream& file)
    {
        file >> number_of_machines_;

        FamilyId number_of_families = -1;

        file >> number_of_families;
        families_.resize(number_of_families);
        Time setup_time;
        for (FamilyId family_id = 0;
                family_id < number_of_families;
                ++family_id) {
            file >> setup_time;
            set_setup_time(family_id, setup_time);
        }

        JobId number_of_jobs = -1;
        file >> number_of_jobs;
        Time processing_time = -1;
        Weight weight = -1;
        FamilyId family_id = -1;
        for (JobId job_id = 0; job_id < number_of_jobs; ++job_id) {
            file
                >> processing_time
                >> weight
                >> family_id;
            add_job(processing_time,
                    weight,
                    family_id);
        }
    }

    /*
     * Private attributes
     */

    /** Number of machines. */
    MachineId number_of_machines_;

    /** Jobs. */
    std::vector<Job> jobs_;

    /** Families. */
    std::vector<Family> families_;

};

}

}
