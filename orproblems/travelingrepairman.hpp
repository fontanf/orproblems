/**
 * Traveling Repairman Problem.
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

#pragma once

#include "optimizationtools/utils/utils.hpp"
#include "optimizationtools/containers/indexed_set.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>

namespace orproblems
{

namespace travelingrepairman
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
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        }
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

    std::ostream& print(
            std::ostream& os,
            int verbose = 1) const
    {
        if (verbose >= 1) {
            os << "Number of locations:  " << number_of_locations() << std::endl;
        }
        if (verbose >= 2) {
            os << std::endl
                << std::setw(12) << "Location"
                << "    Travel times"
                << std::endl
                << std::setw(12) << "---------"
                << "    ------------"
                << std::endl;
            for (LocationId j1 = 0; j1 < number_of_locations(); ++j1) {
                os << std::setw(12) << j1
                    << "   ";
                for (LocationId j2 = 0; j2 < number_of_locations(); ++j2)
                    os << " " << travel_time(j1, j2);
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
                << std::setw(12) << "Location"
                << std::setw(12) << "Travel time"
                << std::setw(12) << "Time"
                << std::setw(12) << "TCT"
                << std::endl
                << std::setw(12) << "--------"
                << std::setw(12) << "-----------"
                << std::setw(12) << "----"
                << std::setw(12) << "---"
                << std::endl;
        }

        LocationId n = number_of_locations();
        LocationId j = -1;
        LocationId j_prec = 0;
        optimizationtools::IndexedSet locations(n);
        locations.add(0);
        LocationPos number_of_duplicates = 0;
        Time current_time = 0;
        Time total_completion_time = 0;
        while (file >> j) {
            if (locations.contains(j)) {
                number_of_duplicates++;
                if (verbose >= 2)
                    os << "Location " << j << " is already scheduled." << std::endl;
            }
            locations.add(j);
            current_time += travel_time(j_prec, j);
            total_completion_time += current_time;
            if (verbose >= 2) {
                os
                    << std::setw(12) << j
                    << std::setw(12) << travel_time(j_prec, j)
                    << std::setw(12) << current_time
                    << std::setw(12) << total_completion_time
                    << std::endl;
            }
            j_prec = j;
        }

        bool feasible
            = (locations.size() == n)
            && (number_of_duplicates == 0);
        if (verbose >= 2)
            os << std::endl;
        if (verbose >= 1) {
            std::cout << "Number of locations:       " << locations.size() << " / " << n  << std::endl;
            std::cout << "Number of duplicates:      " << number_of_duplicates << std::endl;
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
        locations_ = std::vector<Location>(n + 1);
        travel_times_ = std::vector<std::vector<Time>>(
                n + 1, std::vector<Time>(n + 1, -1));
        for (LocationId j = 0; j < n + 1; ++j)
            file >> tmp >> locations_[j].x >> locations_[j].y;
        for (LocationId j1 = 0; j1 < n + 1; ++j1) {
            for (LocationId j2 = 0; j2 < n + 1; ++j2) {
                Time dx = locations_[j1].x - locations_[j2].x;
                Time dy = locations_[j1].y - locations_[j2].y;
                Time dxy = std::floor(std::sqrt(dx * dx + dy * dy));
                set_travel_time(j1, j2, dxy);
            }
        }
    }

    std::vector<Location> locations_;
    std::vector<std::vector<Time>> travel_times_;

};

}

}

