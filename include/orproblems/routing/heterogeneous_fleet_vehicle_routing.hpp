/**
 * Heterogeneous fleet vehicle routing problem
 *
 * Input:
 * - m vehicle types; for each vehicle i = 1..m
 *   - a number of vehicles mᵢ
 *   - a capacity Qᵢ
 *   - a fixed cost fᵢ
 *   - a variable cost rᵢ
 * - 1 depot
 * - n - 1 customers; for each customer location_id = 2..n, a demand qⱼ
 * - A n×n symmetric matrix d specifying the distances to travel between each
 *   pair of locations
 * Problem:
 * - find a set of routes that begin and end at the depot, such that each
 *   customer is visited on exactly one route and the total demand of the
 *   customers assigned to a route does not exceed the vehicle type capacity.
 * Objective:
 * - Minimize the total cost of the routes. The cost of a route contains:
 *   - The fixed cost the vehicle type used
 *   - The product of the variable cost of the vehicle type used with the
 *     length of the route
 *
 */

#pragma once

#include "optimizationtools/containers/indexed_set.hpp"
#include "optimizationtools/utils/utils.hpp"

#include "travelingsalesmansolver/distances/distances_builder.hpp"

#include <iostream>
#include <fstream>
#include <memory>
#include <iomanip>

namespace orproblems
{
namespace heterogeneous_fleet_vehicle_routing
{

using LocationId = int64_t;
using LocationPos = int64_t;
using VehicleTypeId = int64_t;
using RouteId = int64_t;
using Demand = int64_t;
using Distance = int64_t;
using Cost = int64_t;

/**
 * Structure for a vehicle type.
 */
struct VehicleType
{
    /** Number of vehicles. */
    RouteId number_of_vehicles = -1;

    /** Capacity. */
    Demand capacity = 0;

    /** Fixed cost. */
    Cost fixed_cost = 0;

    /** Variable cost. */
    Cost variable_cost = 1;
};

/**
 * Instance class for a 'heterogeneous_fleet_vehicle_routing' problem.
 */
class Instance
{

public:

    /*
     * Getters
     */

    /** Get the number of locations. */
    inline LocationId number_of_locations() const { return demands_.size(); }

    /** Get the total demand. */
    inline Demand total_demand() const { return total_demand_; }

    /** Get the demand of a location. */
    inline Demand demand(LocationId location_id) const { return demands_[location_id]; }

    /** Get distances. */
    const travelingsalesmansolver::Distances& distances() const { return *distances_; }

    /** Get the number of vehicle types. */
    VehicleTypeId number_of_vehicle_types() const { return vehicle_types_.size(); }

    /** Get a vehicle type. */
    const VehicleType& vehicle_type(VehicleTypeId vehicle_type_id) const { return vehicle_types_[vehicle_type_id]; }

    /** Get the number of vehicle. */
    RouteId number_of_vehicles() const { return vehicle_type_ids_.size(); }

    /** Get the type of a vehicle. */
    VehicleTypeId vehicle_type_id(RouteId vehicle_pos) const { return vehicle_type_ids_[vehicle_pos]; }

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
                << "Number of locations:      " << number_of_locations() << std::endl
                << "Number of vehicle types:  " << number_of_vehicle_types() << std::endl
                << "Total demand:             " << total_demand() << std::endl
                << "Demand ratio:             " << (double)total_demand() << std::endl
                ;
        }

        if (verbosity_level >= 2) {
            os << std::endl
                << std::setw(12) << "Veh. type"
                << std::setw(12) << "# vehicles"
                << std::setw(12) << "Capacity"
                << std::setw(12) << "Fixed cost"
                << std::setw(12) << "Var. cost"
                << std::endl
                << std::setw(12) << "---------"
                << std::setw(12) << "----------"
                << std::setw(12) << "--------"
                << std::setw(12) << "----------"
                << std::setw(12) << "---------"
                << std::endl;
            for (VehicleTypeId vehicle_type_id = 0;
                    vehicle_type_id < number_of_vehicle_types();
                    ++vehicle_type_id) {
                const VehicleType& vehicle_type = this->vehicle_type(vehicle_type_id);
                os << std::setw(12) << vehicle_type_id
                    << std::setw(12) << vehicle_type.number_of_vehicles
                    << std::setw(12) << vehicle_type.capacity
                    << std::setw(12) << vehicle_type.fixed_cost
                    << std::setw(12) << vehicle_type.variable_cost
                    << std::endl;
            }
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
                << std::setw(12) << "Tot. cost"
                << std::endl
                << std::setw(10) << "-----"
                << std::setw(10) << "--------"
                << std::setw(12) << "----------"
                << std::setw(12) << "-----------"
                << std::setw(12) << "----------"
                << std::setw(12) << "---------"
                << std::endl;
        }

        optimizationtools::IndexedSet visited_locations(number_of_locations());
        RouteId number_of_routes = 0;

        LocationPos number_of_duplicates = 0;
        RouteId number_of_overloaded_vehicles = 0;

