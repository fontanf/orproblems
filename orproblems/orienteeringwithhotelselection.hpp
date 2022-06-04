/**
 * Orienteering problem with hotel selection.
 *
 * Input:
 * - n + H locations:
 *   - 1 starting hotel
 *   - 1 ending hotel
 *   - H extra hotels
 *   - n - 2 potential locations to visit; for each potential location
 *     j = H+2..n+H to visit, a profit pⱼ
 * - An (n+H)×(n+H) symmetric matrix containing the travel times between each
 *   pair of locations
 * - A maximum duration tₘₐₓ
 * - A number of trips D; for each trip d = 1..D, a maximum duration td
 * Problem:
 * - Find a list of trips such that:
 *   - Each potential location to visit is visited at most once (an extra hotel
 *     can be visited more than once).
 *   - The first trip starts at the starting hotel (location 1).
 *   - The last trip ends at the ending hotel (location 2).
 *   - Each trip d = 1..D-1 ends at the same location where trip d + 1 starts.
 *     This location must be an extra hotel (location within 3..3+H).
 *   - The duration of each trip d = 1..D is smaller than Td.
 *   - The sum of the duration of all trips is smaller than tₘₐₓ.
 * Objective:
 * - Maximize the total profit of the visited locations
 *
 */

#pragma once

#include "optimizationtools/containers/indexed_set.hpp"
#include "optimizationtools/utils/utils.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>

namespace orproblems
{

namespace orienteeringwithhotelselection
{

using LocationId = int64_t;
using LocationPos = int64_t;
using TripId = int64_t;
using Time = double;
using Length = double;
using Profit = double;

struct Location
{
    Length x;
    Length y;
    Profit profit;
};

class Instance
{

public:

    Instance(
            LocationPos number_of_locations,
            TripId number_of_trips):
        locations_(number_of_locations),
        trip_maximum_duration_(number_of_trips, std::numeric_limits<Time>::max()),
        travel_times_(number_of_locations, std::vector<Time>(number_of_locations, std::numeric_limits<Time>::max()))
    { }

    void set_number_of_extra_hotels(
            LocationPos number_of_extra_hotels)
    {
        number_of_extra_hotels_ = number_of_extra_hotels;
    }

    void set_maximum_duration(
            Time maximum_duration)
    {
        maximum_duration_ = maximum_duration;
    }

    void set_trip_maximum_duration(
            TripId trip_id,
            Time maximum_duration)
    {
        trip_maximum_duration_[trip_id] = maximum_duration;
    }

    void set_travel_time(
            LocationId j1,
            LocationId j2,
            Time d)
    {
        travel_times_[j1][j2] = d;
        travel_times_[j2][j1] = d;
    }

