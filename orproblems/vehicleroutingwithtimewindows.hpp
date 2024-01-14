/**
 * Vehicle routing problem with time windows
 *
 * Input:
 * - m vehicles of capacity Q
 * - 1 depot
 * - n - 1 customers; for each customer j = 1..n
 *   - a demand qⱼ
 *   - a service time sⱼ
 *   - a time window [rⱼ, dⱼ]
 * - A n×n symmetric matrix d specifying the times to travel between each pair
 *   of locations
 * Problem:
 * - find a set of at most m routes that begin and end at the depot, such that
 *   - each customer is visited on exactly one route
 *   - each customer is visited during its time window
 *   - the total demand by the customers assigned to a route does not exceed
 *     the vehicle capacity Q.
 * Objective:
 * - minimize the total combined cost of the routes. The cost of a route is the
 *   sum of travel times between each pair of consecutive location of the
 *   route, including the departure and the arrival to the depot, excluding the
 *   waiting times.
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
namespace vehicleroutingwithtimewindows
{

using LocationId = int64_t;
using LocationPos = int64_t;
using RouteId = int64_t;
using Demand = double;
using Time = int64_t;

/**
 * Structure for a location.
 */
struct Location
{
    /** x-coordinate of the location. */
    double x;

    /** y-coordinate of the location. */
    double y;

    /** Demand of the location. */
    Demand demand;

    /** Release date of the location. */
    Time release_date = 0;

    /** Deadline of the location. */
    Time deadline = 0;

    /** Service time of the location. */
    Time service_time = 0;
};

/**
 * Instance class for a 'vehicleroutingwithtimewindows' problem.
 */
class Instance
{

public:

    /*
     * Getters
     */

    /** Get the number of vehicles. */
    inline RouteId number_of_vehicles() const { return number_of_vehicles_; }

    /** Get the number of locations. */
    inline LocationId number_of_locations() const { return locations_.size(); }

    /** Get the vehicle capacity. */
    inline Demand capacity() const { return locations_[0].demand; }

    /** Get a location. */
    inline const Location& location(LocationId location_id) const { return locations_[location_id]; }

    /** Get the travel time between two locations. */
    inline Time travel_time(
            LocationId location_id_1,
            LocationId location_id_2) const
    {
        return travel_times_[std::max(location_id_1, location_id_2)][std::min(location_id_1, location_id_2)];
    }

    /** Get the maximum travel time between two locations. */
    inline Time highest_travel_time() const { return highest_travel_time_; }

