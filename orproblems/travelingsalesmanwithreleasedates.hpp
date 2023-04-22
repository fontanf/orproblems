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

using LocationId = int64_t;
using LocationPos = int64_t;
using Time = int64_t;

/**
 * Structure for a location.
 */
struct Location
{
    /** x-coordinate of the location. */
    double x;

    /** y-coordinate of the location. */
    double y;

    /** z-coordinate of the location. */
    double z;

    /** Release date. */
    Time release_date;
};

/**
 * Instance class for a 'travelingsalesmanwithreleasedates' problem.
 */
class Instance
{

public:

    /*
     * Constructors and destructor
     */

    /** Constructor to build an instance manually. */
    Instance(LocationId number_of_locations):
        locations_(number_of_locations),
        travel_times_(number_of_locations, std::vector<Time>(number_of_locations, -1))
    {
        for (LocationId location_id = 0;
                location_id < number_of_locations;
                ++location_id) {
            travel_times_[location_id][location_id] = 0;
        }
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

    /** Set the travel time between two location. */
    void set_travel_time(
            LocationId location_id_1,
            LocationId location_id_2,
            Time travel_time)
    {
        travel_times_[location_id_1][location_id_2] = travel_time;
        travel_times_[location_id_2][location_id_1] = travel_time;
        maximum_travel_time_ = std::max(maximum_travel_time_, travel_time);
    }

    /** Set the release date for a location. */
    void set_release_date(
            LocationId location_id,
            Time release_date)
    {
        locations_[location_id].release_date = release_date;
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

    /*
     * Getters
     */

    /** Get the number of locations. */
    inline LocationId number_of_locations() const { return locations_.size(); }

    /** Get a location. */
    inline const Location& location(LocationId location_id) const { return locations_[location_id]; }

    /** Get the travel time between two locations. */
    inline Time travel_time(
            LocationId location_id_1,
            LocationId location_id_2) const
    {
        return travel_times_[location_id_1][location_id_2];
    }

    /** Get the maximum travel time. */
    inline Time maximum_travel_time() const { return maximum_travel_time_; }

    /** Print the instance. */
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
                << std::endl
                << std::setw(12) << "--------"
                << std::setw(12) << "---------"
                << std::endl;
            for (LocationId location_id = 0;
                    location_id < number_of_locations();
                    ++location_id) {
                os
                    << std::setw(12) << location_id
                    << std::setw(12) << location(location_id).release_date
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
                        << std::setw(12) << travel_time(location_id_1, location_id_2)
                        << std::endl;
                }
            }
        }

        return os;
    }

    /** Check a certificate. */
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

        optimizationtools::IndexedSet locations(number_of_locations());
        LocationPos number_of_duplicates = 0;
        Time current_time = 0;
        LocationPos current_trip_number_of_locations = -1;
        LocationPos number_of_trips = 0;
        while (file >> current_trip_number_of_locations) {

            LocationId location_id_prev = 0;
            LocationId location_id = -1;
            Time trip_duration = 0;
            Time trip_start = current_time;
            for (LocationPos location_pos = 0;
                    location_pos < current_trip_number_of_locations;
                    ++location_pos) {
                file >> location_id;

                // Check duplicates.
                if (locations.contains(location_id)) {
                    number_of_duplicates++;
                    if (verbose >= 2) {
                        os << "Location " << location_id
                            << " has already been visited." << std::endl;
                    }
                }
                locations.add(location_id);

                trip_duration += travel_time(location_id_prev, location_id);
                if (trip_start < location(location_id).release_date)
                    trip_start = location(location_id).release_date;

                if (verbose >= 2) {
                    os
                        << std::setw(12) << location_id
                        << std::setw(12) << location(location_id).release_date
                        << std::setw(12) << travel_time(location_id_prev, location_id)
                        << std::setw(12) << trip_start
                        << std::setw(12) << trip_duration
                        << std::endl;
                }

                location_id_prev = location_id;
            }
            trip_duration += travel_time(location_id_prev, 0);
            current_time = trip_start + trip_duration;
            number_of_trips++;

            if (verbose >= 2) {
                os
                    << std::setw(12) << 0
                    << std::setw(12) << 0
                    << std::setw(12) << travel_time(location_id_prev, 0)
                    << std::setw(12) << trip_start
                    << std::setw(12) << trip_duration
                    << std::endl;
                os << "Trip end: " << current_time << std::endl;
            }
        }

        bool feasible
            = (locations.size() == number_of_locations() - 1)
            && (!locations.contains(0))
            && (number_of_duplicates == 0);

        if (verbose >= 2)
            os << std::endl;
        if (verbose >= 1) {
            os
                << "Number of locations:    " << locations.size() << " / " << number_of_locations() - 1  << std::endl
                << "Number of trips:        " << number_of_trips << std::endl
                << "Number of duplicates:   " << number_of_duplicates << std::endl
                << "Feasible:               " << feasible << std::endl
                << "Makespan:               " << current_time << std::endl
                ;
        }
        return {feasible, current_time};
    }

