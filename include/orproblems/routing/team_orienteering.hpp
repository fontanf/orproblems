/**
 * Team orienteering problem
 *
 * Input:
 * - m vehicles
 * - 1 starting depot
 * - 1 ending depot
 * - n - 2 potential locations to visit; for each potential location j = 2..n to
 *   visit, a profit pⱼ
 * - An n×n symmetric matrix containing the travel times between each
 *   pair of locations
 * - A maximum duration tₘₐₓ
 * Problem:
 * - Find m tours such that:
 *   - Each potential location to visit is visited at most once.
 *   - Each tour starts at the starting depot and ends at the ending depot.
 *   - The duration of each tour is smaller than tₘₐₓ.
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
namespace team_orienteering
{

using LocationId = int64_t;
using LocationPos = int64_t;
using VehicleId = int64_t;
using Time = double;
using Profit = double;

/**
 * Structure for a location.
 */
struct Location
{
    /** x-coordinate of the location. */
    double x;

    /** y-coordinate of the location. */
    double y;

    /** Profit of the location. */
    Profit profit;
};


/**
 * Instance class for a 'team_orienteering' problem.
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

    /** Get the number of vehicles. */
    inline LocationId number_of_vehicles() const { return number_of_vehicles_; }

    /** Get the maximum duration. */
    inline Time maximum_duration() const { return maximum_duration_; }

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
                << "Number of locations:  " << number_of_locations() << std::endl
                << "Number of vehicles:   " << number_of_vehicles() << std::endl
                << "Maximum duration:     " << maximum_duration() << std::endl
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

        if (verbosity_level >= 3) {
            os << std::endl << std::right
                << std::setw(12) << "Vehicle"
                << std::setw(12) << "Location"
                << std::setw(12) << "Profit"
                << std::setw(12) << "Travel time"
                << std::setw(12) << "Total time"
                << std::setw(12) << "Tot. profit"
                << std::endl
                << std::setw(12) << "-------"
                << std::setw(12) << "--------"
                << std::setw(12) << "------"
                << std::setw(12) << "-----------"
                << std::setw(12) << "----------"
                << std::setw(12) << "-----------"
                << std::endl;
        }

        LocationId location_id = -1;
        optimizationtools::IndexedSet locations(number_of_locations());
        LocationPos number_of_duplicates = 0;
        LocationPos number_of_tour_duration_violations = 0;
        Profit profit = 0;
        for (VehicleId vehicle_id = 0;
                vehicle_id < number_of_vehicles();
                ++vehicle_id) {
            Time tour_duration = 0;
            LocationId tour_number_of_locations = -1;
            file >> tour_number_of_locations;
            LocationId location_id_prev = 0;
            for (LocationPos pos = 0; pos < tour_number_of_locations; ++pos) {
                LocationId location_id;
                file >> location_id;
                if (location_id == 0
                        || location_id == number_of_locations() - 1) {
                    locations.add(location_id);
                    if (verbosity_level >= 1)
                        os << "Location " << location_id
                            << " must not appear in the certificate."
                            << std::endl;
                }

                tour_duration += travel_time(location_id_prev, location_id);
                profit += location(location_id).profit;

                if (verbosity_level >= 3) {
                    os
                        << std::setw(12) << vehicle_id
                        << std::setw(12) << location_id
                        << std::setw(12) << location(location_id).profit
                        << std::setw(12) << travel_time(location_id_prev, location_id)
                        << std::setw(12) << tour_duration
                        << std::setw(12) << profit
                        << std::endl;
                }

                // Check duplicates.
                if (locations.contains(location_id)) {
                    number_of_duplicates++;
                    if (verbosity_level >= 2)
                        os << "Location " << location_id
                            << " has already been visited." << std::endl;
                }
                locations.add(location_id);

                location_id_prev = location_id;
            }

            // Finish last tour.
            tour_duration += travel_time(
                    location_id_prev,
                    number_of_locations() - 1);
            if (verbosity_level >= 3) {
                os
                    << std::setw(12) << vehicle_id
                    << std::setw(12) << 0
                    << std::setw(12) << location(location_id).profit
                    << std::setw(12) << travel_time(location_id_prev, location_id)
                    << std::setw(12) << tour_duration
                    << std::setw(12) << profit
                    << std::endl;
            }
            if (verbosity_level >= 2) {
                os << "Tour " << vehicle_id
                    << "; duration: " << tour_duration
                    << " / " << maximum_duration()
                    << std::endl;
            }
            if (tour_duration > maximum_duration()) {
                number_of_tour_duration_violations++;
            }
        }

        bool feasible
            = (number_of_tour_duration_violations == 0)
            && (!locations.contains(0))
            && (number_of_duplicates == 0);

        if (verbosity_level >= 2)
            os << std::endl;
        if (verbosity_level >= 1) {
            os
                << "Number of locations:                 " << locations.size() << " / " << number_of_locations() - 1 << std::endl
                << "Number of duplicates:                " << number_of_duplicates << std::endl
                << "Number of tour duration violations:  " << number_of_tour_duration_violations << std::endl
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

    /** Number of vehicles. */
    VehicleId number_of_vehicles_ = 0;

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

    /** Set the number of vehicles. */
    void set_number_of_vehicles(
            VehicleId number_of_vehicles)
    {
        instance_.number_of_vehicles_ = number_of_vehicles;
    }

    /** Set the maximum duration. */
    void set_maximum_duration(
            Time maximum_duration)
    {
        instance_.maximum_duration_ = maximum_duration;
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
        if (format == "" || format == "chao1996") {
            read_chao1996(file);
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

    /** Read an instance from a file in 'chao1996' format. */
    void read_chao1996(
            std::ifstream& file)
    {
        std::string tmp;
        LocationPos number_of_locations = -1;
        LocationPos number_of_vehicles = -1;
        Time maximum_duration = -1;
        file >> tmp >> number_of_locations
            >> tmp >> number_of_vehicles
            >> tmp >> maximum_duration;
        set_number_of_locations(number_of_locations);
        set_number_of_vehicles(number_of_vehicles);
        set_maximum_duration(maximum_duration);

        double x = -1;
        double y = -1;
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
