/**
 * Traveling salesman problem with release dates.
 *
 * Input:
 * - n locations; for each location j, j = 1..n, a release date rⱼ
 * - an n×n symmetric matrix containing the travel times between each pair of
 *   locations
 * Problem:
 * - find a set of consecutive tours from location 1 to location 1 such that
 *   - each other location is visited exactly once
 *   - the tour visiting location j starts after rⱼ
 * Objective:
 * - minimize the makespan of the tour
 *
 */

#pragma once

#include "optimizationtools/containers/indexed_set.hpp"
#include "optimizationtools/utils/utils.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>

namespace orproblems
{

namespace travelingsalesmanwithreleasedates
{

typedef int64_t LocationId;
typedef int64_t LocationPos;
typedef int64_t Time;

struct Location
{
    double x;
    double y;
    double z;
    Time release_date;
};

class Instance
{

public:

    Instance(LocationId n):
        locations_(n),
        travel_times_(n, std::vector<Time>(n, -1))
    {
        for (LocationId j = 0; j < n; ++j)
            travel_times_[j][j] = 0;
    }
    void set_xy(LocationId j, double x, double y, double z = -1)
    {
        locations_[j].x = x;
        locations_[j].y = y;
        locations_[j].z = z;
    }
    void set_travel_time(LocationId j1, LocationId j2, Time d)
    {
        travel_times_[j1][j2] = d;
        travel_times_[j2][j1] = d;
        maximum_travel_time_ = std::max(maximum_travel_time_, d);
    }
    void set_release_date(LocationId j, Time release_date) { locations_[j].release_date = release_date; }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        }
        if (format == "" || format == "default" || format == "archetti2018") {
            read_archetti2018(file);
        } else if (format == "archetti2018_atsplib") {
            read_archetti2018_atsplib(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    virtual ~Instance() { }

    inline LocationId number_of_locations() const { return locations_.size(); }
    inline Time release_date(LocationId j) const { return locations_[j].release_date; }
    inline double x(LocationId j) const { return locations_[j].x; }
    inline double y(LocationId j) const { return locations_[j].y; }
    inline Time travel_time(LocationId j1, LocationId j2) const { return travel_times_[j1][j2]; }
    inline Time maximum_travel_time() const { return maximum_travel_time_; }

    std::ostream& print(
            std::ostream& os,
            int verbose = 1) const
    {
        if (verbose >= 1) {
            os << "Number of locations:  " << number_of_locations() << std::endl;
        }
        if (verbose >= 2) {
            os << std::endl
                << std::setw(12) << "Location"
                << std::setw(12) << "Rel. date"
                << "    Travel times"
                << std::endl
                << std::setw(12) << "--------"
                << std::setw(12) << "---------"
                << "    ------------"
                << std::endl;
            for (LocationId j1 = 0; j1 < number_of_locations(); ++j1) {
                os << std::setw(12) << j1
                    << std::setw(12) << release_date(j1)
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
        // Initial display.
        std::ifstream file(certificate_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");
        }

        if (verbose >= 2) {
            os << std::endl << std::right
                << std::setw(12) << "Location"
                << std::setw(12) << "Rel. date"
                << std::setw(12) << "Travel time"
                << std::setw(12) << "Trip start"
                << std::setw(12) << "Trip dur."
                << std::endl
                << std::setw(12) << "--------"
                << std::setw(12) << "---------"
                << std::setw(12) << "-----------"
                << std::setw(12) << "----------"
                << std::setw(12) << "---------"
                << std::endl;
        }

        LocationId n = number_of_locations();
        optimizationtools::IndexedSet locations(n);
        LocationPos number_of_duplicates = 0;
        Time current_time = 0;
        LocationPos n_cur = -1;
        LocationPos number_of_trips = 0;
        while (file >> n_cur) {
            LocationId j_prec = 0;
            LocationId j = -1;
            Time trip_duration = 0;
            Time trip_start = current_time;
            for (LocationPos j_pos = 0; j_pos < n_cur; ++j_pos) {
                file >> j;
                if (locations.contains(j)) {
                    number_of_duplicates++;
                    if (verbose >= 2)
                        os << "Location " << j << " has already been visited." << std::endl;
                }
                locations.add(j);
                trip_duration += travel_time(j_prec, j);
                if (trip_start < release_date(j))
                    trip_start = release_date(j);
                if (verbose >= 2) {
                    os
                        << std::setw(12) << j
                        << std::setw(12) << release_date(j)
                        << std::setw(12) << travel_time(j_prec, j)
                        << std::setw(12) << trip_start
                        << std::setw(12) << trip_duration
                        << std::endl;
                }
                j_prec = j;
            }
            trip_duration += travel_time(j_prec, 0);
            current_time = trip_start + trip_duration;
            number_of_trips++;
            if (verbose >= 2) {
                os
                    << std::setw(12) << 0
                    << std::setw(12) << 0
                    << std::setw(12) << travel_time(j_prec, 0)
                    << std::setw(12) << trip_start
                    << std::setw(12) << trip_duration
                    << std::endl;
                os << "Trip end: " << current_time << std::endl;
            }
        }

        bool feasible
            = (locations.size() == n - 1)
            && (!locations.contains(0))
            && (number_of_duplicates == 0);
        if (verbose >= 2)
            os << std::endl;
        if (verbose >= 1) {
            os << "Number of locations:    " << locations.size() << " / " << n - 1  << std::endl;
            os << "Number of trips:        " << number_of_trips << std::endl;
            os << "Number of duplicates:   " << number_of_duplicates << std::endl;
            os << "Feasible:               " << feasible << std::endl;
            os << "Makespan:               " << current_time << std::endl;
        }
        return {feasible, current_time};
    }

private:

    void read_archetti2018(std::ifstream& file)
    {
        std::string tmp;
        LocationId n = -1;
        file
            >> tmp >> n
            >> tmp >> tmp
            >> tmp >> tmp
            >> tmp >> tmp
            >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp
            >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp;
        locations_ = std::vector<Location>(n);
        travel_times_ = std::vector<std::vector<Time>>(n, std::vector<Time>(n, -1));
        std::vector<std::vector<Time>> travel_times_tmp(n, std::vector<Time>(n, -1));
        for (LocationId j = 0; j < n; ++j) {
            double x = -1;
            double y = -1;
            Time r = -1;
            file >> x >> y >> tmp >> tmp >> tmp >> tmp >> r;
            set_xy(j, x, y);
            set_release_date(j, r);
        }
        for (LocationId j1 = 0; j1 < n; ++j1) {
            for (LocationId j2 = 0; j2 < n; ++j2) {
                double xd = x(j2) - x(j1);
                double yd = y(j2) - y(j1);
                Time d = std::round(std::sqrt(xd * xd + yd * yd));
                travel_times_tmp[j1][j2] = d;
                travel_times_tmp[j2][j1] = d;
            }
        }
        // Run Floyd-Warshall algorithm to ensure triangular inequality.
        // This is what the authors said they did.
        for (LocationId j1 = 0; j1 < n; ++j1) {
            for (LocationId j2 = 0; j2 < n; ++j2) {
                for (LocationId j3 = 0; j3 < n; ++j3) {
                    Time d = travel_times_tmp[j2][j1] + travel_times_tmp[j1][j3];
                    if (travel_times_tmp[j2][j3] > d) {
                        //std::cout << j2
                        //    << " " << j3
                        //    << " " << travel_times_tmp[j2][j3]
                        //    << " -> " << d
                        //    << std::endl;
                        travel_times_tmp[j2][j3] = d;
                    }
                }
            }
        }
        for (LocationId j1 = 0; j1 < n; ++j1)
            for (LocationId j2 = j1 + 1; j2 < n; ++j2)
                set_travel_time(j1, j2, travel_times_tmp[j1][j2]);
    }

    void read_archetti2018_atsplib(std::ifstream& file)
    {
        std::string tmp;
        std::vector<std::string> line;
        LocationId n = -1;
        std::string edge_weight_type;
        std::string edge_weight_format;
        std::string node_coord_type = "TWOD_COORDS";
        while (getline(file, tmp)) {
            line = optimizationtools::split(tmp, ' ');
            if (line.size() == 0) {
            } else if (tmp.rfind("NAME", 0) == 0) {
            } else if (tmp.rfind("COMMENT", 0) == 0) {
            } else if (tmp.rfind("TYPE", 0) == 0) {
            } else if (tmp.rfind("DISPLAY_DATA_TYPE", 0) == 0) {
            } else if (tmp.rfind("DIMENSION", 0) == 0) {
                n = std::stol(line.back());
                locations_ = std::vector<Location>(n);
                travel_times_ = std::vector<std::vector<Time>>(n, std::vector<Time>(n, -1));
            } else if (tmp.rfind("EDGE_WEIGHT_TYPE", 0) == 0) {
                edge_weight_type = line.back();
            } else if (tmp.rfind("EDGE_WEIGHT_FORMAT", 0) == 0) {
                edge_weight_format = line.back();
            } else if (tmp.rfind("NODE_COORD_TYPE", 0) == 0) {
                node_coord_type = line.back();
            } else if (tmp.rfind("EDGE_WEIGHT_SECTION", 0) == 0) {
                if (edge_weight_format == "UPPER_ROW") {
                    Time d;
                    for (LocationId j1 = 0; j1 < n - 1; ++j1) {
                        for (LocationId j2 = j1 + 1; j2 < n; ++j2) {
                            file >> d;
                            set_travel_time(j1, j2, d);
                        }
                    }
                } else if (edge_weight_format == "LOWER_ROW") {
                    Time d;
                    for (LocationId j1 = 1; j1 < n; ++j1) {
                        for (LocationId j2 = 0; j2 < j1; ++j2) {
                            file >> d;
                            set_travel_time(j1, j2, d);
                        }
                    }
                } else if (edge_weight_format == "UPPER_DIAG_ROW") {
                    Time d;
                    for (LocationId j1 = 0; j1 < n; ++j1) {
                        for (LocationId j2 = j1; j2 < n; ++j2) {
                            file >> d;
                            set_travel_time(j1, j2, d);
                        }
                    }
                } else if (edge_weight_format == "LOWER_DIAG_ROW") {
                    Time d;
                    for (LocationId j1 = 0; j1 < n; ++j1) {
                        for (LocationId j2 = 0; j2 <= j1; ++j2) {
                            file >> d;
                            set_travel_time(j1, j2, d);
                        }
                    }
                } else if (edge_weight_format == "FULL_MATRIX") {
                    Time d;
                    for (LocationId j1 = 0; j1 < n; ++j1) {
                        for (LocationId j2 = 0; j2 < n; ++j2) {
                            file >> d;
                            set_travel_time(j1, j2, d);
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
            } else if (tmp.rfind("RELEASE_DATES", 0) == 0) {
                Time rj;
                for (LocationId j = 0; j < n; ++j) {
                    file >> rj;
                    set_release_date(j, rj);
                }
            } else if (tmp.rfind("EOF", 0) == 0) {
                break;
            } else {
                std::cerr << "\033[31m" << "ERROR, ENTRY \"" << line[0] << "\" not implemented." << "\033[0m" << std::endl;
            }
        }

        // Compute travel times.
        if (edge_weight_type == "EUC_2D") {
            for (LocationId j1 = 0; j1 < n; ++j1) {
                for (LocationId j2 = j1 + 1; j2 < n; ++j2) {
                    double xd = x(j2) - x(j1);
                    double yd = y(j2) - y(j1);
                    Time d = std::round(std::sqrt(xd * xd + yd * yd));
                    set_travel_time(j1, j2, d);
                }
            }
        } else if (edge_weight_type == "CEIL_2D") {
            for (LocationId j1 = 0; j1 < n; ++j1) {
                for (LocationId j2 = j1 + 1; j2 < n; ++j2) {
                    double xd = x(j2) - x(j1);
                    double yd = y(j2) - y(j1);
                    Time d = std::ceil(std::sqrt(xd * xd + yd * yd));
                    set_travel_time(j1, j2, d);
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
                    Time d = (Time)(rrr * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);
                    set_travel_time(j1, j2, d);
                }
            }
        } else if (edge_weight_type == "ATT") {
            for (LocationId j1 = 0; j1 < n; ++j1) {
                for (LocationId j2 = j1 + 1; j2 < n; ++j2) {
                    double xd = x(j1) - x(j2);
                    double yd = y(j1) - y(j2);
                    double rij = sqrt((xd * xd + yd * yd) / 10.0);
                    int tij = std::round(rij);
                    Time d = (tij < rij)? tij + 1: tij;
                    set_travel_time(j1, j2, d);
                }
            }
        } else if (edge_weight_type == "EXPLICIT") {
        } else {
            std::cerr << "\033[31m" << "ERROR, EDGE_WEIGHT_TYPE \"" << edge_weight_type << "\" not implemented." << "\033[0m" << std::endl;
        }
        for (LocationId j = 0; j < n; ++j)
            travel_times_[j][j] = std::numeric_limits<Time>::max();
    }

    std::vector<Location> locations_;
    std::vector<std::vector<Time>> travel_times_;
    Time maximum_travel_time_ = 0;

};

}

}

