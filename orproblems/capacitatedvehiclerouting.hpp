/**
 * Capacitated Vehicle Routing Problem.
 *
 * Input:
 * - vehicles of capacity Q
 * - 1 depot
 * - n - 1 customers; for each customer location_id = 2..n, a demand qⱼ
 * - A n×n symmetric matrix d specifying the distances to travel between each
 *   pair of locations
 * Problem:
 * - find a set of routes that begin and end at the depot, such that each
 *   customer is visited on exactly one route and the total demand by the
 *   customers assigned to a route does not exceed the vehicle capacity Q.
 * Objective:
 * - minimize the total combined distance of the routes.
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

namespace capacitatedvehiclerouting
{

using LocationId = int64_t;
using LocationPos = int64_t;
using RouteId = int64_t;
using Demand = int64_t;
using Distance = int64_t;
using RouteId = int64_t;

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
    Demand demand = 0;
};

/**
 * Instance class for a 'capacitatedvehiclerouting' problem.
 */
class Instance
{

public:

    /*
     * Constructors and destructor
     */

    /** Constructor to build an instance manually. */
    Instance(LocationId number_of_locations):
        locations_(number_of_locations),
        distances_(number_of_locations, std::vector<Distance>(number_of_locations, -1)) { }

    /** Set the capacity of the vehicles. */
    void set_capacity(Demand capacity) { locations_[0].demand = capacity; }

    /** Set the demand of a location. */
    void set_demand(
            LocationId location_id,
            Demand demand)
    {
        if (location_id != 0)
            total_demand_ -= locations_[location_id].demand;
        locations_[location_id].demand = demand;
        if (location_id != 0)
            total_demand_ += locations_[location_id].demand;
    }

    /** Set the coordinates of a location. */
    void set_xy(
            LocationId location_id,
            double x,
            double y)
    {
        locations_[location_id].x = x;
        locations_[location_id].y = y;
    }

    /** Set the distance between two locations. */
    void set_distance(
            LocationId location_id_1,
            LocationId location_id_2,
            Distance distance)
    {
        distances_[location_id_1][location_id_2] = distance;
        distances_[location_id_2][location_id_2] = distance;
        distance_max_ = std::max(distance_max_, distance);
    }

    /** Build an instance from a file. */
    Instance(
            std::string instance_path,
            std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        }

        if (format == "" || format == "vrplib") {
            read_cvrplib(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    /*
     * Getters
     */

    /** Get the number of locations. */
    inline LocationId number_of_locations() const { return locations_.size(); }

    /** Get the vehicle capacity. */
    inline Demand capacity() const { return locations_[0].demand; }

    /** Get the total demand. */
    inline Demand total_demand() const { return total_demand_; }

    /** Get the demand of a location. */
    inline Demand demand(LocationId location_id) const { return locations_[location_id].demand; }

    /** Get the x-coordinate of a location. */
    inline Distance x(LocationId location_id) const { return locations_[location_id].x; }

    /** Get the y-coordinate of a location. */
    inline Distance y(LocationId location_id) const { return locations_[location_id].y; }

    /** Get the distance between two locations. */
    inline Distance distance(
            LocationId location_id_1,
            LocationId location_id_2) const
    {
        return distances_[location_id_1][location_id_2];
    }

    /** Get the maximum distance between two locations. */
    inline Distance maximum_distance() const { return distance_max_; }

    /** Print the instance. */
    std::ostream& print(
            std::ostream& os,
            int verbose = 1) const
    {
        if (verbose >= 1) {
            os
                << "Number of locations:  " << number_of_locations() << std::endl
                << "Capacity:             " << capacity() << std::endl
                << "Total demand:         " << total_demand() << std::endl
                << "Demand ratio:         " << (double)total_demand() / capacity() << std::endl
                ;
        }

        if (verbose >= 2) {
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
                    << std::setw(12) << demand(location_id_1)
                    << std::endl;
            }
        }

        if (verbose >= 3) {
            os << std::endl
                << std::setw(12) << "Loc. 1"
                << std::setw(12) << "Loc. 2"
                << std::setw(12) << "Distance"
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
                        << std::setw(12) << distance(location_id_1, location_id_2)
                        << std::endl;
                }
            }
        }