    Instance(
            std::string instance_path,
            std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        }
        if (format == "" || format == "divsalar2013") {
            read_divsalar2013(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    virtual ~Instance() { }

    inline LocationId number_of_locations() const { return locations_.size(); }
    inline LocationId number_of_trips() const { return trip_maximum_duration_.size(); }
    inline LocationId number_of_extra_hotels() const { return number_of_extra_hotels_; }
    inline const Location& location(LocationId j) const { return locations_[j]; }
    inline Time maximum_duration() const { return maximum_duration_; }
    inline Time maximum_duration(TripId trip_id) const { return trip_maximum_duration_[trip_id]; }
    inline Time travel_time(LocationId j1, LocationId j2) const { return travel_times_[j1][j2]; }

    std::ostream& print(
            std::ostream& os,
            int verbose = 1) const
    {
        if (verbose > 0) {
            os << "Number of locations:     " << number_of_locations() << std::endl;
            os << "Number of trips:         " << number_of_trips() << std::endl;
            os << "Number of extra hotels:  " << number_of_extra_hotels() << std::endl;
        }
        if (verbose > 1) {
            os << std::endl
                << std::setw(12) << "Location"
                << std::setw(12) << "Profit"
                << "    Travel times"
                << std::endl
                << std::setw(12) << "--------"
                << std::setw(12) << "------"
                << "    ------------"
                << std::endl;
            for (LocationId j1 = 0; j1 < number_of_locations(); ++j1) {
                os << std::setw(12) << j1
                    << std::setw(12) << location(j1).profit
                    << "   ";
                for (LocationId j2 = 0; j2 < number_of_locations(); ++j2)
                    os << " " << travel_time(j1, j2);
                os << std::endl;
            }
        }
        return os;
    }

    std::pair<bool, Profit> check(
            std::string certificate_path,
            std::ostream& os,
            int verbose = 1) const
    {
        // The certificate must contain neither the starting nor the ending
        // hotel.

        std::ifstream file(certificate_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");
        }

        if (verbose >= 2) {
            os << std::endl << std::right
                << std::setw(12) << "Location"
                << std::setw(12) << "Profit"
                << std::setw(12) << "Travel time"
                << std::setw(12) << "Trip time"
                << std::setw(12) << "Total time"
                << std::setw(12) << "Tot. profit"
                << std::endl
                << std::setw(12) << "--------"
                << std::setw(12) << "------"
                << std::setw(12) << "-----------"
                << std::setw(12) << "---------"
                << std::setw(12) << "----------"
                << std::setw(12) << "-----------"
                << std::endl;
        }

        LocationId n = number_of_locations();
        LocationId j = -1;
        LocationId j_pred = 0;
        optimizationtools::IndexedSet locations(n);
        LocationPos number_of_duplicates = 0;
        LocationPos number_of_trip_duration_violations = 0;
        TripId trip_id = 0;
        Time trip_duration = 0;
        Time total_duration = 0;
        Profit profit = 0;
        while (file >> j) {
            if (j == 0 || j == 1) {
                locations.add(j);
                if (verbose >= 2)
                    os << "Location " << j << " must not appear in the certificate." << std::endl;
            }
            trip_duration += travel_time(j_pred, j);
            total_duration += travel_time(j_pred, j);
            profit += location(j).profit;
            if (verbose >= 2) {
                os
                    << std::setw(12) << j
                    << std::setw(12) << location(j).profit
                    << std::setw(12) << travel_time(j_pred, j)
                    << std::setw(12) << trip_duration
                    << std::setw(12) << total_duration
                    << std::setw(12) << profit
                    << std::endl;
            }
            // Start a new trip.
            if (j < number_of_extra_hotels() + 2) {
                if (verbose >= 2) {
                    os << "Trip " << trip_id
                        << "; duration: " << trip_duration
                        << " / " << maximum_duration(trip_id) << "."
                        << std::endl;
                }
                if (trip_duration > maximum_duration(trip_id)) {
                    if (verbose >= 2)
                        os << "Trip " << trip_id << " is too long." << std::endl;
                    number_of_trip_duration_violations++;
                }
                trip_id++;
                trip_duration = 0;
            } else {
                if (locations.contains(j)) {
                    number_of_duplicates++;
                    if (verbose >= 2)
                        os << "Location " << j << " has already been visited." << std::endl;
                }
                locations.add(j);
            }
            j_pred = j;
        }
        // Finish last trip.
        j = 1;
        trip_duration += travel_time(j_pred, j);
        total_duration += travel_time(j_pred, j);
        if (verbose >= 2) {
            os
                << std::setw(12) << j
                << std::setw(12) << location(j).profit
                << std::setw(12) << travel_time(j_pred, j)
                << std::setw(12) << trip_duration
                << std::setw(12) << total_duration
                << std::setw(12) << profit
                << std::endl;
        }
        os << "Trip " << trip_id
            << "; duration: " << trip_duration
            << " / " << maximum_duration(trip_id) << "."
            << std::endl;
        if (trip_duration > maximum_duration(trip_id)) {
            os << "Trip " << trip_id << " is too long." << std::endl;
            number_of_trip_duration_violations++;
        }
        trip_id++;

        bool feasible
            = (total_duration <= maximum_duration())
            && (number_of_trip_duration_violations == 0)
            && (!locations.contains(0))
            && (!locations.contains(1))
            && (trip_id == number_of_trips())
            && (number_of_duplicates == 0);
        if (verbose >= 2)
            os << std::endl;
        if (verbose >= 1) {
            os << "Number of locations:                 " << locations.size() - 2 << " / " << n - 2 - number_of_extra_hotels() << std::endl;
            os << "Number of duplicates:                " << number_of_duplicates << std::endl;
            os << "Number of trips:                     " << trip_id << " / " << number_of_trips() << std::endl;
            os << "Number of trip duration violations:  " << number_of_trip_duration_violations;
            os << "Total duraction:                     " << total_duration << " / " << maximum_duration() << std::endl;
            os << "Feasible:                            " << feasible << std::endl;
            os << "Profit:                              " << profit << std::endl;
        }
        return {feasible, profit};
    }

private:

    void read_divsalar2013(
            std::ifstream& file)
    {
        std::string tmp;
        LocationPos n = -1;
        TripId number_of_trips = -1;
        file >> n >> number_of_extra_hotels_ >> number_of_trips;
        n += 2;
        locations_ = std::vector<Location>(n);
        trip_maximum_duration_ = std::vector<Time>(
                number_of_trips, std::numeric_limits<Time>::max());
        std::vector<std::vector<Time>> travel_times_tmp(
                n, std::vector<Time>(n, -1));

        file >> maximum_duration_;
        for (TripId trip_id = 0; trip_id < number_of_trips; ++trip_id)
            file >> trip_maximum_duration_[trip_id];

        for (LocationId j = 0; j < n; ++j)
            file >> locations_[j].x >> locations_[j].y >> locations_[j].profit;

        for (LocationId j1 = 0; j1 < n; ++j1) {
            for (LocationId j2 = j1 + 1; j2 < n; ++j2) {
                double xd = location(j2).x - location(j1).x;
                double yd = location(j2).y - location(j1).y;
                Time d = std::sqrt(xd * xd + yd * yd);
                set_travel_time(j1, j2, d);
            }
        }
    }

    std::vector<Location> locations_;
    LocationPos number_of_extra_hotels_ = 0;
    std::vector<Time> trip_maximum_duration_;
    std::vector<std::vector<Time>> travel_times_;
    Time maximum_duration_ = 0;

};

}

}

