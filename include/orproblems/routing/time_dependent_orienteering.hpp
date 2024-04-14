/**
 * Time-dependent orienteering problem
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

#pragma once

#include "optimizationtools/containers/indexed_set.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

namespace orproblems
{
namespace time_dependent_orienteering
{

using LocationId = int64_t;
using LocationPos = int64_t;
using ArcCategory = int64_t;
using TimePeriod = int64_t;
using Time = double;
using Length = double;
using Profit = double;

/**
 * Structure for a location.
 */
struct Location
{
    /** x-coordinate. */
    Length x;

    /** y-coordinate. */
    Length y;

    /** Profit. */
    Profit profit;
};

/**
 * Structure for an arc.
 */
struct Arc
{
    /** Category. */
    ArcCategory category;

    /** Length. */
    Length length;
};

/**
 * Instance class for a 'time_dependent_orienteering' problem.
 */
class Instance
{

public:

    /*
     * Getters
     */

    /** Get the number of locations. */
    inline LocationId number_of_locations() const { return locations_.size(); }

    /** Get the maximum duraction. */
    inline Time maximum_duration() const { return maximum_duration_; }

    /** Get a location. */
    inline const Location& location(LocationId location_id) const { return locations_[location_id]; }

    /**
     * Get the arrival time at a location depending on the departure location
     * and the departure time.
     */
    inline Time arrival_time(
            LocationId location_id_1,
            LocationId location_id_2,
            Time start) const
    {
        Time current_time = start;
        Length remaining_length = arcs_[location_id_1][location_id_2].length;
        ArcCategory arc_category = arcs_[location_id_1][location_id_2].category;
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
                //os << "location_id_1 " << location_id_1
                //    << " location_id_2 " << location_id_2
                //    << " x1 " << locations_[location_id_1].x
                //    << " y1 " << locations_[location_id_1].y
                //    << " x2 " << locations_[location_id_2].x
                //    << " y2 " << locations_[location_id_2].y
                //    << " length " << arcs_[location_id_1][location_id_2].length
                //    << " cat " << arc_category
                //    << " start " << start
                //    << " dur " << at - start
                //    << " arrival " << at << " / " << time_period_end
                //    << std::endl;
                return at;
            }
            remaining_length -= (time_period_end - current_time) * speed;
            //os << "remaining_length " << remaining_length << std::endl;
            current_time = time_period_end;
            time_period++;
        }
        return -1;
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
            os << "Maximum duration:     " << maximum_duration() << std::endl;
        }

        // Print locations.
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

        if (verbosity_level >= 2) {
            os << std::endl << std::right
                << std::setw(12) << "Location"
                << std::setw(12) << "Profit"
                << std::setw(12) << "Total time"
                << std::setw(12) << "Tot. profit"
                << std::endl
                << std::setw(12) << "--------"
                << std::setw(12) << "------"
                << std::setw(12) << "----------"
                << std::setw(12) << "-----------"
                << std::endl;
        }

        LocationId location_id = -1;
        LocationId location_id_prev = 0;
        optimizationtools::IndexedSet locations(number_of_locations());
        locations.add(0);
        locations.add(number_of_locations() - 1);
        LocationPos number_of_duplicates = 0;
        Time current_time = 0;
        Profit profit = location(0).profit;
        while (file >> location_id) {

            // Check duplicates.
            if (locations.contains(location_id)) {
                number_of_duplicates++;
                if (verbosity_level >= 2)
                    os << "Location " << location_id
                        << " has already been visited." << std::endl;
            }
            locations.add(location_id);

            current_time = arrival_time(
                    location_id_prev,
                    location_id,
                    current_time);
            profit += location(location_id).profit;

            if (verbosity_level >= 2) {
                os
                    << std::setw(12) << location_id
                    << std::setw(12) << location(location_id).profit
                    << std::setw(12) << current_time
                    << std::setw(12) << profit
                    << std::endl;
            }

            location_id_prev = location_id;
        }
        current_time = arrival_time(location_id_prev, number_of_locations() - 1, current_time);
        profit += location(number_of_locations() - 1).profit;

        if (verbosity_level >= 2) {
            os
                << std::setw(12) << number_of_locations() - 1
                << std::setw(12) << location(number_of_locations() - 1).profit
                << std::setw(12) << current_time
                << std::setw(12) << profit
                << std::endl;
        }

        bool feasible
            = (current_time <= maximum_duration())
            && (number_of_duplicates == 0);

        if (verbosity_level >= 2)
            os << std::endl;
        if (verbosity_level >= 1) {
            os << "Number of locations:       " << locations.size() << " / " << number_of_locations()  << std::endl;
            os << "Number of duplicates:      " << number_of_duplicates << std::endl;
            os << "Duraction:                 " << current_time << " / " << maximum_duration() << std::endl;
            os << "Feasible:                  " << feasible << std::endl;
            os << "Profit:                    " << profit << std::endl;
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

    /** Arcs. */
    std::vector<std::vector<Arc>> arcs_;

    /** Speed matrix. */
    std::vector<std::vector<double>> speed_matrix_;

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
     * This method resets the locations, arcs and the speed matrix.
     */
    void set_number_of_locations(LocationId number_of_locations)
    {
        instance_.locations_ = std::vector<Location>(number_of_locations);
        instance_.arcs_ = std::vector<std::vector<Arc>>(
                number_of_locations,
                std::vector<Arc>(number_of_locations));
        instance_.speed_matrix_ = std::vector<std::vector<double>>(
                5,
                std::vector<double>(4, 0.0));
    }

    /** Set the maximum duration. */
    void set_maximum_duration(Time maximum_duration) { instance_.maximum_duration_ = maximum_duration; }

    /** Set the profit of a location; */
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

    /** Set the length of an arc. */
    void set_arc_length(
        LocationId location_id_1,
        LocationId location_id_2,
        Length length)
    {
        instance_.arcs_[location_id_1][location_id_2].length = length;
    }

    /** Set the category of an arc. */
    void set_arc_category(
        LocationId location_id_1,
        LocationId location_id_2,
        ArcCategory category)
    {
        instance_.arcs_[location_id_1][location_id_2].category = category;
    }

    /** Set the speed for an arc category and a given time period. */
    void set_speed(
            ArcCategory arc_category,
            TimePeriod time_period,
            double speed)
    {
        instance_.speed_matrix_[arc_category][time_period] = speed;
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
        if (format == "" || format == "verbeeck2014") {
            read_verbeeck2014(file, instance_path);
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

    /** Read an instance from a file in 'verbeeck2014' format. */
    void read_verbeeck2014(
            std::ifstream& file,
            const std::string& instance_path)
    {
        std::string tmp;

        LocationId number_of_locations = -1;
        file >> tmp >> number_of_locations;
        set_number_of_locations(number_of_locations);

        Time maximum_duration = -1;
        file >> tmp >> tmp >> tmp >> maximum_duration;
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
            for (LocationId location_id_2 = 0;
                    location_id_2 < number_of_locations;
                    ++location_id_2) {
                Length dx = instance_.location(location_id_1).x - instance_.location(location_id_2).x;
                Length dy = instance_.location(location_id_1).y - instance_.location(location_id_2).y;
                Length dxy = std::sqrt(dx * dx + dy * dy);
                dxy /= 5;
                set_arc_length(location_id_1, location_id_2, dxy);
            }
        }

        // Read speed matrix.
        auto speed_matrix_path = boost::filesystem::path(instance_path)
            .parent_path().parent_path().parent_path() /= "speedmatrix.txt";
        std::ifstream speed_matrix_file(speed_matrix_path.string());
        double speed = -1;
        for (ArcCategory arc_category = 0; arc_category < 5; ++arc_category) {
            for (TimePeriod time_period = 0; time_period < 4; ++time_period) {
                speed_matrix_file >> speed;
                set_speed(arc_category, time_period, speed);
            }
        }

        // Read arc category matrix.
        ArcCategory arc_category;
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
            for (LocationId location_id_1 = 0;
                    location_id_1 < number_of_locations;
                    ++location_id_1) {
                for (LocationId location_id_2 = 0;
                        location_id_2 < number_of_locations;
                        ++location_id_2) {
                    arc_category_file >> arc_category;
                    set_arc_category(location_id_1, location_id_2, arc_category);
                }
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