        return os;
    }

    /** Check a certificate. */
    std::pair<bool, Distance> check(
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
                << std::setw(10) << "Route"
                << std::setw(10) << "Location"
                << std::setw(12) << "Route dem."
                << std::setw(12) << "Route dist."
                << std::setw(12) << "Tot. dist."
                << std::endl
                << std::setw(10) << "-----"
                << std::setw(10) << "--------"
                << std::setw(12) << "----------"
                << std::setw(12) << "-----------"
                << std::setw(12) << "----------"
                << std::endl;
        }

        optimizationtools::IndexedSet visited_locations(number_of_locations());
        RouteId number_of_routes = 0;
        LocationPos route_number_of_locations = -1;

        LocationPos number_of_duplicates = 0;
        RouteId number_of_overloaded_vehicles = 0;

        Distance total_distance = 0;
        file >> number_of_routes;
        for (RouteId route_id = 0; route_id < number_of_routes; ++route_id) {
            file >> route_number_of_locations;
            if (route_number_of_locations == 0)
                continue;
            Distance route_distance = 0;
            Demand route_demand = 0;
            LocationId location_id_prev = 0;
            LocationId location_id = -1;
            for (LocationPos pos = 0; pos < route_number_of_locations; ++pos) {
                file >> location_id;

                // Check duplicates.
                if (visited_locations.contains(location_id)) {
                    number_of_duplicates++;
                    if (verbose >= 2) {
                        os << "Location " << location_id
                            << " has already been visited." << std::endl;
                    }
                }
                visited_locations.add(location_id);

                route_demand += demand(location_id);
                route_distance += distance(location_id_prev, location_id);
                total_distance += distance(location_id_prev, location_id);

                if (verbose >= 2) {
                    os
                        << std::setw(10) << route_id
                        << std::setw(10) << location_id
                        << std::setw(12) << route_demand
                        << std::setw(12) << route_distance
                        << std::setw(12) << total_distance
                        << std::endl;
                }

                location_id_prev = location_id;
            }
            if (location_id_prev != 0) {
                route_distance += distance(location_id_prev, 0);
                total_distance += distance(location_id_prev, 0);
            }

            if (verbose >= 2) {
                os
                    << std::setw(10) << route_id
                    << std::setw(10) << 0
                    << std::setw(12) << route_demand
                    << std::setw(12) << route_distance
                    << std::setw(12) << total_distance
                    << std::endl;
            }

            // Check vehicle capacity.
            if (route_demand > capacity())
                number_of_overloaded_vehicles++;
        }

        bool feasible
            = (visited_locations.size() == number_of_locations() - 1)
            && (!visited_locations.contains(0))
            && (number_of_duplicates == 0)
            && (number_of_overloaded_vehicles == 0);
        if (verbose == 2)
            os << std::endl;
        if (verbose >= 1) {
            os
                << "Number of visited locations:    " << visited_locations.size() << " / " << number_of_locations() - 1 << std::endl
                << "Number of duplicates:           " << number_of_duplicates << std::endl
                << "Number of routes:               " << number_of_routes << std::endl
                << "Number of overloaded vehicles:  " << number_of_overloaded_vehicles << std::endl
                << "Feasible:                       " << feasible << std::endl
                << "Total distance:                 " << total_distance << std::endl
                ;
        }
        return {feasible, total_distance};
    }

private:

    /*
     * Private methods
     */

    /** Read an instance from a file in 'cvrplib' format. */
    void read_cvrplib(std::ifstream& file)
    {
        std::string tmp;
        std::vector<std::string> line;
        std::string edge_weight_type;
        while (getline(file, tmp)) {
            replace(begin(tmp), end(tmp), '\t', ' ');
            line = optimizationtools::split(tmp, ' ');
            if (line.empty()) {
            } else if (tmp.rfind("NAME", 0) == 0) {
            } else if (tmp.rfind("COMMENT", 0) == 0) {
            } else if (tmp.rfind("TYPE", 0) == 0) {
            } else if (tmp.rfind("DEPOT_SECTION", 0) == 0) {
                LocationId j_tmp;
                file >> j_tmp >> j_tmp;
            } else if (tmp.rfind("DIMENSION", 0) == 0) {
                LocationId n = std::stol(line.back());
                locations_ = std::vector<Location>(n);
                distances_ = std::vector<std::vector<Distance>>(n, std::vector<Distance>(n, -1));
            } else if (tmp.rfind("EDGE_WEIGHT_TYPE", 0) == 0) {
                edge_weight_type = line.back();
            } else if (tmp.rfind("CAPACITY", 0) == 0) {
                Demand c = std::stol(line.back());
                set_demand(0, c);
            } else if (tmp.rfind("NODE_COORD_SECTION", 0) == 0) {
                LocationId j_tmp;
                double x = -1;
                double y = -1;
                for (LocationId location_id = 0;
                        location_id < number_of_locations();
                        ++location_id) {
                    file >> j_tmp >> x >> y;
                    set_xy(location_id, x, y);
                }
            } else if (tmp.rfind("DEMAND_SECTION", 0) == 0) {
                LocationId j_tmp = -1;
                Demand demand = -1;
                for (LocationId location_id = 0;
                        location_id < number_of_locations();
                        ++location_id) {
                    file >> j_tmp >> demand;
                    if (location_id != 0)
                        set_demand(location_id, demand);
                }
            } else if (line[0].rfind("EOF", 0) == 0) {
                break;
            } else {
                std::cerr << "\033[31m" << "ERROR, ENTRY \"" << line[0] << "\" not implemented." << "\033[0m" << std::endl;
            }
        }

        // Compute distances.
        if (edge_weight_type == "EUC_2D") {
            for (LocationId location_id_1 = 0;
                    location_id_1 < number_of_locations();
                    ++location_id_1) {
                for (LocationId location_id_2 = location_id_1 + 1;
                        location_id_2 < number_of_locations();
                        ++location_id_2) {
                    double xd = x(location_id_2) - x(location_id_1);
                    double yd = y(location_id_2) - y(location_id_1);
                    Distance d = std::round(std::sqrt(xd * xd + yd * yd));
                    set_distance(location_id_1, location_id_2, d);
                }
            }
        } else {
            std::cerr << "\033[31m" << "ERROR, EDGE_WEIGHT_TYPE \"" << edge_weight_type << "\" not implemented." << "\033[0m" << std::endl;
        }
    }

    /*
     * Private attributes
     */

    /** Locations. */
    std::vector<Location> locations_;

    /** Distances between locations. */
    std::vector<std::vector<Distance>> distances_;

    /*
     * Computed attributes
     */

    /** Total demand. */
    Demand total_demand_ = 0;

    /** Maximum distance between two locations. */
    Distance distance_max_ = 0;

};

}

}