    /** Get the maximum service time between two locations. */
    inline Time highest_service_time() const { return highest_service_time_; }

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
                << "Number of vehicles:   " << number_of_vehicles() << std::endl
                << "Number of locations:  " << number_of_locations() << std::endl
                << "Capacity:             " << capacity() << std::endl
                ;
        }

        if (verbosity_level >= 2) {
            os << std::endl
                << std::setw(12) << "Location"
                << std::setw(12) << "Demand"
                << std::setw(12) << "Serv. time"
                << std::setw(12) << "Rel. date"
                << std::setw(12) << "Deadline"
                << std::endl
                << std::setw(12) << "--------"
                << std::setw(12) << "----------"
                << std::setw(12) << "------"
                << std::setw(12) << "---------"
                << std::setw(12) << "--------"
                << std::endl;
            for (LocationId location_id_1 = 0;
                    location_id_1 < number_of_locations();
                    ++location_id_1) {
                os << std::setw(12) << location_id_1
                    << std::setw(12) << location(location_id_1).demand
                    << std::setw(12) << location(location_id_1).service_time
                    << std::setw(12) << location(location_id_1).release_date
                    << std::setw(12) << location(location_id_1).deadline
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
                for (LocationId location_id_2 = 0;
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
    std::pair<bool, Time> check(
            const std::string& certificate_path,
            std::ostream& os,
            int verbosity_level = 1) const
    {
        std::ifstream file(certificate_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");
        }

        if (verbosity_level >= 2) {
            os << std::endl << std::right
                << std::setw(10) << "Route"
                << std::setw(10) << "Location"
                << std::setw(12) << "Route dem."
                << std::setw(12) << "Time"
                << std::setw(12) << "Route tr."
                << std::endl
                << std::setw(10) << "-----"
                << std::setw(10) << "--------"
                << std::setw(12) << "----------"
                << std::setw(12) << "----"
                << std::setw(12) << "---------"
                << std::endl;
        }

        optimizationtools::IndexedSet visited_locations(number_of_locations());
        RouteId number_of_routes = -1;
        LocationPos route_number_of_locations = -1;

        LocationPos number_of_duplicates = 0;
        RouteId number_of_overloaded_vehicles = 0;
        LocationPos number_of_late_visits = 0;

        Time total_travel_time = 0;
        file >> number_of_routes;
        for (RouteId route_id = 0; route_id < number_of_routes; ++route_id) {
            file >> route_number_of_locations;
            if (route_number_of_locations == 0)
                continue;
            Time current_time = 0;
            Time route_travel_time = 0;
            Demand demand = 0;
            LocationId location_id_prev = 0;
            LocationId location_id = -1;
            for (LocationPos pos = 0; pos <= route_number_of_locations; ++pos) {
                if (pos < route_number_of_locations) {
                    file >> location_id;

                    // Check duplicates.
                    if (visited_locations.contains(location_id)) {
                        number_of_duplicates++;
                        if (verbosity_level >= 2)
                            os << "Location " << location_id
                                << " has already been visited." << std::endl;
                    }
                    visited_locations.add(location_id);

                    demand += location(location_id).demand;
                } else {
                    location_id = 0;
                }
                current_time += travel_time(location_id_prev, location_id);
                if (current_time < location(location_id).release_date)
                    current_time = location(location_id).release_date;

                // Check deadline.
                if (current_time > location(location_id).deadline)
                    number_of_late_visits++;

                route_travel_time += travel_time(location_id_prev, location_id);

                if (verbosity_level >= 2) {
                    os
                        << std::setw(10) << route_id
                        << std::setw(10) << location_id
                        << std::setw(12) << demand
                        << std::setw(12) << current_time
                        << std::setw(12) << route_travel_time
                        << std::endl;
                }

                current_time += location(location_id).service_time;
                location_id_prev = location_id;
            }
            if (location_id_prev != 0)
                route_travel_time += travel_time(location_id_prev, 0);
            total_travel_time += route_travel_time;

            if (verbosity_level >= 2) {
                os
                    << std::setw(10) << route_id
                    << std::setw(10) << 0
                    << std::setw(12) << demand
                    << std::setw(12) << current_time
                    << std::setw(12) << route_travel_time
                    << std::endl;
            }

            // Check vehicle capacity.
            if (demand > capacity())
                number_of_overloaded_vehicles++;
        }

        bool feasible
            = (visited_locations.size() == number_of_locations() - 1)
            && (!visited_locations.contains(0))
            && (number_of_duplicates == 0)
            && (number_of_routes <= number_of_vehicles())
            && (number_of_overloaded_vehicles == 0)
            && (number_of_late_visits == 0);
        if (verbosity_level >= 2)
            os << std::endl;
        if (verbosity_level >= 1) {
            os
                << "Number of visited locations:    " << visited_locations.size() << " / " << number_of_locations() - 1 << std::endl
                << "Number of duplicates:           " << number_of_duplicates << std::endl
                << "Number of routes:               " << number_of_routes << " / " << number_of_vehicles() << std::endl
                << "Number of overloaded vehicles:  " << number_of_overloaded_vehicles << std::endl
                << "Number of late visits:          " << number_of_late_visits << std::endl
                << "Feasible:                       " << feasible << std::endl
                << "Total travel time:              " << total_travel_time << std::endl
                ;
        }
        return {feasible, total_travel_time};
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

    /** Travel times. */
    std::vector<std::vector<Time>> travel_times_;

    /** Number of vehicles. */
    RouteId number_of_vehicles_ = 0;

    /*
     * Computed attributes
     */

    /** Maximum travel time. */
    Time highest_travel_time_ = 0;

    /** Maximum service time. */
    Time highest_service_time_ = 0;

    friend class InstanceBuilder;
};

class InstanceBuilder
{

public:

    /** Constructor. */
    InstanceBuilder() { }

    /** Set the number of vehicles. */
    void set_number_of_vehicles(
            RouteId number_of_vehicles)
    {
        instance_.number_of_vehicles_ = number_of_vehicles;
    }

    /** Set the capacity of the vehicles. */
    void set_capacity(Demand capacity) { instance_.locations_[0].demand = capacity; }

    /** Set the properties of a location. */
    void add_location(
            Demand demand,
            Time release_date,
            Time deadline,
            Time service_time)
    {
        Location location;
        location.demand = demand;
        location.release_date = release_date;
        location.deadline = deadline;
        location.service_time = service_time;
        instance_.locations_.push_back(location);

        instance_.travel_times_.push_back(std::vector<Time>(instance_.locations_.size()));
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
        instance_.travel_times_[std::max(location_id_1, location_id_2)][std::min(location_id_1, location_id_2)] = travel_time;
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
        if (format == "" || format == "dimacs2021") {
            read_dimacs2021(file);
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
        // Compute maximum service time and maximum travel time.
        for (LocationId location_id_1 = 0;
                location_id_1 < instance_.number_of_locations();
                ++location_id_1) {
            instance_.highest_service_time_ = std::max(
                    instance_.highest_service_time_,
                    instance_.location(location_id_1).service_time);
            for (LocationId location_id_2 = location_id_1 + 1;
                    location_id_2 < instance_.number_of_locations();
                    ++location_id_2) {
                instance_.highest_travel_time_ = std::max(
                        instance_.highest_travel_time_,
                        instance_.travel_time(location_id_1, location_id_2));
            }
        }

        return std::move(instance_);
    }

private:

    /*
     * Private methods
     */

    /** Read an instance from a file in 'dimacs2021' format. */
    void read_dimacs2021(std::ifstream& file)
    {
        std::string tmp;
        file >> tmp >> tmp >> tmp >> tmp;

        // Read number of locations.
        RouteId number_of_vehicles = -1;
        file >> number_of_vehicles;
        set_number_of_vehicles(number_of_vehicles);

        // Read capacity.
        Demand capacity = -1;
        file >> capacity;

        file
            >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp
            >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp
            ;

        // Read locations.
        LocationId location_id;
        double x = -1;
        double y = -1;
        Demand demand = -1;
        Time release_date = -1;
        Time deadline = -1;
        Time service_time = -1;
        while (file >> location_id >> x >> y >> demand >> release_date >> deadline >> service_time) {
            add_location(
                    demand,
                    10 * release_date,
                    10 * deadline,
                    10 * service_time);
            set_location_coordinates(location_id, x, y);
        }
        set_capacity(capacity);

        // Compute times.
        for (LocationId location_id_1 = 0;
                location_id_1 < instance_.number_of_locations();
                ++location_id_1) {
            for (LocationId location_id_2 = location_id_1 + 1;
                    location_id_2 < instance_.number_of_locations();
                    ++location_id_2) {
                double xd = instance_.location(location_id_2).x - instance_.location(location_id_1).x;
                double yd = instance_.location(location_id_2).y - instance_.location(location_id_1).y;
                double e = std::sqrt(xd * xd + yd * yd);
                //Time d = std::round(e * 10) / 10;
                Time d = std::floor(e * 10);
                set_travel_time(location_id_1, location_id_2, d);
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
