/**
 * Thief orienterring problem.
 *
 * Input:
 * - n cities and an n×n symmetric matrix d containing the distances between
 *   each pair of cities
 * - m items; for each item i = 1..m
 *   - a profit pᵢ
 *   - a weight wᵢ
 *   - a location nᵢ
 * - A time limit T
 * - A capacity c
 * - A maximum speed vmax and a minimum speed vmin such that the time to travel
 *   from city location_id_1 to city location_id_2 is equal to:
 *       d(location_id_1, location_id_2) / (vmax - w * (vmax - vmin) / c)
 *   with w the sum of the weights of the currently collected items
 * Problem:
 * - find a route from city 1 to city n and a set of items to collect such
 *   that:
 *   - an item can only be collected in the city in which it is located
 *   - the total weight of the collected items does not exceed the capacity
 *   - the total time of the route does not exceed the time limit
 * Objective:
 * - maximize the profit of collected items
 *
 */

#pragma once

#include "optimizationtools/utils/utils.hpp"
#include "optimizationtools/containers/indexed_set.hpp"
#include "optimizationtools/containers/sorted_on_demand_array.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>

namespace orproblems
{

namespace thieforienteering
{

using LocationId = int64_t;
using Distance = int64_t;
using Time = double;
using ItemId = int64_t;
using ItemPos = int64_t;
using Profit = int64_t;
using Weight = int64_t;

/**
 * Structure for an item.
 */
struct Item
{
    /** Profit of the item. */
    Profit profit;

    /** Weight of the item. */
    Weight weight;

    /** Location of the item. */
    LocationId location_id;
};

/**
 * Structure for a location.
 */
struct Location
{
    /** x-coordinate. */
    double x;

    /** y-coordinate. */
    double y;

    /** z-coordinate. */
    double z;

    /** Items available at the location. */
    std::vector<ItemId> item_ids;
};

/**
 * Instance class for a 'thieforienteering' problem.
 */
class Instance
{

public:

    /*
     * Constructors and destructor
     */

    /** Constructor to build an instance manually. */
    Instance(LocationId n):
        locations_(n),
        distances_(n, std::vector<Distance>(n, -1))
    {
        for (LocationId location_id = 0;
                location_id < n;
                ++location_id) {
            distances_[location_id][location_id] = 0;
        }
    }

    /** Set the time limit. */
    void set_time_limit(Time time_limit)
    {
        time_limit_ = time_limit;
    }

    /** Set the coordinates of a location. */
    void set_xy(
            LocationId location_id,
            double x,
            double y,
            double z = -1)
    {
        locations_[location_id].x = x;
        locations_[location_id].y = y;
        locations_[location_id].z = z;
    }

    /** Set the distance between two locations. */
    void set_distance(
            LocationId location_id_1,
            LocationId location_id_2,
            Distance distance)
    {
        distances_[location_id_1][location_id_2] = distance;
        distances_[location_id_2][location_id_1] = distance;
        distance_max_ = std::max(distance_max_, distance);
    }

    /** Set the minimum speed. */
    void set_minimum_speed(double minimum_speed)
    {
        speed_min_ = minimum_speed;
    }

    /** Set the maximum speed. */
    void set_maximum_speed(double maximum_speed)
    {
        speed_max_ = maximum_speed;
    }

    /** Set the capacity of the knapsack. */
    void set_capacity(Weight capacity)
    {
        capacity_ = capacity;
    }

