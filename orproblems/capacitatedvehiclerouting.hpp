/**
 * Capacitated Vehicle Routing Problem.
 *
 * Input:
 * - vehicles of capacity Q
 * - 1 depot
 * - n - 1 customers; for each customer j = 2..n, a demand qⱼ
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

typedef int64_t LocationId;
typedef int64_t LocationPos;
typedef int64_t RouteId;
typedef int64_t Demand;
typedef int64_t Distance;
typedef int64_t RouteId;

struct Location
{
    double x;
    double y;
    Demand demand = 0;
};

class Instance
{

public:

    Instance(LocationId n):
        locations_(n),
        distances_(n, std::vector<Distance>(n, -1)) { }
    void set_demand(LocationId j, Demand q)
    {
        if (j != 0)
            total_demand_ -= locations_[j].demand;
        locations_[j].demand = q;
        if (j != 0)
            total_demand_ += locations_[j].demand;
    }
    void set_xy(LocationId j, double x, double y)
    {
        locations_[j].x = x;
        locations_[j].y = y;
    }
    void set_distance(LocationId j1, LocationId j2, Distance d)
    {
        distances_[j1][j2] = d;
        distances_[j2][j1] = d;
        distance_max_ = std::max(distance_max_, d);
    }

    Instance(std::string instance_path, std::string format = "")
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

    virtual ~Instance() { }

    LocationId number_of_locations() const { return locations_.size(); }
    Demand capacity() const { return locations_[0].demand; }
    Demand total_demand() const { return total_demand_; }
    Demand demand(LocationId j) const { return locations_[j].demand; }
    Distance x(LocationId j) const { return locations_[j].x; }
    Distance y(LocationId j) const { return locations_[j].y; }
    Distance distance(LocationId j1, LocationId j2) const { return distances_[j1][j2]; }
    Distance maximum_distance() const { return distance_max_; }

    std::ostream& print(
            std::ostream& os,
            int verbose = 1) const
    {
        if (verbose >= 1) {
            os << "Number of locations:  " << number_of_locations() << std::endl;
            os << "Capacity:             " << capacity() << std::endl;
            os << "Total demand:         " << total_demand() << std::endl;
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
            for (LocationId j1 = 0; j1 < number_of_locations(); ++j1) {
                os << std::setw(12) << j1
                    << std::setw(12) << demand(j1)
                    << std::endl;
            }
            os << std::endl
                << std::setw(12) << "Location"
                << "    Travel times"
                << std::endl
                << std::setw(12) << "---------"
                << "    ------------"
                << std::endl;
            for (LocationId j1 = 0; j1 < number_of_locations(); ++j1) {
                os << std::setw(12) << j1
                    << "   ";
                for (LocationId j2 = 0; j2 < number_of_locations(); ++j2)
                    os << " " << distance(j1, j2);
                os << std::endl;
            }
        }
        return os;
    }

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
                << std::setw(10) << "Location"
                << std::setw(12) << "Demand"
                << std::setw(12) << "Distance"
                << std::setw(12) << "Route dem."
                << std::setw(12) << "Tot. dist."
                << std::setw(12) << "Route dist."
                << std::endl
                << std::setw(10) << "--------"
                << std::setw(12) << "------"
                << std::setw(12) << "--------"
                << std::setw(12) << "----------"
                << std::setw(12) << "----------"
                << std::setw(12) << "-----------"
                << std::endl;
        }

        LocationId n = number_of_locations();
        optimizationtools::IndexedSet visited_locations(n);
        LocationPos number_of_duplicates = 0;
        LocationPos route_number_of_locations = -1;
        RouteId number_of_routes = 0;
        RouteId number_of_overloaded_vehicles = 0;
        Distance total_distance = 0;
        while (file >> route_number_of_locations) {
            if (route_number_of_locations == 0)
                continue;
            Distance route_distance = 0;
            Demand route_demand = 0;
            LocationId j_prev = 0;
            LocationId j = -1;
            for (LocationPos pos = 0; pos < route_number_of_locations; ++pos) {
                file >> j;
                if (visited_locations.contains(j)) {
                    number_of_duplicates++;
                    if (verbose >= 2)
                        os << "Location " << j << " has already been visited." << std::endl;
                }
                visited_locations.add(j);
                route_demand += demand(j);
                route_distance += distance(j_prev, j);
                total_distance += distance(j_prev, j);
                if (verbose >= 2) {
                    os
                        << std::setw(10) << j
                        << std::setw(12) << demand(j)
                        << std::setw(12) << distance(j_prev, j)
                        << std::setw(12) << route_demand
                        << std::setw(12) << route_distance
                        << std::setw(12) << total_distance
                        << std::endl;
                }
                j_prev = j;
            }
            if (j_prev != 0) {
                route_distance += distance(j_prev, 0);
                total_distance += distance(j_prev, 0);
            }
            if (verbose >= 2) {
                os << "Route " << number_of_routes
                    << "; demand: " << route_demand
                    << "; travel time: " << route_distance
                    << "; total travel time: " << total_distance
                    << "." << std::endl;
            }
            number_of_routes++;
            if (route_demand > capacity())
                number_of_overloaded_vehicles++;
        }

        bool feasible
            = (visited_locations.size() == n - 1)
            && (!visited_locations.contains(0))
            && (number_of_duplicates == 0)
            && (number_of_overloaded_vehicles == 0);
        if (verbose == 2)
            os << std::endl;
        if (verbose >= 1) {
            os << "Number of visited locations:    " << visited_locations.size() << " / " << n - 1 << std::endl;
            os << "Number of duplicates:           " << number_of_duplicates << std::endl;
            os << "Number of routes:               " << number_of_routes << std::endl;
            os << "Number of overloaded vehicles:  " << number_of_overloaded_vehicles << std::endl;
            os << "Feasible:                       " << feasible << std::endl;
            os << "Total distance:                 " << total_distance << std::endl;
        }
        return {feasible, total_distance};
    }

private:

    void read_cvrplib(std::ifstream& file)
    {
        std::string tmp;
        std::vector<std::string> line;
        LocationId n = -1;
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
                n = std::stol(line.back());
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
                for (LocationId j = 0; j < n; ++j) {
                    file >> j_tmp >> x >> y;
                    set_xy(j, x, y);
                }
            } else if (tmp.rfind("DEMAND_SECTION", 0) == 0) {
                LocationId j_tmp = -1;
                Demand demand = -1;
                for (LocationId j = 0; j < n; ++j) {
                    file >> j_tmp >> demand;
                    if (j != 0)
                        set_demand(j, demand);
                }
            } else if (line[0].rfind("EOF", 0) == 0) {
                break;
            } else {
                std::cerr << "\033[31m" << "ERROR, ENTRY \"" << line[0] << "\" not implemented." << "\033[0m" << std::endl;
            }
        }

        // Compute distances.
        if (edge_weight_type == "EUC_2D") {
            for (LocationId j1 = 0; j1 < n; ++j1) {
                for (LocationId j2 = j1 + 1; j2 < n; ++j2) {
                    double xd = x(j2) - x(j1);
                    double yd = y(j2) - y(j1);
                    Distance d = std::round(std::sqrt(xd * xd + yd * yd));
                    set_distance(j1, j2, d);
                }
            }
        } else {
            std::cerr << "\033[31m" << "ERROR, EDGE_WEIGHT_TYPE \"" << edge_weight_type << "\" not implemented." << "\033[0m" << std::endl;
        }
    }

    std::vector<Location> locations_;
    std::vector<std::vector<Distance>> distances_;
    Demand total_demand_ = 0;
    Distance distance_max_ = 0;

};

}

}
