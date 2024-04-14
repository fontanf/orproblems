/**
 * Capacitated open vehicle routing problem
 *
 * Input:
 * - m vehicles of capacity Q
 * - A maximum route length L
 * - 1 depot
 * - n - 1 customers; for each customer j = 2..n, a demand qⱼ
 * - A n×n symmetric matrix d specifying the distances to travel between each
 *   pair of locations
 * Problem:
 * - find a set of at most m paths that begin (but does not end) at the depot,
 *   such that
 *   - each customer is visited on exactly one path
 *   - the total demand by the customers assigned to a path does not exceed
 *     the vehicle capacity Q
 *   - the total length of each route does not exceed the maximum route length
 * Objective:
 * - minimize the total combined distance of the routes.
 *
 */

#pragma once

#include "optimizationtools/utils/utils.hpp"
#include "optimizationtools/containers/indexed_set.hpp"

#include "travelingsalesmansolver/distances/distances_builder.hpp"

#include <iostream>
#include <fstream>
#include <memory>
#include <iomanip>

namespace orproblems
{
namespace capacitated_open_vehicle_routing
{

using LocationId = int64_t;
using LocationPos = int64_t;
using VehicleId = int64_t;
using RouteId = int64_t;
using Demand = int64_t;
using Distance = double;

/**
 * Instance class for a 'capacitated_open_vehicle_routing' problem.
 */
class Instance
{

public:

    /*
     * Getters
     */

    /** Get the number of vehicles. */
    inline VehicleId number_of_vehicles() const { return number_of_vehicles_; }

    /** Get the number of locations. */
    inline LocationId number_of_locations() const { return demands_.size(); }

    /** Get the maximum length of a route. */
    inline Distance maximum_route_length() const { return maximum_route_length_; }

    /** Get the capacity of the vehicles. */
    inline Demand capacity() const { return demands_[0]; }

    /** Get the demand of a location. */
    inline Demand demand(LocationId location_id) const { return demands_[location_id]; }

    /** Get distances. */
    const travelingsalesmansolver::Distances& distances() const { return *distances_; }

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
                << "Number of vehicles:    " << number_of_vehicles() << std::endl
                << "Number of locations:   " << number_of_locations() << std::endl
                << "Maximum route length:  " << maximum_route_length() << std::endl
                << "Capacity:              " << capacity() << std::endl
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
                    << std::setw(12) << demand(location_id_1)
                    << std::endl;
            }
        }