    /** Add an item. */
    void add_item(
            LocationId location_id,
            Profit profit,
            Weight weight)
    {
        ItemId item_id = items_.size();
        locations_[location_id].item_ids.push_back(item_id);

        Item item;
        item.location_id = location_id;
        item.profit = profit;
        item.weight = weight;
        items_.push_back(item);

        weight_sum_ += weight;
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
        if (format == "" || format == "santos2018") {
            read_santos2018(file);
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

    /** Get a location. */
    inline const Location& location(LocationId location_id) const { return locations_[location_id]; }

    /** Get the x-coordinate of a location. */
    inline double x(LocationId location_id) const { return locations_[location_id].x; }

    /** Get the y-coordinate of a location. */
    inline double y(LocationId location_id) const { return locations_[location_id].y; }

    /** Get the distance between two locations. */
    inline Distance distance(
            LocationId location_id_1,
            LocationId location_id_2) const
    {
        return distances_[location_id_1][location_id_2];
    }

    /** Get the maximum distance between two locations. */
    inline Distance maximum_distance() const { return distance_max_; }

    /** Get the time limit. */
    inline Time time_limit() const { return time_limit_; }

    /** Get the duration between two locations. */
    inline Time duration(
            LocationId location_id_1,
            LocationId location_id_2,
            Weight weight) const
    {
        double speed = speed_max_ - (double)(weight * (speed_max_ - speed_min_)) / capacity();
        return (double)distance(location_id_1, location_id_2) / speed;
    }

    /** Get the number of items. */
    inline ItemId number_of_items() const { return items_.size(); }

    /** Get an item. */
    inline const Item& item(ItemId item_id) const { return items_[item_id]; }

    /** Get the capacity of the knapsack. */
    inline Weight capacity() const { return capacity_; }

    /** Print the instance. */
    std::ostream& print(
            std::ostream& os,
            int verbose = 1) const
    {
        if (verbose >= 1) {
            os
                << "Number of locations:  " << number_of_locations() << std::endl
                << "Number of items:      " << number_of_items() << std::endl
                << "Time limit:           " << time_limit() << std::endl
                << "Capacity:             " << capacity() << std::endl
                << "Minimum speed:        " << speed_min_ << std::endl
                << "Maximum speed:        " << speed_max_ << std::endl
                << "Weight sum:           " << weight_sum_ << std::endl
                << "Weight ratio:         " << (double)weight_sum_ / capacity() << std::endl
            ;
        }

        if (verbose >= 2) {
            os << std::endl
                << std::setw(12) << "Location"
                << std::setw(12) << "X"
                << std::setw(12) << "Y"
                << std::setw(12) << "Z"
                << std::setw(12) << "# items"
                << std::endl
                << std::setw(12) << "------"
                << std::setw(12) << "-"
                << std::setw(12) << "-"
                << std::setw(12) << "-"
                << std::setw(12) << "-------"
                << std::endl;
            for (LocationId location_id = 0;
                    location_id < number_of_locations();
                    ++location_id) {
                const Location& location = this->location(location_id);
                os
                    << std::setw(12) << location_id
                    << std::setw(12) << location.x
                    << std::setw(12) << location.y
                    << std::setw(12) << location.z
                    << std::setw(12) << location.item_ids.size()
                    << std::endl;
            }
        }

        if (verbose >= 2) {
            os << std::endl
                << std::setw(12) << "Item"
                << std::setw(12) << "Location"
                << std::setw(12) << "Weight"
                << std::setw(12) << "Profit"
                << std::endl
                << std::setw(12) << "----"
                << std::setw(12) << "--------"
                << std::setw(12) << "------"
                << std::setw(12) << "------"
                << std::endl;
            for (ItemId item_id = 0;
                    item_id < number_of_items();
                    ++item_id) {
                const Item& item = this->item(item_id);
                os
                    << std::setw(12) << item_id
                    << std::setw(12) << item.location_id
                    << std::setw(12) << item.weight
                    << std::setw(12) << item.profit
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
                for (LocationId location_id_2 = location_id_1 + 1;
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
    std::pair<bool, Profit> check(
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
            os << std::endl
                << std::setw(12) << "Item"
                << std::setw(12) << "Location"
                << std::setw(12) << "Time"
                << std::setw(12) << "Weight"
                << std::setw(12) << "Profit"
                << std::endl
                << std::setw(12) << "----"
                << std::setw(12) << "--------"
                << std::setw(12) << "----"
                << std::setw(12) << "------"
                << std::setw(12) << "------"
                << std::endl;
        }

        Time time = 0;
        Profit profit = 0;
        Weight weight = 0;
        LocationId location_id = 0;
        ItemId item_id = -1;
        optimizationtools::IndexedSet items(number_of_items());
        ItemPos duplicates = 0;
        while (file >> item_id) {
            //i--;
            if (items.contains(item_id)) {
                duplicates++;
                if (verbose >= 2)
                    os << "Item " << item_id << " already selected." << std::endl;
            }
            thieforienteering::LocationId location_id_next = item(item_id).location_id;
            time += duration(location_id, location_id_next, weight);
            profit += item(item_id).profit;
            weight += item(item_id).weight;

            if (verbose >= 2) {
                os
                    << std::setw(12) << item_id
                    << std::setw(12) << location_id
                    << std::setw(12) << time
                    << std::setw(12) << weight
                    << std::setw(12) << profit
                    << std::endl;
            }

            location_id = location_id_next;
        }
        time += duration(location_id, number_of_locations() - 1, weight);

        bool feasible = (duplicates == 0)
            && (time <= time_limit())
            && (weight <= capacity());
        if (verbose >= 2)
            os << std::endl;
        if (verbose >= 1) {
            os
                << "Duration:  " << time << " / " << time_limit() << std::endl
                << "Weight:    " << weight << " / " << capacity() << std::endl
                << "Feasible:  " << feasible << std::endl
                << "Profit:    " << profit << std::endl
                ;
        }
        return {feasible, profit};
    }

private:

    /*
     * Private methods
     */

    /** Read an instance from a file in 'santos2018' format. */
    void read_santos2018(std::ifstream& file)
    {
        std::string tmp;
        std::vector<std::string> line;
        ItemId number_of_items = -1;
        std::string edge_weight_type;
        std::string edge_weight_format;
        std::string node_coord_type = "TWOD_COORDS";
        while (getline(file, tmp)) {
            line = optimizationtools::split(tmp, ' ');
            if (line.size() == 0) {
            } else if (tmp.rfind("NAME", 0) == 0) {
            } else if (tmp.rfind("PROBLEM NAME", 0) == 0) {
            } else if (tmp.rfind("COMMENT", 0) == 0) {
            } else if (tmp.rfind("TYPE", 0) == 0) {
            } else if (tmp.rfind("KNAPSACK DATA TYPE", 0) == 0) {
            } else if (tmp.rfind("DISPLAY_DATA_TYPE", 0) == 0) {
            } else if (tmp.rfind("DIMENSION", 0) == 0) {
                LocationId n = std::stol(line.back());
                locations_ = std::vector<Location>(n);
                distances_ = std::vector<std::vector<Distance>>(n, std::vector<Distance>(n, -1));
            } else if (tmp.rfind("NUMBER OF ITEMS", 0) == 0) {
                number_of_items = std::stol(line.back());
            } else if (tmp.rfind("CAPACITY OF KNAPSACK", 0) == 0) {
                set_capacity(std::stol(line.back()));
            } else if (tmp.rfind("MAX TIME", 0) == 0) {
                set_time_limit(std::stol(line.back()));
            } else if (tmp.rfind("MIN SPEED", 0) == 0) {
                set_minimum_speed(std::stod(line.back()));
            } else if (tmp.rfind("MAX SPEED", 0) == 0) {
                set_maximum_speed(std::stod(line.back()));
            } else if (tmp.rfind("EDGE_WEIGHT_TYPE", 0) == 0) {
                edge_weight_type = line.back();
            } else if (tmp.rfind("EDGE_WEIGHT_FORMAT", 0) == 0) {
                edge_weight_format = line.back();
            } else if (tmp.rfind("NODE_COORD_TYPE", 0) == 0) {
                node_coord_type = line.back();
            } else if (tmp.rfind("EDGE_WEIGHT_SECTION", 0) == 0) {
                if (edge_weight_format == "UPPER_ROW") {
                    Distance d;
                    for (LocationId location_id_1 = 0;
                            location_id_1 < number_of_locations() - 1;
                            ++location_id_1) {
                        for (LocationId location_id_2 = location_id_1 + 1;
                                location_id_2 < number_of_locations();
                                ++location_id_2) {
                            file >> d;
                            set_distance(location_id_1, location_id_2, d);
                        }
                    }
                } else if (edge_weight_format == "LOWER_ROW") {
                    Distance d;
                    for (LocationId location_id_1 = 1;
                            location_id_1 < number_of_locations();
                            ++location_id_1) {
                        for (LocationId location_id_2 = 0;
                                location_id_2 < location_id_1;
                                ++location_id_2) {
                            file >> d;
                            set_distance(location_id_1, location_id_2, d);
                        }
                    }
                } else if (edge_weight_format == "UPPER_DIAG_ROW") {
                    Distance d;
                    for (LocationId location_id_1 = 0;
                            location_id_1 < number_of_locations();
                            ++location_id_1) {
                        for (LocationId location_id_2 = location_id_1;
                                location_id_2 < number_of_locations();
                                ++location_id_2) {
                            file >> d;
                            set_distance(location_id_1, location_id_2, d);
                        }
                    }
                } else if (edge_weight_format == "LOWER_DIAG_ROW") {
                    Distance d;
                    for (LocationId location_id_1 = 0;
                            location_id_1 < number_of_locations();
                            ++location_id_1) {
                        for (LocationId location_id_2 = 0;
                                location_id_2 <= location_id_1;
                                ++location_id_2) {
                            file >> d;
                            set_distance(location_id_1, location_id_2, d);
                        }
                    }
                } else if (edge_weight_format == "FULL_MATRIX") {
                    Distance d;
                    for (LocationId location_id_1 = 0;
                            location_id_1 < number_of_locations();
                            ++location_id_1) {
                        for (LocationId location_id_2 = 0;
                                location_id_2 < number_of_locations();
                                ++location_id_2) {
                            file >> d;
                            set_distance(location_id_1, location_id_2, d);
                        }
                    }
                } else {
                    std::cerr << "\033[31m" << "ERROR, EDGE_WEIGHT_FORMAT \"" << edge_weight_format << "\" not implemented." << "\033[0m" << std::endl;
                }
            } else if (tmp.rfind("NODE_COORD_SECTION", 0) == 0) {
                if (node_coord_type == "TWOD_COORDS") {
                    LocationId tmp;
                    double x, y;
                    for (LocationId location_id = 0;
                            location_id < number_of_locations();
                            ++location_id) {
                        file >> tmp >> x >> y;
                        set_xy(location_id, x, y);
                    }
                } else if (node_coord_type == "THREED_COORDS") {
                    LocationId tmp;
                    double x, y, z;
                    for (LocationId location_id = 0;
                            location_id < number_of_locations();
                            ++location_id) {
                        file >> tmp >> x >> y >> z;
                        set_xy(location_id, x, y, z);
                    }
                }
            } else if (tmp.rfind("DISPLAY_DATA_SECTION", 0) == 0) {
                LocationId tmp;
                double x, y;
                for (LocationId location_id = 0;
                        location_id < number_of_locations();
                        ++location_id) {
                    file >> tmp >> x >> y;
                    set_xy(location_id, x, y);
                }
            } else if (tmp.rfind("ITEMS SECTION", 0) == 0) {
                ItemId tmp = -1;
                Profit profit = -1;
                Weight weight = -1;
                LocationId location = -1;
                for (ItemId item_id = 0; item_id < number_of_items; ++item_id) {
                    file >> tmp >> profit >> weight >> location;
                    add_item(location - 1, profit, weight);
                }
            } else if (tmp.rfind("EOF", 0) == 0) {
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
                    Distance xd = x(location_id_2) - x(location_id_1);
                    Distance yd = y(location_id_2) - y(location_id_1);
                    Distance d = std::round(std::sqrt(xd * xd + yd * yd));
                    set_distance(location_id_1, location_id_2, d);
                }
            }
        } else if (edge_weight_type == "CEIL_2D") {
            for (LocationId location_id_1 = 0;
                    location_id_1 < number_of_locations();
                    ++location_id_1) {
                for (LocationId location_id_2 = location_id_1 + 1;
                        location_id_2 < number_of_locations();
                        ++location_id_2) {
                    Distance xd = x(location_id_2) - x(location_id_1);
                    Distance yd = y(location_id_2) - y(location_id_1);
                    Distance d = std::ceil(std::sqrt(xd * xd + yd * yd));
                    set_distance(location_id_1, location_id_2, d);
                }
            }
        } else if (edge_weight_type == "GEO") {
            std::vector<double> latitudes(number_of_locations(), 0);
            std::vector<double> longitudes(number_of_locations(), 0);
            for (LocationId location_id = 0;
                    location_id < number_of_locations();
                    ++location_id) {
                double pi = 3.141592;
                int deg_x = std::round(x(location_id));
                double min_x = x(location_id) - deg_x;
                latitudes[location_id] = pi * (deg_x + 5.0 * min_x / 3.0) / 180.0;
                int deg_y = std::round(y(location_id));
                double min_y = y(location_id) - deg_y;
                longitudes[location_id] = pi * (deg_y + 5.0 * min_y / 3.0) / 180.0;
            }
            double rrr = 6378.388;
            for (LocationId location_id_1 = 0;
                    location_id_1 < number_of_locations();
                    ++location_id_1) {
                for (LocationId location_id_2 = location_id_1 + 1;
                        location_id_2 < number_of_locations();
                        ++location_id_2) {
                    double q1 = cos(longitudes[location_id_1] - longitudes[location_id_2]);
                    double q2 = cos(latitudes[location_id_1] - latitudes[location_id_2]);
                    double q3 = cos(latitudes[location_id_1] + latitudes[location_id_2]);
                    Distance d = (Distance)(rrr * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);
                    set_distance(location_id_1, location_id_2, d);
                }
            }
        } else if (edge_weight_type == "ATT") {
            for (LocationId location_id_1 = 0;
                    location_id_1 < number_of_locations();
                    ++location_id_1) {
                for (LocationId location_id_2 = location_id_1 + 1;
                        location_id_2 < number_of_locations();
                        ++location_id_2) {
                    double xd = x(location_id_1) - x(location_id_2);
                    double yd = y(location_id_1) - y(location_id_2);
                    double rij = sqrt((xd * xd + yd * yd) / 10.0);
                    int tij = std::round(rij);
                    Distance d = (tij < rij)? tij + 1: tij;
                    set_distance(location_id_1, location_id_2, d);
                }
            }
        } else if (edge_weight_type == "EXPLICIT") {
        } else {
            std::cerr << "\033[31m" << "ERROR, EDGE_WEIGHT_TYPE \"" << edge_weight_type << "\" not implemented." << "\033[0m" << std::endl;
        }
        for (LocationId location_id = 0;
                location_id < number_of_locations();
                ++location_id)
            distances_[location_id][location_id] = 0;
    }

    /*
     * Private attributes
     */

    /** Locations. */
    std::vector<Location> locations_;

    /** Distances. */
    std::vector<std::vector<Distance>> distances_;

    /** Minimum speed. */
    double speed_min_ = -1;

    /** Maximum speed. */
    double speed_max_ = -1;

    /** Time limit. */
    Time time_limit_ = -1;

    /** Items. */
    std::vector<Item> items_;

    /** Capacity of the knapsack. */
    Weight capacity_ = -1;

    /*
     * Computed attributes
     */

    /** Maximum distance. */
    Distance distance_max_ = 0;

    /** Weight sum. */
    Weight weight_sum_ = 0;

};

}

}

