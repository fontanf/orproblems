#pragma once

#include "optimizationtools/utils.hpp"

/**
 * Capacitated Open Vehicle Routing Problem.
 *
 * Input:
 * - m vehicles of capacity Q
 * - A maximum route length L
 * - 1 depot
 * - n - 1 customer with demand qⱼ (j = 2..n)
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


namespace orproblems
{

namespace capacitatedopenvehiclerouting
{

typedef int64_t LocationId;
typedef int64_t VehicleId;
typedef int64_t RouteId;
typedef int64_t Demand;
typedef double Distance;

struct Location
{
    double x;
    double y;
    Demand demand;
};

class Instance
{

public:

    Instance(LocationId n):
        locations_(n),
        distances_(n, std::vector<Distance>(n, -1)),
        vehicle_number_(n) { }
    void set_vehicle_number(VehicleId m) { vehicle_number_ = m; }
    void set_maximum_route_length(Distance maximum_route_length) { maximum_route_length_ = maximum_route_length; }
    void set_demand(LocationId j, Demand q) { locations_[j].demand = q; }
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
            std::cerr << "\033[31m" << "ERROR, unable to open file \"" << instance_path << "\"" << "\033[0m" << std::endl;
            assert(false);
            return;
        }
        if (format == "" || format == "vrplib") {
            read_vrplib(file);
        } else {
            std::cerr << "\033[31m" << "ERROR, unknown instance format \"" << format << "\"" << "\033[0m" << std::endl;
        }
        file.close();
    }

    virtual ~Instance() { }

    VehicleId vehicle_number() const { return vehicle_number_; }
    LocationId location_number() const { return locations_.size(); }
    Distance maximum_route_length() const { return maximum_route_length_; }
    Demand capacity() const { return locations_[0].demand; }
    Demand demand(LocationId j) const { return locations_[j].demand; }
    Distance x(LocationId j) const { return locations_[j].x; }
    Distance y(LocationId j) const { return locations_[j].y; }
    Distance distance(LocationId j1, LocationId j2) const { return distances_[j1][j2]; }
    Distance maximum_distance() const { return distance_max_; }
    Distance bound() const { return powf(10.0f, ceil(log10f(location_number() * maximum_distance()))); }

private:

    void read_vrplib(std::ifstream& file)
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
                vehicle_number_ = n;
            } else if (tmp.rfind("EDGE_WEIGHT_TYPE", 0) == 0) {
                edge_weight_type = line.back();
            } else if (tmp.rfind("DISTANCE", 0) == 0) {
                Distance l = std::stol(line.back());
                set_maximum_route_length(l * 0.9);
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
                    //Distance d = std::round(std::sqrt(xd * xd + yd * yd));
                    Distance d = std::sqrt(xd * xd + yd * yd);
                    set_distance(j1, j2, d);
                }
            }
        } else {
            std::cerr << "\033[31m" << "ERROR, EDGE_WEIGHT_TYPE \"" << edge_weight_type << "\" not implemented." << "\033[0m" << std::endl;
        }
    }

    std::vector<Location> locations_;
    std::vector<std::vector<Distance>> distances_;
    VehicleId vehicle_number_ = 0;
    Distance maximum_route_length_ = std::numeric_limits<Distance>::infinity();;
    Distance distance_max_ = 0;

};

static std::ostream& operator<<(std::ostream &os, const Instance& instance)
{
    os << "location number " << instance.location_number() << std::endl;
    os << "vehicle number " << instance.vehicle_number() << std::endl;
    os << "capacity " << instance.capacity() << std::endl;
    os << "maximum route length " << instance.maximum_route_length() << std::endl;
    os << "bound " << instance.bound() << std::endl;
    for (LocationId j = 0; j < instance.location_number(); ++j)
        os << "location " << j
            << " d " << instance.demand(j)
            << std::endl;
    return os;
}

}

}
