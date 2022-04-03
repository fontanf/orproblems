#pragma once

/**
 * Star Observation Scheduling Problem.
 *
 * Input:
 * - m nights
 * - n targets; for each target j = 1..n, a profit wⱼ
 * - a list of possible observations. An observation is associated to a night i
 *   and a target j and has a time-window [rᵢⱼ, dᵢⱼ] and a duration pᵢⱼ such
 *   that 2 pⱼᵢ ≥ dⱼᵢ - rⱼᵢ
 * Problem:
 * - select a list of observations and their starting dates sᵢⱼ such that:
 *   - a target is observed at most once
 *   - observations do not overlap
 *   - starting dates satisfy the time-windows, i.e. rᵢⱼ <= sᵢⱼ and
 *     sᵢⱼ + pᵢⱼ <= dᵢⱼ
 * Objective:
 * - maximize the overall profit of the selected observations
 *
 */

#include "optimizationtools/containers/indexed_set.hpp"

#include <fstream>
#include <iostream>

namespace orproblems
{

namespace starobservationscheduling
{

typedef int64_t TargetId;
typedef int64_t NightId;
typedef int64_t Profit;
typedef int64_t Time;

struct Observable
{
    NightId i;
    TargetId j;
    Time r;
    Time d;
    Time p; // Observation time.
    Profit profit;
};

class Instance
{

public:

    Instance(NightId m, TargetId n): observables_(m), profits_(n) {  }
    void add_observable(const Observable& o) { observables_[o.i].push_back(o); }
    void set_profit(TargetId j, Profit w) { profits_[j] = w; profit_sum_ += w; }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");

        if (format == "" || format == "catusse2016") {
            read_catusse2016(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    virtual ~Instance() { }

    NightId number_of_nights() const { return observables_.size(); }
    TargetId number_of_targets() const { return profits_.size(); }
    TargetId number_of_observables(NightId i) const { return observables_[i].size(); }
    const Observable& observable(NightId i, TargetId j_pos) const { return observables_[i][j_pos]; }
    Profit profit(TargetId j) const { return profits_[j]; }
    Profit total_profit() const { return profit_sum_; }

private:

    void read_catusse2016(std::ifstream& file)
    {
        TargetId n;
        NightId m;
        std::string null;
        std::string line;

        std::getline(file, line);
        std::istringstream iss_m(line);
        iss_m >> null >> null >> m;
        observables_ = std::vector<std::vector<Observable>>(m);

        std::getline(file, line);
        std::istringstream iss_n(line);
        iss_n >> null >> null >> n;
        profits_ = std::vector<Profit>(n);

        Profit w;
        for (TargetId j = 0; j < n; ++j) {
            std::getline(file, line);
            std::istringstream iss(line);
            iss >> null >> null >> null >> null >> w;
            set_profit(j, w);

            for (NightId i = 0; i < m; ++i) {
                std::getline(file, line);
                std::istringstream iss(line);
                iss >> null >> null >> null;
                if (iss.eof())
                    continue;
                Observable o;
                o.j = j;
                o.i = i;
                iss >> o.p >> null >> o.r >> null >> null >> null >> o.d;
                add_observable(o);
            }
        }
    }

    std::vector<std::vector<Observable>> observables_;
    std::vector<Profit> profits_;
    Profit profit_sum_ = 0;

};

}

}
