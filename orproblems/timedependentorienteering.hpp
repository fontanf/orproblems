#pragma once

#include "optimizationtools/containers/indexed_set.hpp"
#include "optimizationtools/utils/utils.hpp"

#include <iostream>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

/**
 * Time-dependent orienteering problem.
 *
 * Input:
 * - n locations; for each location j = 1..n, a profit pⱼ
 * - a function t(j₁, j₂, s) which returns the time to travel from location j₁
 *   to location j₂ starting at time s
 * - a time limit tₘₐₓ
 * Problem:
 * - Find a path starting at location 1 and ending at location n such that:
 *   - each location is visited at most once
 *   - the arrival at location n is before tₘₐₓ
 * Objective:
 * - Maximize the total profit of the visited locations
 *
 */

namespace orproblems
{

namespace timedependentorienteering
{

using LocationId = int64_t;
using LocationPos = int64_t;
using ArcCategory = int64_t;
using TimePeriod = int64_t;
using Time = double;
using Length = double;
using Profit = double;

struct Location
{
    Length x;
    Length y;
    Profit profit;
};

struct Arc
{
    ArcCategory category;
    Length length;
};

class Instance
{

public:

    Instance(LocationId n):
        locations_(n),
        arcs_(n, std::vector<Arc>(n)) { }
    void set_maximum_duration(Time maximum_duration) { maximum_duration_ = maximum_duration; }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        }
        if (format == "" || format == "verbeeck2014") {
            read_verbeeck2014(file, instance_path);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    virtual ~Instance() { }

    inline LocationId number_of_locations() const { return locations_.size(); }
    inline const Location& location(LocationId j) const { return locations_[j]; }
    inline Time maximum_duration() const { return maximum_duration_; }
    inline Time arrival_time(LocationId j1, LocationId j2, Time start) const
    {
        Time current_time = start;
        Length remaining_length = arcs_[j1][j2].length;
        ArcCategory arc_category = arcs_[j1][j2].category;
        TimePeriod time_period =
            (current_time < 9 - 7)? 0:
            (current_time < 17 - 7)? 1:
            (current_time < 19 - 7)? 2:
            3;
        for (;;) {
            Time time_period_end =
                (time_period == 0)? 9 - 7:
                (time_period == 1)? 17 - 7:
                (time_period == 2)? 19 - 7:
                std::numeric_limits<Time>::max();
            double speed = speed_matrix_[arc_category][time_period];
            Time at = current_time + remaining_length / speed;
            if (at <= time_period_end) {
                //std::cout << "j1 " << j1
                //    << " j2 " << j2
                //    << " x1 " << locations_[j1].x
                //    << " y1 " << locations_[j1].y
                //    << " x2 " << locations_[j2].x
                //    << " y2 " << locations_[j2].y
                //    << " length " << arcs_[j1][j2].length
                //    << " cat " << arc_category
                //    << " start " << start
                //    << " dur " << at - start
                //    << " arrival " << at << " / " << time_period_end
                //    << std::endl;
                return at;
            }
            remaining_length -= (time_period_end - current_time) * speed;
            //std::cout << "remaining_length " << remaining_length << std::endl;
            current_time = time_period_end;
            time_period++;
        }
        return -1;
    }

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
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");
        }

        LocationId n = number_of_locations();
        LocationId j = -1;
        LocationId j_prec = 0;
        optimizationtools::IndexedSet locations(n);
        locations.add(0);
        locations.add(n - 1);
        LocationPos number_of_duplicates = 0;
        Time current_time = 0;
        Profit profit = location(0).profit;
        while (file >> j) {
            if (locations.contains(j)) {
                number_of_duplicates++;
                if (verbose == 2)
                    std::cout << "Location " << j << " is already scheduled." << std::endl;
            }
            locations.add(j);
            current_time = arrival_time(j_prec, j, current_time);
            profit += location(j).profit;
            if (verbose == 2)
                std::cout << "Location: " << j
                    << "; Time: " << current_time
                    << "; Profit: " << profit << " (" << location(j).profit << ")"
                    << std::endl;
            j_prec = j;
        }
        current_time = arrival_time(j_prec, n - 1, current_time);
        profit += location(n - 1).profit;