        distances().format(os, verbosity_level);
    }

    /** Check a certificate. */
    std::pair<bool, Distance> check(
            const std::string& certificate_path,
            std::ostream& os,
            int verbosity_level = 1) const
    {
        return FUNCTION_WITH_DISTANCES(
                (this->Instance::check),
                *distances_,
                certificate_path,
                os,
                verbosity_level);
    }

    /** Check a certificate. */
    template <typename Distances>
    std::pair<bool, Distance> check(
            const Distances& distances,
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
        LocationPos number_of_duplicates = 0;
        LocationPos route_number_of_locations = -1;
        RouteId number_of_routes = 0;
        RouteId number_of_overloaded_vehicles = 0;
        RouteId number_of_route_maximum_length_violations = 0;
        Distance total_distance = 0;
        file >> number_of_routes;
        for (RouteId route_id = 0; route_id < number_of_routes; ++route_id) {
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
                    if (verbosity_level >= 2) {
                        os << "Location " << location_id
                            << " has already been visited." << std::endl;
                    }
                }
                visited_locations.add(location_id);

                route_demand += demand(location_id);
                route_distance += distances.distance(location_id_prev, location_id);
                total_distance += distances.distance(location_id_prev, location_id);

                if (verbosity_level >= 2) {
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

            // Check route maximum length.
            if (route_distance > maximum_route_length()) {
                number_of_route_maximum_length_violations++;
                if (verbosity_level >= 2) {
                    os << "Route " << route_id
                        << " is too long." << std::endl;
                }
            }

            // Check capacity.
            if (route_demand > capacity()) {
                number_of_overloaded_vehicles++;
                if (verbosity_level >= 2) {
                    os << "Vehicle " << route_id
                        << " is overloaded." << std::endl;
                }
            }
        }

        bool feasible
            = (visited_locations.size() == number_of_locations() - 1)
            && (!visited_locations.contains(0))
            && (number_of_duplicates == 0)
            && (number_of_overloaded_vehicles == 0)
            && (number_of_routes <= number_of_vehicles())
            && (number_of_route_maximum_length_violations == 0);

        if (verbosity_level == 2)
            os << std::endl;
        if (verbosity_level >= 1) {
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

    /** Constructor to build an instance manually. */
    Instance() { }

    /*
     * Private attributes
     */

    /** Demands. */
    std::vector<Demand> demands_;

    /** Distances. */
    std::shared_ptr<const travelingsalesmansolver::Distances> distances_;

    /** Number of vehicles. */
    VehicleId number_of_vehicles_ = 0;

    /** Maximum length of a rotue. */
    Distance maximum_route_length_ = std::numeric_limits<Distance>::infinity();;

    /*
     * Computed attributes
     */

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
     * This method resets the whole instance.
     */
    void set_number_of_locations(LocationId number_of_locations)
    {
        instance_.demands_ = std::vector<Demand>(number_of_locations);
        instance_.number_of_vehicles_ = number_of_locations;
    }

    /** Set the number of vehicles. */
    void set_number_of_vehicles(VehicleId number_of_vehicles) { instance_.number_of_vehicles_ = number_of_vehicles; }

    /** Set the maximum route length. */
    void set_maximum_route_length(Distance maximum_route_length) { instance_.maximum_route_length_ = maximum_route_length; }

    /** Set the demand of a location. */
    void set_demand(
            LocationId location_id,
            Demand demand)
    {
        instance_.demands_[location_id] = demand;
    }

    /** Set the distance between two cities. */
    inline void set_distances(
            const std::shared_ptr<const travelingsalesmansolver::Distances>& distances)
    {
        instance_.distances_ = distances;
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

        if (format == "" || format == "vrplib") {
            read_vrplib(file);
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

    /** Read an instance from a file in 'vrplib' format. */
    void read_vrplib(std::ifstream& file)
    {
        travelingsalesmansolver::DistancesBuilder distances_builder;

        std::string tmp;
        std::vector<std::string> line;
        LocationId number_of_locations = -1;
        std::string edge_weight_type;
        while (getline(file, tmp)) {
            replace(begin(tmp), end(tmp), '\t', ' ');
            line = optimizationtools::split(tmp, ' ');
            if (line.empty()) {
            } else if (distances_builder.read_tsplib(file, tmp, line)) {
            } else if (tmp.rfind("NAME", 0) == 0) {
            } else if (tmp.rfind("COMMENT", 0) == 0) {
            } else if (tmp.rfind("TYPE", 0) == 0) {
            } else if (tmp.rfind("DEPOT_SECTION", 0) == 0) {
                LocationId location_id_tmp;
                file >> location_id_tmp >> location_id_tmp;
            } else if (tmp.rfind("DIMENSION", 0) == 0) {
                number_of_locations = std::stol(line.back());
                set_number_of_locations(number_of_locations);
                distances_builder.set_number_of_vertices(number_of_locations);
            } else if (tmp.rfind("DISTANCE", 0) == 0) {
                Distance l = std::stol(line.back());
                set_maximum_route_length(l * 0.9);
            } else if (tmp.rfind("CAPACITY", 0) == 0) {
                Demand c = std::stol(line.back());
                set_demand(0, c);
            } else if (tmp.rfind("DEMAND_SECTION", 0) == 0) {
                LocationId location_id_tmp = -1;
                Demand demand = -1;
                for (LocationId location_id = 0;
                        location_id < number_of_locations;
                        ++location_id) {
                    file >> location_id_tmp >> demand;
                    if (location_id != 0)
                        set_demand(location_id, demand);
                }
            } else if (line[0].rfind("EOF", 0) == 0) {
                break;
            } else {
                throw std::invalid_argument(
                        "Entry \""
                        + line[0]
                        + "\" not implemented.");
            }
        }

        set_distances(std::shared_ptr<const travelingsalesmansolver::Distances>(
                    new travelingsalesmansolver::Distances(distances_builder.build())));
    }

    /*
     * Private attributes
     */

    /** Instance. */
    Instance instance_;

};

}
}
