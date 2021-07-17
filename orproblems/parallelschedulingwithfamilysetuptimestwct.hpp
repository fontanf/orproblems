#pragma once

/**
 * Identical parallel machine scheduling problem with family setup times, Total
 * weighted completion time.
 *
 * Input:
 * - m machines
 * - o families with setup time sₖ (k = 1..o)
 * - n jobs with processing time pⱼ, weight wⱼ and a family fⱼ (j = 1..n)
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

#include "optimizationtools/indexed_set.hpp"

#include <fstream>
#include <iostream>

namespace orproblems
{

namespace parallelschedulingwithfamilysetuptimestwct
{

typedef int64_t JobId;
typedef int64_t MachineId;
typedef int64_t FamilyId;
typedef int64_t Time;
typedef int64_t Weight;

struct Family
{
    FamilyId id;
    Time setup_time;
    std::vector<JobId> jobs;
};

struct Job
{
    JobId id;
    Time processing_time;
    Weight weight;
    FamilyId family;
};

class Instance
{

public:

    Instance(MachineId machine_number, FamilyId family_number):
        machine_number_(machine_number),
        families_(family_number)
    {
        for (FamilyId k = 0; k < family_number; ++k)
            families_[k].id = k;
    }
    void set_setup_time(FamilyId k, Time setup_time) { families_[k].setup_time = setup_time; }
    void add_job(
            Time processing_time,
            Weight weight,
            FamilyId family)
    {
        JobId id = jobs_.size();
        Job job;
        job.id = id;
        job.processing_time = processing_time;
        job.weight = weight;
        job.family = family;
        jobs_.push_back(job);
        families_[family].jobs.push_back(id);
    }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            std::cerr << "\033[31m" << "ERROR, unable to open file \"" << instance_path << "\"" << "\033[0m" << std::endl;
            assert(false);
            return;
        }
        if (format == "" || format == "default") {
            read_default(file);
        } else {
            std::cerr << "\033[31m" << "ERROR, unknown instance format \"" << format << "\"" << "\033[0m" << std::endl;
        }
        file.close();
    }

    virtual ~Instance() { }

    MachineId machine_number() const { return machine_number_; }
    FamilyId family_number() const { return families_.size(); }
    JobId job_number() const { return jobs_.size(); }
    const Job& job(JobId j) const { return jobs_[j]; }
    const Family& family(FamilyId k) const { return families_[k]; }

private:

    void read_default(std::ifstream& file)
    {
        file >> machine_number_;

        FamilyId o = -1;

        file >> o;
        families_.resize(o);
        for (FamilyId k = 0; k < o; ++k)
            families_[k].id = k;
        Time s;
        for (FamilyId k = 0; k < o; ++k) {
            file >> s;
            set_setup_time(k, s);
        }

        JobId n = -1;
        file >> n;
        Time p = -1;
        Weight w = -1;
        FamilyId k = -1;
        for (JobId j = 0; j < n; ++j) {
            file >> p >> w >> k;
            add_job(p, w, k);
        }
    }

    MachineId machine_number_;
    std::vector<Job> jobs_;
    std::vector<Family> families_;

};

static std::ostream& operator<<(std::ostream &os, const Instance& instance)
{
    os << "machine number " << instance.machine_number() << std::endl;
    os << "job number " << instance.job_number() << std::endl;
    os << "family number " << instance.family_number() << std::endl;
    for (JobId j = 0; j < instance.job_number(); ++j)
        os << "job " << j
            << " p " << instance.job(j).processing_time
            << " w " << instance.job(j).weight
            << " f " << instance.job(j).family
            << std::endl;
    for (FamilyId k = 0; k < instance.family_number(); ++k) {
        os << "family " << k
            << " s " << instance.family(k).setup_time
            << " j";
        for (JobId j: instance.family(k).jobs)
            os << " " << j;
        os << std::endl;
    }
    return os;
}

}

}
