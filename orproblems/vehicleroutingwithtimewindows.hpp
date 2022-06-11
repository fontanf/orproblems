/**
 * Vehicle Routing Problem with Time Windows.
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

typedef int64_t LocationId;
typedef int64_t LocationPos;
typedef int64_t RouteId;
typedef double Demand;
//typedef double Time;
typedef int64_t Time;

struct Location
{
    double x;
    double y;
    Demand demand;
    Time release_date = 0;
    Time deadline = 0;
    Time service_time = 0;
};

class Instance
{

public:

    Instance(LocationId n):
        locations_(n),
        travel_times_(n, std::vector<Time>(n, -1)) { }
    void set_number_of_vehicles(RouteId m) { number_of_vehicles_ = m; }
    void set_capacity(Demand capacity) { locations_[0].demand = capacity; }
    void set_location(
            LocationId j,
            Demand demand,
            Time release_date,
            Time deadline,
            Time service_time)
    {
        locations_[j].demand = demand;
        locations_[j].release_date = release_date;
        locations_[j].deadline = deadline;
        locations_[j].service_time = service_time;
        service_maximum_travel_time_ = std::max(service_maximum_travel_time_, service_time);
    }
    void set_xy(LocationId j, double x, double y)
    {
        locations_[j].x = x;
        locations_[j].y = y;
    }
    void set_travel_time(LocationId j1, LocationId j2, Time d)
    {
        travel_times_[j1][j2] = d;
        travel_times_[j2][j1] = d;
        maximum_travel_time_ = std::max(maximum_travel_time_, d);
    }

    Instance(std::string instance_path, std::string format = "")
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

    virtual ~Instance() { }

    RouteId number_of_vehicles() const { return number_of_vehicles_; }
    LocationId number_of_locations() const { return locations_.size(); }
    Demand capacity() const { return locations_[0].demand; }
    inline const Location& location(LocationId j) const { return locations_[j]; }
    Time travel_time(LocationId j1, LocationId j2) const { return travel_times_[j1][j2]; }
    Time maximum_travel_time() const { return maximum_travel_time_; }
    Time maximum_service_time() const { return service_maximum_travel_time_; }

    std::ostream& print(
            std::ostream& os,
            int verbose = 1) const
    {
        if (verbose >= 1) {
            os << "Number of vehicles:   " << number_of_vehicles() << std::endl;
            os << "Number of locations:  " << number_of_locations() << std::endl;
            os << "Capacity:             " << capacity() << std::endl;
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
                    << std::setw(12) << location(j1).demand
                    << std::setw(12) << location(j1).service_time
                    << std::setw(12) << location(j1).release_date
                    << std::setw(12) << location(j1).deadline
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
                    os << " " << travel_time(j1, j2);
                os << std::endl;
            }
        }
        return os;
    }

    std::pair<bool, Time> check(
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
                << std::setw(12) << "Rel. date"
                << std::setw(12) << "Deadline"
                << std::setw(12) << "Travel time"
                << std::setw(12) << "Serv. time"
                << std::setw(12) << "Route dem."
                << std::setw(12) << "Time"
                << std::setw(12) << "Route tr."
                << std::endl
                << std::setw(10) << "--------"
                << std::setw(12) << "------"
                << std::setw(12) << "---------"
                << std::setw(12) << "--------"
                << std::setw(12) << "-----------"
                << std::setw(12) << "----------"
                << std::setw(12) << "----------"
                << std::setw(12) << "----"
                << std::setw(12) << "---------"
                << std::endl;
        }

        LocationId n = number_of_locations();
        optimizationtools::IndexedSet visited_locations(n);
        LocationPos number_of_duplicates = 0;
        LocationPos route_number_of_locations = -1;
        LocationPos number_of_late_visits = 0;
        RouteId number_of_routes = 0;
        RouteId number_of_overloaded_vehicles = 0;
        Time total_travel_time = 0;
        while (file >> route_number_of_locations) {
            if (route_number_of_locations == 0)
                continue;
            Time current_time = 0;
            Time route_travel_time = 0;
            Demand demand = 0;
            LocationId j_prev = 0;
            LocationId j = -1;
            for (LocationPos pos = 0; pos <= route_number_of_locations; ++pos) {
                if (pos < route_number_of_locations) {
                    file >> j;
                    if (visited_locations.contains(j)) {
                        number_of_duplicates++;
                        if (verbose >= 2)
                            os << "Location " << j << " has already been visited." << std::endl;
                    }
                    visited_locations.add(j);
                    demand += location(j).demand;
                } else {
                    j = 0;
                }
                current_time += travel_time(j_prev, j);
                if (current_time < location(j).release_date)
                    current_time = location(j).release_date;
                if (current_time > location(j).deadline)
                    number_of_late_visits++;
                route_travel_time += travel_time(j_prev, j);
                if (verbose >= 2) {
                    os
                        << std::setw(10) << j
                        << std::setw(12) << location(j).demand
                        << std::setw(12) << location(j).release_date
                        << std::setw(12) << location(j).deadline
                        << std::setw(12) << travel_time(j_prev, j)
                        << std::setw(12) << location(j).service_time
                        << std::setw(12) << demand
                        << std::setw(12) << current_time
                        << std::setw(12) << route_travel_time
                        << std::endl;
                }
                current_time += location(j).service_time;
                j_prev = j;
            }
            if (j_prev != 0)
                route_travel_time += travel_time(j_prev, 0);
            total_travel_time += route_travel_time;
            if (verbose >= 2) {
                os << "Route " << number_of_routes
                    << "; demand: " << demand
                    << "; travel time: " << route_travel_time
                    << "; total travel time: " << total_travel_time
                    << "." << std::endl;
            }
            number_of_routes++;
            if (demand > capacity())
                number_of_overloaded_vehicles++;
        }

        bool feasible
            = (visited_locations.size() == n - 1)
            && (!visited_locations.contains(0))
            && (number_of_duplicates == 0)
            && (number_of_routes <= number_of_vehicles())
            && (number_of_overloaded_vehicles == 0)
            && (number_of_late_visits == 0);
        if (verbose == 2)
            os << std::endl;
        if (verbose >= 1) {
            os << "Number of visited locations:    " << visited_locations.size() << " / " << n - 1 << std::endl;
            os << "Number of duplicates:           " << number_of_duplicates << std::endl;
            os << "Number of routes:               " << number_of_routes << " / " << number_of_vehicles() << std::endl;
            os << "Number of overloaded vehicles:  " << number_of_overloaded_vehicles << std::endl;
            os << "Number of late visits:          " << number_of_late_visits << std::endl;
            os << "Feasible:                       " << feasible << std::endl;
            os << "Total travel time:              " << total_travel_time << std::endl;
        }
        return {feasible, total_travel_time};
    }

private:

    void read_dimacs2021(std::ifstream& file)
    {
        std::string tmp;
        file >> tmp >> tmp >> tmp >> tmp;

        // Read number of locations.
        RouteId m = -1;
        file >> m;
        set_number_of_vehicles(m);

        // Read capacity.
        Demand capacity = -1;
        file >> capacity;

        file
            >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp
            >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp
            ;

        // Read locations.
        LocationId j;
        double x = -1;
        double y = -1;
        Demand demand = -1;
        Time release_date = -1;
        Time deadline = -1;
        Time service_time = -1;
        while (file >> j >> x >> y >> demand >> release_date >> deadline >> service_time) {
            locations_.push_back({});
            set_xy(j, x, y);
            //set_location(j, demand, release_date, deadline, service_time);
            set_location(j, demand, 10 * release_date, 10 * deadline, 10 * service_time);
        }
        set_capacity(capacity);
        LocationId n = locations_.size();

        // Compute times.
        travel_times_.resize(n, std::vector<Time>(n, -1));
        for (LocationId j1 = 0; j1 < n; ++j1) {
            for (LocationId j2 = j1 + 1; j2 < n; ++j2) {
                double xd = location(j2).x - location(j1).x;
                double yd = location(j2).y - location(j1).y;
                double e = std::sqrt(xd * xd + yd * yd);
                //Time d = std::round(e * 10) / 10;
                Time d = std::floor(e * 10);
                set_travel_time(j1, j2, d);
            }
        }
    }

    std::vector<Location> locations_;
    std::vector<std::vector<Time>> travel_times_;
    RouteId number_of_vehicles_ = 0;
    Time maximum_travel_time_ = 0;
    Time service_maximum_travel_time_ = 0;

};

}

}
