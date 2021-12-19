#pragma once

#include "optimizationtools/utils.hpp"
#include "optimizationtools/indexed_set.hpp"

#include <iostream>
#include <fstream>

/**
 * Travelling Repairman Problem.
 *
 * Input:
 * - n locations
 * - an n×n matrix s containing the travel times between each pair of locations
 * Problem:
 * - Find a tour starting and ending at location 0 such that:
 *   - every other location is visited exactly once
 * Objective:
 * - Minimize the sum of arrival times (except for the return at location 0)
 *
 */

namespace orproblems
{

namespace travellingrepairman
{

typedef int64_t LocationId;
typedef int64_t LocationPos;
typedef double Time;

struct Location
{
    double x;
    double y;
};

class Instance
{

public:

    Instance(LocationId n):
        locations_(n),
        travel_times_(n, std::vector<Time>(n, -1))
    {
        for (LocationId j = 0; j < n; ++j)
            travel_times_[j][j] = 0;
    }
    void set_travel_time(LocationId j1, LocationId j2, Time travel_time)
    {
        travel_times_[j1][j2] = travel_time;
    }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        if (format == "" || format == "salehipour2011") {
            read_salehipour2011(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    virtual ~Instance() { }

    inline LocationId number_of_locations() const { return travel_times_.size(); }
    inline Time travel_time(LocationId j1, LocationId j2) const { return travel_times_[j1][j2]; }

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

        LocationId n = number_of_locations();
        LocationId j = -1;
        LocationId j_prec = 0;
        optimizationtools::IndexedSet locations(n);
        LocationPos duplicates = 0;
        Time current_time = 0;
        Time total_completion_time = 0;
        while (file >> j) {
            if (locations.contains(j)) {
                duplicates++;
                if (verbose == 2)
                    std::cout << "Location " << j << " is already scheduled." << std::endl;
            }
            locations.add(j);
            current_time += travel_time(j_prec, j);
            total_completion_time += current_time;
            if (verbose == 2)
                std::cout << "Location: " << j
                    << "; Time: " << current_time
                    << "; Total completion time: " << total_completion_time
                    << std::endl;
        }

        bool feasible
            = (locations.size() == n)
            && (duplicates == 0);
        if (verbose == 2)
            std::cout << "---" << std::endl;
        if (verbose >= 1) {
            std::cout << "Location number:           " << locations.size() << " / " << n  << std::endl;
            std::cout << "Duplicates:                " << duplicates << std::endl;
            std::cout << "Feasible:                  " << feasible << std::endl;
            std::cout << "Total completion time:     " << total_completion_time << std::endl;
        }
        return {feasible, total_completion_time};
    }

private:

    void read_salehipour2011(std::ifstream& file)
    {
        std::string tmp;
        LocationId n = -1;
        file
            >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp
            >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp
            >> n
            >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp
            ;
        locations_.resize(n);
        for (LocationId j = 0; j < n; ++j)
            file >> tmp >> locations_[j].x >> locations_[j].y;
        for (LocationId j1 = 0; j1 < n; ++j1) {
            for (LocationId j2 = 0; j2 < n; ++j2) {
                Time dx = locations_[j1].x - locations_[j2].x;
                Time dy = locations_[j1].y - locations_[j2].y;
                Time dxy = std::round(std::sqrt(dx * dx + dy * dy));
                set_travel_time(j1, j2, dxy);
            }
        }
    }

    std::vector<Location> locations_;
    std::vector<std::vector<Time>> travel_times_;

};

static inline std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "number of locations: " << instance.number_of_locations() << std::endl;
    for (LocationId j1 = 0; j1 < instance.number_of_locations(); ++j1) {
        os << "location " << j1 << ":";
        for (LocationId j2 = 0; j2 < instance.number_of_locations(); ++j2)
            os << " " << instance.travel_time(j1, j2);
        os << std::endl;
    }
    return os;
}

}

}

