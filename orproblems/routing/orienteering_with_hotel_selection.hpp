/**
 * Orienteering problem with hotel selection
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

#include <iostream>
#include <fstream>
#include <iomanip>

namespace orproblems
{
namespace orienteering_with_hotel_selection
{

using LocationId = int64_t;
using LocationPos = int64_t;
using TripId = int64_t;
using Time = double;
using Length = double;
using Profit = double;

/**
 * Structure for a location.
 */
struct Location
{
    /** x-coordinate of the location. */
    Length x;

    /** y-coordinate of the location. */
    Length y;

    /** Profit of the location. */
    Profit profit;
};


/**
 * Instance class for a 'orienteering_with_hotel_selection' problem.
 */
class Instance
{

public:

    /*
     * Getters
     */

    /** Get the number of locations. */
    inline LocationId number_of_locations() const { return locations_.size(); }

    /** Get a location. */
    inline const Location& location(LocationId location_id) const { return locations_[location_id]; }

    /** Get the number of trips. */
    inline LocationId number_of_trips() const { return trip_maximum_duration_.size(); }

    /** Get the number of extra hotels. */
    inline LocationId number_of_extra_hotels() const { return number_of_extra_hotels_; }

    /** Get the maximum duration. */
    inline Time maximum_duration() const { return maximum_duration_; }

    /** Get the maximum duration of a given trip. */
    inline Time maximum_duration(TripId trip_id) const { return trip_maximum_duration_[trip_id]; }

    /** Get the travel time between two locations. */
    inline Time travel_time(
            LocationId location_id_1,
            LocationId location_id_2) const
    {
        return travel_times_[location_id_1][location_id_2];
    }

    /*
     * Outputs
     */

    /** Print the instance. */
    void format(
            std::ostream& os,
            int verbosity_level = 1) const
    {
        if (verbosity_level >= 1) {
            os
                << "Number of locations:     " << number_of_locations() << std::endl
                << "Number of trips:         " << number_of_trips() << std::endl
                << "Number of extra hotels:  " << number_of_extra_hotels() << std::endl
                ;
        }

        if (verbosity_level >= 2) {
            os << std::endl
                << std::setw(12) << "Location"
                << std::setw(12) << "Profit"
                << std::endl
                << std::setw(12) << "--------"
                << std::setw(12) << "------"
                << std::endl;
            for (LocationId location_id = 0;
                    location_id < number_of_locations();
                    ++location_id) {
                os
                    << std::setw(12) << location_id
                    << std::setw(12) << location(location_id).profit
                    << std::endl;
            }
        }

        if (verbosity_level >= 3) {
            os << std::endl
                << std::setw(12) << "Loc. 1"
                << std::setw(12) << "Loc. 2"
                << std::setw(12) << "Tr. time"
                << std::endl
                << std::setw(12) << "------"
                << std::setw(12) << "------"
                << std::setw(12) << "--------"
                << std::endl;
            for (LocationId location_id_1 = 0;
                    location_id_1 < number_of_locations();
                    ++location_id_1) {
                for (LocationId location_id_2 = location_id_1 + 1;
                        location_id_2 < number_of_locations();
                        ++location_id_2) {
                    os
                        << std::setw(12) << location_id_1
                        << std::setw(12) << location_id_2
                        << std::setw(12) << travel_time(location_id_1, location_id_2)
                        << std::endl;
                }
            }
        }
    }

