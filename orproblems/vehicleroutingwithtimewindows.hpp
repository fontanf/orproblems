#pragma once

#include "optimizationtools/utils.hpp"

#include "pugixml.hpp"

/**
 * Vehicle Routing Problem with Time Windows.
 *
 * Input:
 * - m vehicles of capacity Q
 * - 1 depot
 * - n - 1 customer with a demand qⱼ, a service time sⱼ and a time window [rⱼ,
 *   dⱼ] (j = 2..n)
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


namespace orproblems
{

namespace vehicleroutingwithtimewindows
{

typedef int64_t LocationId;
typedef int64_t VehicleId;
typedef int64_t RouteId;
typedef double Demand;
typedef double Time;

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
        times_(n, std::vector<Time>(n, -1)) { }
    void set_vehicle_number(VehicleId m) { vehicle_number_ = m; }
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
        service_time_max_ = std::max(service_time_max_, service_time);
    }
    void set_xy(LocationId j, double x, double y)
    {
        locations_[j].x = x;
        locations_[j].y = y;
    }
    void set_time(LocationId j1, LocationId j2, Time d)
    {
        times_[j1][j2] = d;
        times_[j2][j1] = d;
        time_max_ = std::max(time_max_, d);
    }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            std::cerr << "\033[31m" << "ERROR, unable to open file \"" << instance_path << "\"" << "\033[0m" << std::endl;
            assert(false);
            return;
        }
        if (format == "" || format == "dimacs2021") {
            read_dimacs2021(file);
        } else if (format == "vrprep") {
            read_vrprep(file);
        } else {
            std::cerr << "\033[31m" << "ERROR, unknown instance format \"" << format << "\"" << "\033[0m" << std::endl;
        }
        file.close();
    }

    virtual ~Instance() { }

    VehicleId vehicle_number() const { return vehicle_number_; }
    LocationId location_number() const { return locations_.size(); }
    Demand capacity() const { return locations_[0].demand; }
    inline const Location& location(LocationId j) const { return locations_[j]; }
    Time time(LocationId j1, LocationId j2) const { return times_[j1][j2]; }
    Time maximum_time() const { return time_max_; }
    Time maximum_service_time() const { return service_time_max_; }

private:

    void read_dimacs2021(std::ifstream& file)
    {
        std::string tmp;
        file >> tmp >> tmp >> tmp >> tmp;

        // Read location number.
        VehicleId m = -1;
        file >> m;
        set_vehicle_number(m);

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
            set_location(j, demand, release_date, deadline, service_time);
        }
        set_capacity(capacity);
        LocationId n = locations_.size();

        // Compute times.
        times_.resize(n, std::vector<Time>(n, -1));
        for (LocationId j1 = 0; j1 < n; ++j1) {
            for (LocationId j2 = j1 + 1; j2 < n; ++j2) {
                double xd = location(j2).x - location(j1).x;
                double yd = location(j2).y - location(j1).y;
                double d = std::sqrt(xd * xd + yd * yd);
                d = std::round(d * 10) / 10;
                set_time(j1, j2, d);
            }
        }
    }

    void read_vrprep(std::ifstream& file)
    {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load(file);
        if (!result) {
            std::cerr << "\033[31m" << "ERROR, XML parsed with errors \"" << result.description() << "\"" << "\033[0m" << std::endl;
            return;
        }

        // Number of locations.
        LocationId n = 0;
        for (pugi::xml_node child = doc.child("instance").child("network").child("nodes").first_child();
                child; child = child.next_sibling())
            n++;
        locations_.resize(n),
        times_.resize(n, std::vector<Time>(n, -1));

        // Coordinates.
        for (pugi::xml_node child = doc.child("instance").child("network").child("nodes").first_child();
                child; child = child.next_sibling()) {
            LocationId j = child.attribute("id").as_int();
            double x = std::stod(child.child("cx").child_value());
            double y = std::stod(child.child("cy").child_value());
            set_xy(j, x, y);
        }

        // Location attributes.
        for (pugi::xml_node child = doc.child("instance").child("requests").first_child();
                child; child = child.next_sibling()) {
            LocationId j = child.attribute("node").as_int();
            Demand demand = std::stod(child.child("quantity").child_value());
            Time release_date = std::stod(child.child("tw").child("start").child_value());
            Time deadline = std::stod(child.child("tw").child("end").child_value());
            Time service_time = std::stod(child.child("service_time").child_value());
            set_location(j, demand, release_date, deadline, service_time);
        }

        // Vehicle number.
        VehicleId m = doc.child("instance").child("fleet").child("vehicle_profile").attribute("number").as_int();
        set_vehicle_number(m);
        // Vehicle capacity.
        Demand c = std::stod(doc.child("instance").child("fleet").child("vehicle_profile").child("capacity").child_value());
        set_capacity(c);

        // Compute times.
        if (doc.child("instance").child("network").child("euclidean")) {
            double dec = std::stod(doc.child("instance").child("network").child("decimals").child_value());
            for (LocationId j1 = 0; j1 < n; ++j1) {
                for (LocationId j2 = j1 + 1; j2 < n; ++j2) {
                    double xd = location(j2).x - location(j1).x;
                    double yd = location(j2).y - location(j1).y;
                    double d = std::sqrt(xd * xd + yd * yd);
                    d = std::round(d * std::pow(10, dec)) / std::pow(10, dec);
                    set_time(j1, j2, d);
                }
            }
        } else {
            std::cerr << "\033[31m" << "ERROR, computing times." << "\033[0m" << std::endl;
        }
    }

    std::vector<Location> locations_;
    std::vector<std::vector<Time>> times_;
    VehicleId vehicle_number_ = 0;
    Time time_max_ = 0;
    Time service_time_max_ = 0;

};

}

}