private:

    /*
     * Private methods
     */

    /** Read an instance from a file in 'archetti2018' format. */
    void read_archetti2018(std::ifstream& file)
    {
        std::string tmp;
        LocationId number_of_locations = -1;
        file
            >> tmp >> number_of_locations
            >> tmp >> tmp
            >> tmp >> tmp
            >> tmp >> tmp
            >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp
            >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp;
        locations_ = std::vector<Location>(number_of_locations);
        travel_times_ = std::vector<std::vector<Time>>(
                number_of_locations,
                std::vector<Time>(number_of_locations, -1));
        std::vector<std::vector<Time>> travel_times_tmp(
                number_of_locations,
                std::vector<Time>(number_of_locations, -1));

        for (LocationId location_id = 0;
                location_id < number_of_locations;
                ++location_id) {
            double x = -1;
            double y = -1;
            Time release_date = -1;
            file >> x >> y >> tmp >> tmp >> tmp >> tmp >> release_date;
            set_xy(location_id, x, y);
            set_release_date(location_id, release_date);
        }

        for (LocationId location_id_1 = 0;
                location_id_1 < number_of_locations;
                ++location_id_1) {
            for (LocationId location_id_2 = 0;
                    location_id_2 < number_of_locations;
                    ++location_id_2) {
                double xd = location(location_id_2).x - location(location_id_1).x;
                double yd = location(location_id_2).y - location(location_id_1).y;
                Time travel_time = std::round(std::sqrt(xd * xd + yd * yd));
                travel_times_tmp[location_id_1][location_id_2] = travel_time;
                travel_times_tmp[location_id_2][location_id_1] = travel_time;
            }
        }

        // Run Floyd-Warshall algorithm to ensure triangular inequality.
        // This is what the authors said they did.
        for (LocationId location_id_1 = 0;
                location_id_1 < number_of_locations;
                ++location_id_1) {
            for (LocationId location_id_2 = 0;
                    location_id_2 < number_of_locations;
                    ++location_id_2) {
                for (LocationId location_id_3 = 0;
                        location_id_3 < number_of_locations;
                        ++location_id_3) {
                    Time travel_time = travel_times_tmp[location_id_2][location_id_1]
                        + travel_times_tmp[location_id_1][location_id_3];
                    if (travel_times_tmp[location_id_2][location_id_3] > travel_time) {
                        //std::cout << location_id_2
                        //    << " " << location_id_3
                        //    << " " << travel_times_tmp[location_id_2][location_id_3]
                        //    << " -> " << d
                        //    << std::endl;
                        travel_times_tmp[location_id_2][location_id_3] = travel_time;
                    }
                }
            }
        }

        for (LocationId location_id_1 = 0;
                location_id_1 < number_of_locations;
                ++location_id_1) {
            for (LocationId location_id_2 = location_id_1 + 1;
                    location_id_2 < number_of_locations;
                    ++location_id_2) {
                set_travel_time(
                        location_id_1,
                        location_id_2,
                        travel_times_tmp[location_id_1][location_id_2]);
            }
        }
    }

    /** Read an instance from a file in 'archetti2018_atsplib' format. */
    void read_archetti2018_atsplib(std::ifstream& file)
    {
        std::string tmp;
        std::vector<std::string> line;
        LocationId number_of_locations = -1;
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
                number_of_locations = std::stol(line.back());
                locations_ = std::vector<Location>(number_of_locations);
                travel_times_ = std::vector<std::vector<Time>>(
                        number_of_locations,
                        std::vector<Time>(number_of_locations, -1));
            } else if (tmp.rfind("EDGE_WEIGHT_TYPE", 0) == 0) {
                edge_weight_type = line.back();
            } else if (tmp.rfind("EDGE_WEIGHT_FORMAT", 0) == 0) {
                edge_weight_format = line.back();
            } else if (tmp.rfind("NODE_COORD_TYPE", 0) == 0) {
                node_coord_type = line.back();
            } else if (tmp.rfind("EDGE_WEIGHT_SECTION", 0) == 0) {
                if (edge_weight_format == "UPPER_ROW") {
                    Time travel_time;
                    for (LocationId location_id_1 = 0;
                            location_id_1 < number_of_locations - 1;
                            ++location_id_1) {
                        for (LocationId location_id_2 = location_id_1 + 1;
                                location_id_2 < number_of_locations;
                                ++location_id_2) {
                            file >> travel_time;
                            set_travel_time(
                                    location_id_1,
                                    location_id_2,
                                    travel_time);
                        }
                    }
                } else if (edge_weight_format == "LOWER_ROW") {
                    Time travel_time;
                    for (LocationId location_id_1 = 1;
                            location_id_1 < number_of_locations;
                            ++location_id_1) {
                        for (LocationId location_id_2 = 0;
                                location_id_2 < location_id_1;
                                ++location_id_2) {
                            file >> travel_time;
                            set_travel_time(
                                    location_id_1,
                                    location_id_2,
                                    travel_time);
                        }
                    }
                } else if (edge_weight_format == "UPPER_DIAG_ROW") {
                    Time travel_time;
                    for (LocationId location_id_1 = 0;
                            location_id_1 < number_of_locations;
                            ++location_id_1) {
                        for (LocationId location_id_2 = location_id_1;
                                location_id_2 < number_of_locations;
                                ++location_id_2) {
                            file >> travel_time;
                            set_travel_time(
                                    location_id_1,
                                    location_id_2,
                                    travel_time);
                        }
                    }
                } else if (edge_weight_format == "LOWER_DIAG_ROW") {
                    Time travel_time;
                    for (LocationId location_id_1 = 0;
                            location_id_1 < number_of_locations;
                            ++location_id_1) {
                        for (LocationId location_id_2 = 0;
                                location_id_2 <= location_id_1;
                                ++location_id_2) {
                            file >> travel_time;
                            set_travel_time(
                                    location_id_1,
                                    location_id_2,
                                    travel_time);
                        }
                    }
                } else if (edge_weight_format == "FULL_MATRIX") {
                    Time travel_time;
                    for (LocationId location_id_1 = 0;
                            location_id_1 < number_of_locations;
                            ++location_id_1) {
                        for (LocationId location_id_2 = 0;
                                location_id_2 < number_of_locations;
                                ++location_id_2) {
                            file >> travel_time;
                            set_travel_time(
                                    location_id_1,
                                    location_id_2,
                                    travel_time);
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
                            location_id < number_of_locations;
                            ++location_id) {
                        file >> tmp >> x >> y;
                        set_xy(location_id, x, y);
                    }
                } else if (node_coord_type == "THREED_COORDS") {
                    LocationId tmp;
                    double x, y, z;
                    for (LocationId location_id = 0;
                            location_id < number_of_locations;
                            ++location_id) {
                        file >> tmp >> x >> y >> z;
                        set_xy(location_id, x, y, z);
                    }
                }
            } else if (tmp.rfind("DISPLAY_DATA_SECTION", 0) == 0) {
                LocationId tmp;
                double x, y;
                for (LocationId location_id = 0;
                        location_id < number_of_locations;
                        ++location_id) {
                    file >> tmp >> x >> y;
                    set_xy(location_id, x, y);
                }
            } else if (tmp.rfind("RELEASE_DATES", 0) == 0) {
                Time release_date;
                for (LocationId location_id = 0;
                        location_id < number_of_locations;
                        ++location_id) {
                    file >> release_date;
                    set_release_date(location_id, release_date);
                }
            } else if (tmp.rfind("EOF", 0) == 0) {
                break;
            } else {
                std::cerr << "\033[31m" << "ERROR, ENTRY \"" << line[0] << "\" not implemented." << "\033[0m" << std::endl;
            }
        }

        // Compute travel times.
        if (edge_weight_type == "EUC_2D") {
            for (LocationId location_id_1 = 0;
                    location_id_1 < number_of_locations;
                    ++location_id_1) {
                for (LocationId location_id_2 = location_id_1 + 1;
                        location_id_2 < number_of_locations;
                        ++location_id_2) {
                    double xd = x(location_id_2) - x(location_id_1);
                    double yd = y(location_id_2) - y(location_id_1);
                    Time d = std::round(std::sqrt(xd * xd + yd * yd));
                    set_travel_time(location_id_1, location_id_2, d);
                }
            }
        } else if (edge_weight_type == "CEIL_2D") {
            for (LocationId location_id_1 = 0;
                    location_id_1 < number_of_locations;
                    ++location_id_1) {
                for (LocationId location_id_2 = location_id_1 + 1;
                        location_id_2 < number_of_locations;
                        ++location_id_2) {
                    double xd = x(location_id_2) - x(location_id_1);
                    double yd = y(location_id_2) - y(location_id_1);
                    Time d = std::ceil(std::sqrt(xd * xd + yd * yd));
                    set_travel_time(location_id_1, location_id_2, d);
                }
            }
        } else if (edge_weight_type == "GEO") {
            std::vector<double> latitudes(number_of_locations, 0);
            std::vector<double> longitudes(number_of_locations, 0);
            for (LocationId j = 0; j < number_of_locations; ++j) {
                double pi = 3.141592;
                int deg_x = std::round(x(j));
                double min_x = x(j) - deg_x;
                latitudes[j] = pi * (deg_x + 5.0 * min_x / 3.0) / 180.0;
                int deg_y = std::round(y(j));
                double min_y = y(j) - deg_y;
                longitudes[j] = pi * (deg_y + 5.0 * min_y / 3.0) / 180.0;
            }
            double rrr = 6378.388;
            for (LocationId location_id_1 = 0;
                    location_id_1 < number_of_locations;
                    ++location_id_1) {
                for (LocationId location_id_2 = location_id_1 + 1;
                        location_id_2 < number_of_locations;
                        ++location_id_2) {
                    double q1 = cos(longitudes[location_id_1] - longitudes[location_id_2]);
                    double q2 = cos(latitudes[location_id_1] - latitudes[location_id_2]);
                    double q3 = cos(latitudes[location_id_1] + latitudes[location_id_2]);
                    Time travel_time = (Time)(rrr * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);
                    set_travel_time(
                            location_id_1,
                            location_id_2,
                            travel_time);
                }
            }
        } else if (edge_weight_type == "ATT") {
            for (LocationId location_id_1 = 0;
                    location_id_1 < number_of_locations;
                    ++location_id_1) {
                for (LocationId location_id_2 = location_id_1 + 1;
                        location_id_2 < number_of_locations;
                        ++location_id_2) {
                    double xd = x(location_id_1) - x(location_id_2);
                    double yd = y(location_id_1) - y(location_id_2);
                    double rij = sqrt((xd * xd + yd * yd) / 10.0);
                    int tij = std::round(rij);
                    Time d = (tij < rij)? tij + 1: tij;
                    set_travel_time(location_id_1, location_id_2, d);
                }
            }
        } else if (edge_weight_type == "EXPLICIT") {
        } else {
            std::cerr << "\033[31m" << "ERROR, EDGE_WEIGHT_TYPE \"" << edge_weight_type << "\" not implemented." << "\033[0m" << std::endl;
        }
        for (LocationId j = 0; j < n; ++j)
            travel_times_[j][j] = std::numeric_limits<Time>::max();
    }

    /*
     * Private attributes
     */

    /** Locations. */
    std::vector<Location> locations_;

    /** Travel times. */
    std::vector<std::vector<Time>> travel_times_;

    /*
     * Computed attributes
     */

    /** Maximum travel time. */
    Time maximum_travel_time_ = 0;

};

}

}