        Distance total_distance = 0;
        Cost total_fixed_cost = 0;
        Cost total_variable_cost = 0;
        Cost total_cost = 0;
        file >> number_of_routes;
        for (RouteId route_id = 0; route_id < number_of_routes; ++route_id) {

            VehicleTypeId vehicle_type_id = -1;
            file >> vehicle_type_id;
            const VehicleType& vehicle_type = this->vehicle_type(vehicle_type_id);

            total_fixed_cost += vehicle_type.fixed_cost;
            total_cost += vehicle_type.fixed_cost;

            LocationPos route_number_of_locations = -1;
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
                route_distance += distances.distance(location_id_prev, location_id);
                total_distance += distances.distance(location_id_prev, location_id);
                total_variable_cost += vehicle_type.variable_cost * distances.distance(location_id_prev, location_id);
                total_cost += vehicle_type.variable_cost * distances.distance(location_id_prev, location_id);

                if (verbosity_level >= 2) {
                    os
                        << std::setw(10) << route_id
                        << std::setw(10) << location_id
                        << std::setw(12) << route_demand
                        << std::setw(12) << route_distance
                        << std::setw(12) << total_distance
                        << std::setw(12) << total_cost
                        << std::endl;
                }

                location_id_prev = location_id;
            }
            if (location_id_prev != 0) {
                route_distance += distances.distance(location_id_prev, 0);
                total_distance += distances.distance(location_id_prev, 0);
                total_variable_cost += vehicle_type.variable_cost * distances.distance(location_id_prev, 0);
                total_cost += vehicle_type.variable_cost * distances.distance(location_id_prev, 0);
            }

            if (verbosity_level >= 2) {
                os
                    << std::setw(10) << route_id
                    << std::setw(10) << 0
                    << std::setw(12) << route_demand
                    << std::setw(12) << route_distance
                    << std::setw(12) << total_distance
                    << std::setw(12) << total_cost
                    << std::endl;
            }

            // Check vehicle capacity.
            if (route_demand > vehicle_type.capacity)
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
                << "Total fixed cost:               " << total_fixed_cost << std::endl
                << "Total variable cost:            " << total_variable_cost << std::endl
                << "Total cost:                     " << total_cost << std::endl
                ;
        }
        return {feasible, total_cost};
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

    /** Vehicle types. */
    std::vector<VehicleType> vehicle_types_;

    /*
     * Computed attributes
     */

    /** Total demand. */
    Demand total_demand_ = 0;

    /** Vehicle type ids. */
    std::vector<VehicleTypeId> vehicle_type_ids_;

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

    VehicleTypeId add_vehicle_type()
    {
        VehicleType vehicle_type;
        instance_.vehicle_types_.push_back(vehicle_type);
        return instance_.vehicle_types_.size() - 1;
    }

    /** Set the number of vehicles of a vehicle type. */
    void set_vehicle_type_number_of_vehicles(
            VehicleTypeId vehicle_type_id,
            RouteId number_of_vehicles)
    {
        instance_.vehicle_types_[vehicle_type_id].number_of_vehicles = number_of_vehicles;
    }

    /** Set the capacity of a vehicle type. */
    void set_vehicle_type_capacity(
            VehicleTypeId vehicle_type_id,
            Demand capacity)
    {
        instance_.vehicle_types_[vehicle_type_id].capacity = capacity;
    }

    /** Set the fixed cost of a vehicle type. */
    void set_vehicle_type_fixed_cost(
            VehicleTypeId vehicle_type_id,
            Cost fixed_cost)
    {
        instance_.vehicle_types_[vehicle_type_id].fixed_cost = fixed_cost;
    }

    /** Set the variable cost of a vehicle type. */
    void set_vehicle_type_variable_cost(
            VehicleTypeId vehicle_type_id,
            Cost variable_cost)
    {
        instance_.vehicle_types_[vehicle_type_id].variable_cost = variable_cost;
    }

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

        // Compute vehicle_type_ids_.
        for (VehicleTypeId vehicle_type_id = 0;
                vehicle_type_id < instance_.number_of_vehicle_types();
                ++vehicle_type_id) {
            if (instance_.vehicle_type(vehicle_type_id).number_of_vehicles == -1) {
                instance_.vehicle_types_[vehicle_type_id].number_of_vehicles
                    = instance_.number_of_locations();
            }
            for (RouteId vehicle_pos = 0;
                    vehicle_pos < instance_.vehicle_type(vehicle_type_id).number_of_vehicles;
                    ++vehicle_pos) {
                instance_.vehicle_type_ids_.push_back(vehicle_type_id);
            }
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
            } else if (tmp.rfind("NAME", 0) == 0) {
            } else if (tmp.rfind("COMMENT", 0) == 0) {
            } else if (tmp.rfind("TYPE", 0) == 0) {
            } else if (tmp.rfind("DEPOT_SECTION", 0) == 0) {
                LocationId location_id_tmp;
                file >> location_id_tmp >> location_id_tmp;
            } else if (tmp.rfind("DIMENSION", 0) == 0) {
                LocationId number_of_locations = std::stol(line.back());
                set_number_of_locations(number_of_locations);
                distances_builder.set_number_of_vertices(number_of_locations);
            } else if (tmp.rfind("CAPACITY", 0) == 0) {
                Demand capacity = std::stol(line.back());
                set_location_demand(0, capacity);
            } else if (tmp.rfind("DEMAND_SECTION", 0) == 0) {
                LocationId location_id_tmp = -1;
                Demand demand = -1;
                for (LocationId location_id = 0;
                        location_id < instance_.number_of_locations();
                        ++location_id) {
                    file >> location_id_tmp >> demand;
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