        bool feasible
            = (current_time <= maximum_duration())
            && (number_of_duplicates == 0);
        if (verbose == 2)
            std::cout << "---" << std::endl;
        if (verbose >= 1) {
            std::cout << "Number of locations:       " << locations.size() << " / " << n  << std::endl;
            std::cout << "Number of duplicates:      " << number_of_duplicates << std::endl;
            std::cout << "Duraction:                 " << current_time << " / " << maximum_duration() << std::endl;
            std::cout << "Feasible:                  " << feasible << std::endl;
            std::cout << "Profit:                    " << profit << std::endl;
        }
        return {feasible, profit};
    }

private:

    void read_verbeeck2014(
            std::ifstream& file,
            std::string instance_path)
    {
        std::string tmp;
        LocationId n = -1;
        file
            >> tmp >> n
            >> tmp >> tmp
            >> tmp >> maximum_duration_
            ;
        locations_ = std::vector<Location>(n);
        for (LocationId j = 0; j < n; ++j)
            file >> locations_[j].x >> locations_[j].y >> locations_[j].profit;
        arcs_ = std::vector<std::vector<Arc>>(n, std::vector<Arc>(n));
        for (LocationId j1 = 0; j1 < n; ++j1) {
            for (LocationId j2 = 0; j2 < n; ++j2) {
                Length dx = locations_[j1].x - locations_[j2].x;
                Length dy = locations_[j1].y - locations_[j2].y;
                Length dxy = std::sqrt(dx * dx + dy * dy);
                dxy /= 5;
                arcs_[j1][j2].length = dxy;
            }
        }

        // Read speed matrix.
        auto speed_matrix_path = boost::filesystem::path(instance_path)
            .parent_path().parent_path().parent_path() /= "speedmatrix.txt";
        std::ifstream speed_matrix_file(speed_matrix_path.string());
        speed_matrix_ = std::vector<std::vector<double>>(
                5, std::vector<double>(4, 0.0));
        for (ArcCategory arc_category = 0; arc_category < 5; ++arc_category)
            for (TimePeriod time_period = 0; time_period < 4; ++time_period)
                speed_matrix_file >> speed_matrix_[arc_category][time_period];

        // Read arc category matrix.
        boost::filesystem::directory_iterator it_end;
        auto arc_category_directory = boost::filesystem::path(instance_path)
            .parent_path().parent_path();
        const boost::regex filter("arc_cat_.*\\.txt");
        for (boost::filesystem::directory_iterator it(arc_category_directory); it != it_end; ++it) {
            if (!boost::filesystem::is_regular_file(it->status()))
                continue;
            boost::smatch what;
            // For V2:
            //if(!boost::regex_match(it->leaf(), what, filter))
            //    continue;
            // For V3:
            if (!boost::regex_match(it->path().filename().string(), what, filter))
                continue;
            // File matches, store it
            std::ifstream arc_category_file(it->path().string());
            for (LocationId location_id_1 = 0; location_id_1 < number_of_locations(); ++location_id_1)
                for (LocationId location_id_2 = 0; location_id_2 < number_of_locations(); ++location_id_2)
                    arc_category_file >> arcs_[location_id_1][location_id_2].category;
        }
    }

    std::vector<Location> locations_;
    std::vector<std::vector<Arc>> arcs_;
    std::vector<std::vector<double>> speed_matrix_;
    Time maximum_duration_ = 0;

};

static inline std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "number of locations: " << instance.number_of_locations() << std::endl;
    for (LocationId j = 0; j < instance.number_of_locations(); ++j) {
        os << "location " << j
            << " profit " << instance.location(j).profit;
        os << std::endl;
    }
    return os;
}

}

}

