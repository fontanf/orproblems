/**
 * Capacitated vehicle routing problem
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

#include "optimizationtools/containers/indexed_set.hpp"
#include "optimizationtools/utils/utils.hpp"

#include "travelingsalesmansolver/distances_builder.hpp"

#include <iostream>
#include <fstream>
#include <memory>
#include <iomanip>

namespace orproblems
{
namespace capacitated_vehicle_routing
{

using LocationId = int64_t;
using LocationPos = int64_t;
using RouteId = int64_t;
using Demand = int64_t;
using Distance = int64_t;

/**
 * Instance class for a 'capacitated_vehicle_routing' problem.
 */
class Instance
{

public:

    /*
     * Getters
     */

    /** Get the number of locations. */
    inline LocationId number_of_locations() const { return demands_.size(); }

    /** Get the vehicle capacity. */
    inline Demand capacity() const { return demands_[0]; }

    /** Get the total demand. */
    inline Demand total_demand() const { return total_demand_; }

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
                << "Number of locations:  " << number_of_locations() << std::endl
                << "Capacity:             " << capacity() << std::endl
                << "Total demand:         " << total_demand() << std::endl
                << "Demand ratio:         " << (double)total_demand() / capacity() << std::endl
                ;
        }

        if (verbosity_level >= 2) {
            os << std::endl
                << std::setw(12) << "Location"
                << std::setw(12) << "Demand"
                << std::endl
                << std::setw(12) << "--------"
                << std::setw(12) << "----------"
                << std::endl;
            for (LocationId location_id_1 = 0;
                    location_id_1 < number_of_locations();
                    ++location_id_1) {
                os << std::setw(12) << location_id_1
                    << std::setw(12) << demand(location_id_1)
                    << std::endl;
            }
        }

        if (verbosity_level >= 3) {
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
                        << std::setw(12) << distances().distance(location_id_1, location_id_2)
                        << std::endl;
                }
            }
        }
    }

    /** Check a certificate. */
    std::pair<bool, Distance> check(
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
                    if (verbosity_level >= 2) {
                        os << "Location " << location_id
                            << " has already been visited." << std::endl;
                    }
                }
                visited_locations.add(location_id);

                route_demand += demand(location_id);
                route_distance += distances().distance(location_id_prev, location_id);
                total_distance += distances().distance(location_id_prev, location_id);

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
            if (location_id_prev != 0) {
                route_distance += distances().distance(location_id_prev, 0);
                total_distance += distances().distance(location_id_prev, 0);
            }

            if (verbosity_level >= 2) {
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
        if (verbosity_level >= 2)
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

    /*
     * Computed attributes
     */

    /** Total demand. */
    Demand total_demand_ = 0;

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
    }

    /** Set the capacity of the vehicles. */
    void set_capacity(Demand capacity) { instance_.demands_[0] = capacity; }

    /** Set the demand of a location. */
    void set_location_demand(
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
            read_cvrplib(file);
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
        // Compute total demand.
        instance_.total_demand_ = 0;
        for (LocationId location_id = 0;
                location_id < instance_.number_of_locations();
                ++location_id) {
            instance_.total_demand_ += instance_.demand(location_id);
        }

        return std::move(instance_);
    }

private:

    /*
     * Private methods
     */

    /** Read an instance from a file in 'cvrplib' format. */
    void read_cvrplib(std::ifstream& file)
    {
        travelingsalesmansolver::DistancesBuilder distances_builder;

        std::string tmp;
        std::vector<std::string> line;
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
                LocationId j_tmp;
                file >> j_tmp >> j_tmp;
            } else if (tmp.rfind("DIMENSION", 0) == 0) {
                LocationId number_of_locations = std::stol(line.back());
                set_number_of_locations(number_of_locations);
                distances_builder.add_vertices(number_of_locations);
            } else if (tmp.rfind("CAPACITY", 0) == 0) {
                Demand c = std::stol(line.back());
                set_location_demand(0, c);
            } else if (tmp.rfind("DEMAND_SECTION", 0) == 0) {
                LocationId j_tmp = -1;
                Demand demand = -1;
                for (LocationId location_id = 0;
                        location_id < instance_.number_of_locations();
                        ++location_id) {
                    file >> j_tmp >> demand;
                    if (location_id != 0)
                        set_location_demand(location_id, demand);
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
