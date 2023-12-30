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

using LocationId = int64_t;
using LocationPos = int64_t;
using Time = double;

/**
 * Structure for a location.
 */
struct Location
{
    /** x-coordinate. */
    double x;

    /** y-coordinate. */
    double y;
};

/**
 * Instance class for a 'travelingrepairman' problem.
 */
class Instance
{

public:

    /*
     * Getters
     */

    /** Get the number of locations. */
    inline LocationId number_of_locations() const { return travel_times_.size(); }

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
            os << "Number of locations:  " << number_of_locations() << std::endl;
        }

        if (verbosity_level >= 2) {
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
                << std::setw(12) << "Location"
                << std::setw(12) << "Time"
                << std::setw(12) << "TCT"
                << std::endl
                << std::setw(12) << "--------"
                << std::setw(12) << "----"
                << std::setw(12) << "---"
                << std::endl;
        }

        LocationId location_id = -1;
        LocationId location_id_prev = 0;
        optimizationtools::IndexedSet locations(number_of_locations());
        locations.add(0);
        LocationPos number_of_duplicates = 0;
        Time current_time = 0;
        Time total_completion_time = 0;
        while (file >> location_id) {
            // Check duplicates.
            if (locations.contains(location_id)) {
                number_of_duplicates++;
                if (verbosity_level >= 2)
                    os << "Location " << location_id
                        << " has already been visited." << std::endl;
            }
            locations.add(location_id);

            current_time += travel_time(location_id_prev, location_id);
            total_completion_time += current_time;

            if (verbosity_level >= 2) {
                os
                    << std::setw(12) << location_id
                    << std::setw(12) << current_time
                    << std::setw(12) << total_completion_time
                    << std::endl;
            }

            location_id_prev = location_id;
        }

        bool feasible
            = (locations.size() == number_of_locations())
            && (number_of_duplicates == 0);

        if (verbosity_level >= 2)
            os << std::endl;
        if (verbosity_level >= 1) {
            os
                << "Number of locations:       " << locations.size() << " / " << number_of_locations()  << std::endl
                << "Number of duplicates:      " << number_of_duplicates << std::endl
                << "Feasible:                  " << feasible << std::endl
                << "Total completion time:     " << total_completion_time << std::endl
                ;
        }
        return {feasible, total_completion_time};
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
     * This method resets the locations and travel times.
     */
    void set_number_of_locations(LocationId number_of_locations)
    {
        instance_.locations_ = std::vector<Location>(number_of_locations),
        instance_.travel_times_ = std::vector<std::vector<Time>>(
                number_of_locations,
                std::vector<Time>(number_of_locations, -1));
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
        if (format == "" || format == "salehipour2011") {
            read_salehipour2011(file);
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

    /** Read an instance from a file in 'salehipour2011' format. */
    void read_salehipour2011(std::ifstream& file)
    {
        std::string tmp;

        LocationId number_of_locations = -1;
        file
            >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp
            >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp
            >> number_of_locations
            >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp
            ;
        set_number_of_locations(number_of_locations);

        // Read location coordinates.
        double x = -1;
        double y = -1;
        for (LocationId location_id = 0;
                location_id < number_of_locations + 1;
                ++location_id) {
            file >> tmp >> x >> y;
            set_location_coordinates(location_id, x, y);
        }

        for (LocationId location_id_1 = 0;
                location_id_1 < number_of_locations + 1;
                ++location_id_1) {
            for (LocationId location_id_2 = 0;
                    location_id_2 < number_of_locations + 1;
                    ++location_id_2) {
                Time dx = instance_.locations_[location_id_1].x - instance_.locations_[location_id_2].x;
                Time dy = instance_.locations_[location_id_1].y - instance_.locations_[location_id_2].y;
                Time dxy = std::floor(std::sqrt(dx * dx + dy * dy));
                set_travel_time(location_id_1, location_id_2, dxy);
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