    /** Check a certificate. */
    std::pair<bool, Profit> check(
            const std::string& certificate_path,
            std::ostream& os,
            int verbosity_level = 1) const
    {
        std::ifstream file(certificate_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");
        }

        // The certificate must contain neither the starting nor the ending
        // hotel.

        if (verbosity_level >= 2) {
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

        LocationId location_id = -1;
        LocationId location_id_prev = 0;
        optimizationtools::IndexedSet locations(number_of_locations());
        LocationPos number_of_duplicates = 0;
        LocationPos number_of_trip_duration_violations = 0;
        TripId trip_id = 0;
        Time trip_duration = 0;
        Time total_duration = 0;
        Profit profit = 0;
        while (file >> location_id) {
            if (location_id == 0 || location_id == 1) {
                locations.add(location_id);
                if (verbosity_level >= 2)
                    os << "Location " << location_id
                        << " must not appear in the certificate."
                        << std::endl;
            }

            trip_duration += travel_time(location_id_prev, location_id);
            total_duration += travel_time(location_id_prev, location_id);
            profit += location(location_id).profit;

            if (verbosity_level >= 2) {
                os
                    << std::setw(12) << location_id
                    << std::setw(12) << location(location_id).profit
                    << std::setw(12) << travel_time(location_id_prev, location_id)
                    << std::setw(12) << trip_duration
                    << std::setw(12) << total_duration
                    << std::setw(12) << profit
                    << std::endl;
            }

            // Start a new trip.
            if (location_id < number_of_extra_hotels() + 2) {
                // Check the maximum duration of the trip.
                if (verbosity_level >= 2) {
                    os << "Trip " << trip_id
                        << "; duration: " << trip_duration
                        << " / " << maximum_duration(trip_id) << "."
                        << std::endl;
                }

                // Check the maximum duration.
                if (trip_duration > maximum_duration(trip_id)) {
                    if (verbosity_level >= 2)
                        os << "Trip " << trip_id << " is too long." << std::endl;
                    number_of_trip_duration_violations++;
                }

                trip_id++;
                trip_duration = 0;
            } else {
                // Check duplicates.
                if (locations.contains(location_id)) {
                    number_of_duplicates++;
                    if (verbosity_level >= 2)
                        os << "Location " << location_id
                            << " has already been visited." << std::endl;
                }
                locations.add(location_id);
            }
            location_id_prev = location_id;
        }
        // Finish last trip.
        location_id = 1;
        trip_duration += travel_time(location_id_prev, location_id);
        total_duration += travel_time(location_id_prev, location_id);
        if (verbosity_level >= 2) {
            os
                << std::setw(12) << location_id
                << std::setw(12) << location(location_id).profit
                << std::setw(12) << travel_time(location_id_prev, location_id)
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

        if (verbosity_level >= 2)
            os << std::endl;
        if (verbosity_level >= 1) {
            os
                << "Number of locations:                 " << locations.size() - 2 << " / " << number_of_locations() - 2 - number_of_extra_hotels() << std::endl
                << "Number of duplicates:                " << number_of_duplicates << std::endl
                << "Number of trips:                     " << trip_id << " / " << number_of_trips() << std::endl
                << "Number of trip duration violations:  " << number_of_trip_duration_violations
                << "Total duraction:                     " << total_duration << " / " << maximum_duration() << std::endl
                << "Feasible:                            " << feasible << std::endl
                << "Profit:                              " << profit << std::endl
                ;
        }
        return {feasible, profit};
    }

private:

    /*
     * Private methods
     */

    /** Constructor to build an instance manually. */
    Instance() { }

    /*
     * Private attributes
     */

    /** Locations. */
    std::vector<Location> locations_;

    /** Number of extra hotels. */
    LocationPos number_of_extra_hotels_ = 0;

    /** Maximum duration of the trips. */
    std::vector<Time> trip_maximum_duration_;

    /** Travel times. */
    std::vector<std::vector<Time>> travel_times_;

    /** Maximum duration. */
    Time maximum_duration_ = 0;

    friend class InstanceBuilder;
};

class InstanceBuilder
{

public:

    /** Constructor. */
    InstanceBuilder() { }

    /**
     * Set the number of locations.
     *
     * This method resets the travel times.
     */
    void set_number_of_locations(LocationId number_of_locations)
    {
        instance_.locations_ = std::vector<Location>(number_of_locations),
        instance_.travel_times_ = std::vector<std::vector<Time>>(
                number_of_locations,
                std::vector<Time>(number_of_locations, -1));
    }

    /** Set the number of extra hotels. */
    void set_number_of_extra_hotels(
            LocationPos number_of_extra_hotels)
    {
        instance_.number_of_extra_hotels_ = number_of_extra_hotels;
    }

    /** Set the maximum duration. */
    void set_maximum_duration(
            Time maximum_duration)
    {
        instance_.maximum_duration_ = maximum_duration;
    }

    /** Set the maximum duration of a trip. */
    void add_trip(
            Time maximum_duration)
    {
        instance_.trip_maximum_duration_.push_back(maximum_duration);
    }

    /** Set the profit of a location. */
    void set_location_profit(
            LocationId location_id,
            Profit profit)
    {
        instance_.locations_[location_id].profit = profit;
    }

    /** Set the coordinates of a location. */
    void set_location_coordinates(
            LocationId location_id,
            double x,
            double y)
    {
        instance_.locations_[location_id].x = x;
        instance_.locations_[location_id].y = y;
    }

    /** Set the travel time between two locations. */
    void set_travel_time(
            LocationId location_id_1,
            LocationId location_id_2,
            Time travel_time)
    {
        instance_.travel_times_[location_id_1][location_id_2] = travel_time;
        instance_.travel_times_[location_id_2][location_id_1] = travel_time;
    }

    /** Build an instance from a file. */
    void read(
            const std::string& instance_path,
            const std::string& format = "")
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

    /*
     * Build
     */

    /** Build the instance. */
    Instance build()
    {
        return std::move(instance_);
    }

private:

    /*
     * Private methods
     */

    /** Read an instance from a file in 'divsalar2013' format. */
    void read_divsalar2013(
            std::ifstream& file)
    {
        LocationPos number_of_locations = -1;
        TripId number_of_trips = -1;
        LocationId number_of_extra_hotels = -1;
        file >> number_of_locations >> number_of_extra_hotels >> number_of_trips;
        number_of_locations += 2;
        set_number_of_locations(number_of_locations);
        set_number_of_extra_hotels(number_of_extra_hotels);

        Time maximum_duration = -1;
        file >> maximum_duration;
        set_maximum_duration(maximum_duration);
        for (TripId trip_id = 0; trip_id < number_of_trips; ++trip_id) {
            file >> maximum_duration;
            add_trip(maximum_duration);
        }

        Length x = -1;
        Length y = -1;
        Profit profit = -1;
        for (LocationId location_id = 0;
                location_id < number_of_locations;
                ++location_id) {
            file >> x >> y >> profit;
            set_location_coordinates(location_id, x, y);
            set_location_profit(location_id, profit);
        }

        for (LocationId location_id_1 = 0;
                location_id_1 < number_of_locations;
                ++location_id_1) {
            for (LocationId location_id_2 = location_id_1 + 1;
                    location_id_2 < number_of_locations;
                    ++location_id_2) {
                double xd = instance_.location(location_id_2).x - instance_.location(location_id_1).x;
                double yd = instance_.location(location_id_2).y - instance_.location(location_id_1).y;
                Time travel_time = std::sqrt(xd * xd + yd * yd);
                set_travel_time(location_id_1, location_id_2, travel_time);
            }
        }
    }

    /*
     * Private attributes
     */

    /** Instance. */
    Instance instance_;

};

}
}
