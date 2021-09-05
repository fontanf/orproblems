#pragma once

#include "optimizationtools/utils.hpp"
#include "optimizationtools/indexed_set.hpp"
#include "optimizationtools/sorted_on_demand_array.hpp"

/**
 * Thief orienterring problem.
 *
 * Input:
 * - n cities and an n×n symmetric matrix d containing the distances between
 *   each pair of cities
 * - m items with profit pᵢ, weight wᵢ (i = 1..m) and location nᵢ
 * - A time limit T
 * - A capacity c
 * - A maximum speed vmax and a minimum speed vmin such that the time to travel
 *   from city j1 to city j2 is equal to:
 *       d(j1, j2) / (vmax - w * (vmax - vmin) / c)
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

namespace orproblems
{

namespace thieforienteering
{

typedef int64_t LocationId;
typedef int64_t Distance;
typedef double Time;
typedef int64_t ItemId;
typedef int64_t ItemPos;
typedef int64_t Profit;
typedef int64_t Weight;

struct Item
{
    Profit profit;
    Weight weight;
    LocationId location;
};

struct Location
{
    double x;
    double y;
    double z;
    std::vector<ItemId> items;
};

class Instance
{

public:

    Instance(LocationId n):
        locations_(n),
        distances_(n, std::vector<Distance>(n, -1))
    {
        for (LocationId j = 0; j < n; ++j)
            distances_[j][j] = 0;
    }
    void set_time_limit(Time time_limit)
    {
        time_limit_ = time_limit;
    }
    void set_xy(LocationId j, double x, double y, double z = -1)
    {
        locations_[j].x = x;
        locations_[j].y = y;
        locations_[j].z = z;
    }
    void set_distance(LocationId j1, LocationId j2, Distance d)
    {
        distances_[j1][j2] = d;
        distances_[j2][j1] = d;
        distance_max_ = std::max(distance_max_, d);
    }
    void add_item(LocationId j, Profit profit, Weight weight)
    {
        ItemId i = items_.size();
        locations_[j].items.push_back(i);
        Item item;
        item.location = j;
        item.profit = profit;
        item.weight = weight;
        items_.push_back(item);
    }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        if (format == "" || format == "santos2018") {
            read_santos2018(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    virtual ~Instance() { }

    inline LocationId number_of_locations() const { return locations_.size(); }
    inline double x(LocationId j) const { return locations_[j].x; }
    inline double y(LocationId j) const { return locations_[j].y; }
    inline Distance distance(LocationId j1, LocationId j2) const { return distances_[j1][j2]; }
    inline Distance maximum_distance() const { return distance_max_; }
    inline Time time_limit() const { return time_limit_; }
    inline Time duration(LocationId j1, LocationId j2, Weight weight) const
    {
        double speed = speed_max_ - (double)(weight * (speed_max_ - speed_min_)) / capacity();
        return (double)distance(j1, j2) / speed;
    }

    inline ItemId number_of_items() const { return items_.size(); }
    inline const Item& item(ItemId i) const { return items_[i]; }
    inline const Location& location(LocationId j) const { return locations_[j]; }
    inline Weight capacity() const { return capacity_; }

    std::pair<bool, Time> check(std::string certificate_path)
    {
        std::ifstream file(certificate_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");

        Time t = 0;
        Profit p = 0;
        Weight w = 0;
        LocationId j = 0;
        ItemId i = -1;
        optimizationtools::IndexedSet items(number_of_items());
        ItemPos duplicates = 0;
        while (file >> i) {
            //i--;
            if (items.contains(i)) {
                duplicates++;
                std::cout << "Item " << i << " already selected." << std::endl;
            }
            thieforienteering::LocationId j_next = item(i).location;
            t += duration(j, j_next, w);
            p += item(i).profit;
            w += item(i).weight;
            std::cout << "Item: " << i
                << "; Location: " << j_next
                << "; Duration: " << t << " / " << time_limit()
                << "; Weight: " << w << " / " << capacity()
                << "; Profit: " << p << std::endl;
            j = j_next;
        }
        t += duration(j, number_of_locations() - 1, w);

        bool feasible = (duplicates == 0)
            && (t <= time_limit())
            && (w <= capacity());

        std::cout << "---" << std::endl;
        std::cout << "Duration:  " << t << " / " << time_limit() << std::endl;
        std::cout << "Weight:    " << w << " / " << capacity() << std::endl;
        std::cout << "Feasible:  " << feasible << std::endl;
        std::cout << "Profit:    " << p << std::endl;
        return {feasible, p};
    }


private:

    void read_santos2018(std::ifstream& file)
    {
        std::string tmp;
        std::vector<std::string> line;
        LocationId n = -1;
        ItemId n_items = -1;
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
                n = std::stol(line.back());
                locations_ = std::vector<Location>(n);
                distances_ = std::vector<std::vector<Distance>>(n, std::vector<Distance>(n, -1));
            } else if (tmp.rfind("NUMBER OF ITEMS", 0) == 0) {
                n_items = std::stol(line.back());
            } else if (tmp.rfind("CAPACITY OF KNAPSACK", 0) == 0) {
                capacity_ = std::stol(line.back());
            } else if (tmp.rfind("MAX TIME", 0) == 0) {
                time_limit_ = std::stol(line.back());
            } else if (tmp.rfind("MIN SPEED", 0) == 0) {
                speed_min_ = std::stod(line.back());
            } else if (tmp.rfind("MAX SPEED", 0) == 0) {
                speed_max_ = std::stod(line.back());
            } else if (tmp.rfind("EDGE_WEIGHT_TYPE", 0) == 0) {
                edge_weight_type = line.back();
            } else if (tmp.rfind("EDGE_WEIGHT_FORMAT", 0) == 0) {
                edge_weight_format = line.back();
            } else if (tmp.rfind("NODE_COORD_TYPE", 0) == 0) {
                node_coord_type = line.back();
            } else if (tmp.rfind("EDGE_WEIGHT_SECTION", 0) == 0) {
                if (edge_weight_format == "UPPER_ROW") {
                    Distance d;
                    for (LocationId j1 = 0; j1 < n - 1; ++j1) {
                        for (LocationId j2 = j1 + 1; j2 < n; ++j2) {
                            file >> d;
                            set_distance(j1, j2, d);
                        }
                    }
                } else if (edge_weight_format == "LOWER_ROW") {
                    Distance d;
                    for (LocationId j1 = 1; j1 < n; ++j1) {
                        for (LocationId j2 = 0; j2 < j1; ++j2) {
                            file >> d;
                            set_distance(j1, j2, d);
                        }
                    }
                } else if (edge_weight_format == "UPPER_DIAG_ROW") {
                    Distance d;
                    for (LocationId j1 = 0; j1 < n; ++j1) {
                        for (LocationId j2 = j1; j2 < n; ++j2) {
                            file >> d;
                            set_distance(j1, j2, d);
                        }
                    }
                } else if (edge_weight_format == "LOWER_DIAG_ROW") {
                    Distance d;
                    for (LocationId j1 = 0; j1 < n; ++j1) {
                        for (LocationId j2 = 0; j2 <= j1; ++j2) {
                            file >> d;
                            set_distance(j1, j2, d);
                        }
                    }
                } else if (edge_weight_format == "FULL_MATRIX") {
                    Distance d;
                    for (LocationId j1 = 0; j1 < n; ++j1) {
                        for (LocationId j2 = 0; j2 < n; ++j2) {
                            file >> d;
                            set_distance(j1, j2, d);
                        }
                    }
                } else {
                    std::cerr << "\033[31m" << "ERROR, EDGE_WEIGHT_FORMAT \"" << edge_weight_format << "\" not implemented." << "\033[0m" << std::endl;
                }
            } else if (tmp.rfind("NODE_COORD_SECTION", 0) == 0) {
                if (node_coord_type == "TWOD_COORDS") {
                    LocationId tmp;
                    double x, y;
                    for (LocationId j = 0; j < n; ++j) {
                        file >> tmp >> x >> y;
                        set_xy(j, x, y);
                    }
                } else if (node_coord_type == "THREED_COORDS") {
                    LocationId tmp;
                    double x, y, z;
                    for (LocationId j = 0; j < n; ++j) {
                        file >> tmp >> x >> y >> z;
                        set_xy(j, x, y, z);
                    }
                }
            } else if (tmp.rfind("DISPLAY_DATA_SECTION", 0) == 0) {
                LocationId tmp;
                double x, y;
                for (LocationId j = 0; j < n; ++j) {
                    file >> tmp >> x >> y;
                    set_xy(j, x, y);
                }
            } else if (tmp.rfind("ITEMS SECTION", 0) == 0) {
                ItemId tmp = -1;
                Profit profit = -1;
                Weight weight = -1;
                LocationId location = -1;
                for (ItemId i = 0; i < n_items; ++i) {
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
            for (LocationId j1 = 0; j1 < n; ++j1) {
                for (LocationId j2 = j1 + 1; j2 < n; ++j2) {
                    Distance xd = x(j2) - x(j1);
                    Distance yd = y(j2) - y(j1);
                    Distance d = std::round(std::sqrt(xd * xd + yd * yd));
                    set_distance(j1, j2, d);
                }
            }
        } else if (edge_weight_type == "CEIL_2D") {
            for (LocationId j1 = 0; j1 < n; ++j1) {
                for (LocationId j2 = j1 + 1; j2 < n; ++j2) {
                    Distance xd = x(j2) - x(j1);
                    Distance yd = y(j2) - y(j1);
                    Distance d = std::ceil(std::sqrt(xd * xd + yd * yd));
                    set_distance(j1, j2, d);
                }
            }
        } else if (edge_weight_type == "GEO") {
            std::vector<double> latitudes(n, 0);
            std::vector<double> longitudes(n, 0);
            for (LocationId j = 0; j < n; ++j) {
                double pi = 3.141592;
                int deg_x = std::round(x(j));
                double min_x = x(j) - deg_x;
                latitudes[j] = pi * (deg_x + 5.0 * min_x / 3.0) / 180.0;
                int deg_y = std::round(y(j));
                double min_y = y(j) - deg_y;
                longitudes[j] = pi * (deg_y + 5.0 * min_y / 3.0) / 180.0;
            }
            double rrr = 6378.388;
            for (LocationId j1 = 0; j1 < n; ++j1) {
                for (LocationId j2 = j1 + 1; j2 < n; ++j2) {
                    double q1 = cos(longitudes[j1] - longitudes[j2]);
                    double q2 = cos(latitudes[j1] - latitudes[j2]);
                    double q3 = cos(latitudes[j1] + latitudes[j2]);
                    Distance d = (Distance)(rrr * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);
                    set_distance(j1, j2, d);
                }
            }
        } else if (edge_weight_type == "ATT") {
            for (LocationId j1 = 0; j1 < n; ++j1) {
                for (LocationId j2 = j1 + 1; j2 < n; ++j2) {
                    double xd = x(j1) - x(j2);
                    double yd = y(j1) - y(j2);
                    double rij = sqrt((xd * xd + yd * yd) / 10.0);
                    int tij = std::round(rij);
                    Distance d = (tij < rij)? tij + 1: tij;
                    set_distance(j1, j2, d);
                }
            }
        } else if (edge_weight_type == "EXPLICIT") {
        } else {
            std::cerr << "\033[31m" << "ERROR, EDGE_WEIGHT_TYPE \"" << edge_weight_type << "\" not implemented." << "\033[0m" << std::endl;
        }
        for (LocationId j = 0; j < n; ++j)
            distances_[j][j] = 0;
    }

    std::vector<Location> locations_;
    std::vector<std::vector<Distance>> distances_;
    Distance distance_max_ = 0;
    double speed_min_ = -1;
    double speed_max_ = -1;
    Time time_limit_ = -1;

    std::vector<Item> items_;
    Weight capacity_ = -1;

};

static inline std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "number of locations: " << instance.number_of_locations() << std::endl;
    os << "number of items: " << instance.number_of_items() << std::endl;
    for (ItemId i = 0; i < instance.number_of_items(); ++i)
        os << "item: " << i
            << "; location: " << instance.item(i).location
            << "; weight: " << instance.item(i).weight
            << "; profit: " << instance.item(i).profit
            << std::endl;
    for (LocationId j = 0; j < instance.number_of_locations(); ++j) {
        os << "location: " << j
            << "; items:";
        for (ItemId i: instance.location(j).items)
            os << " " << i;
        os << std::endl;
    }
    for (LocationId j1 = 0; j1 < instance.number_of_locations(); ++j1) {
        os << "location " << j1 << ":";
        for (LocationId j2 = 0; j2 < instance.number_of_locations(); ++j2)
            os << " " << instance.distance(j1, j2);
        os << std::endl;
    }
    return os;
}

}

}

