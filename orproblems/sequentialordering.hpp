/**
 * Sequential Ordering Problem.
 * (Asymmetric Traveling Salesman Problem with Precedence Constraints)
 *
 * Input:
 * - n locations and an n×n matrix containing the distances between each pair of
 *   locations (not necessarily symmetric)
 * - a directed acyclic graph such that each location corresponds to a location
 * Problem:
 * - find a route from location 1 such that:
 *   - each location is visited exactly once
 *   - precedence constraints are satisfied
 *   - if there exists an arc from location location_id_1 to location location_id_2 in G, then location
 *     location_id_1 is visited before location location_id_2
 * Objective:
 * - Minimize the total length of the route
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

namespace sequentialordering
{

using LocationId = int64_t;
using LocationPos = int64_t;
using Distance = int64_t;

/**
 * Structure for a location.
 */
struct Location
{
    /** Predecessors. */
    std::vector<LocationId> predecessors;
};


/**
 * Instance class for a 'sequentialordering' problem.
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
        distances_(number_of_locations, std::vector<Distance>(number_of_locations, -1))
    {
        for (LocationId location_id = 0;
                location_id < number_of_locations;
                ++location_id)
            distances_[location_id][location_id] = 0;
    }

    /** Set the distance between two locations. */
    void set_distance(
            LocationId location_id_1,
            LocationId location_id_2,
            Distance distance)
    {
        check_location_index(location_id_1);
        check_location_index(location_id_2);
        distances_[location_id_1][location_id_2] = distance;
        distance_max_ = std::max(distance_max_, distance);
    }

    /** Add a predecessor to a location. */
    void add_predecessor(
            LocationId location_id_1,
            LocationId location_id_2)
    {
        check_location_index(location_id_1);
        check_location_index(location_id_2);
        locations_[location_id_1].predecessors.push_back(location_id_2);
    }

    /** Create an instance from a file. */
    Instance(
            std::string instance_path,
            std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        }

        if (format == "" || format == "tsplib") {
            read_tsplib(file);
        } else if (format == "soplib") {
            read_soplib(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    /*
     * Getters
     */

    /** Get the number of locations */
    inline LocationId number_of_locations() const { return locations_.size(); }

    /** Get the distance between two locations. */
    inline Distance distance(
            LocationId location_id_1,
            LocationId location_id_2) const
    {
        return distances_[location_id_1][location_id_2];
    }

    /** Get the predecessors of location. */
    inline const std::vector<LocationId>& predecessors(LocationId location_id) const { return locations_[location_id].predecessors; }

    /** Get the maximum distance between two locations. */
    inline Distance maximum_distance() const { return distance_max_; }

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

        if (verbose >= 2) {
            os << std::endl
                << std::setw(12) << "Loc. 1"
                << std::setw(12) << "Pred."
                << std::endl
                << std::setw(12) << "------"
                << std::setw(12) << "-----"
                << std::endl;
            for (LocationId location_id_1 = 0;
                    location_id_1 < number_of_locations();
                    ++location_id_1) {
                for (LocationId location_id_2: predecessors(location_id_1)) {
                    os
                        << std::setw(12) << location_id_1
                        << std::setw(12) << location_id_2
                        << std::endl;
                }
            }
        }

        return os;
    }

    /** Check a certificate. */
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
            os << std::endl
                << std::setw(12) << "Location"
                << std::setw(12) << "Distance"
                << std::endl
                << std::setw(12) << "--------"
                << std::setw(12) << "--------"
                << std::endl;
        }

        LocationId location_id_pred = 0;
        LocationId location_id = -1;
        optimizationtools::IndexedSet locations(number_of_locations());
        locations.add(0);
        LocationPos number_of_duplicates = 0;
        LocationPos number_of_precedence_violations = 0;
        Distance total_distance = 0;
        while (file >> location_id) {
            // Check duplicates.
            if (locations.contains(location_id)) {
                number_of_duplicates++;
                if (verbose >= 2) {
                    os << "Location " << location_id
                        << " has already been visited." << std::endl;
                }
            }
            // Check predecessors.
            for (LocationId location_id_predeceoor: predecessors(location_id)) {
                if (!locations.contains(location_id_predeceoor)) {
                    number_of_precedence_violations++;
                    if (verbose >= 2) {
                        os << std::endl << "Location " << location_id
                            << " depends on location "
                            << location_id_predeceoor
                            << " which has not been visited yet."
                            << std::endl;
                    }
                }
            }

            locations.add(location_id);
            total_distance += distance(location_id_pred, location_id);

            if (verbose >= 2) {
                os
                    << std::setw(12) << location_id
                    << std::setw(12) << total_distance
                    << std::endl;
            }

            location_id_pred = location_id;
        }

        bool feasible
            = (locations.size() == number_of_locations())
            && (number_of_duplicates == 0)
            && (number_of_precedence_violations == 0);

        if (verbose >= 2)
            os << std::endl;
        if (verbose >= 1) {
            os
                << "Number of Vertices:               " << locations.size() << " / " << number_of_locations() << std::endl
                << "Number of duplicates:             " << number_of_duplicates << std::endl
                << "Number of precedence violations:  " << number_of_precedence_violations << std::endl
                << "Feasible:                         " << feasible << std::endl
                << "Total distance:                   " << total_distance << std::endl
                ;
        }
        return {feasible, total_distance};
    }

    /** Check if a location index is within the correct range. */
    inline void check_location_index(LocationId location_id)
    {
        if (location_id < 0 || location_id >= number_of_locations())
            throw std::out_of_range(
                    "Invalid location index: \"" + std::to_string(location_id) + "\"."
                    + " Location indices should belong to [0, "
                    + std::to_string(number_of_locations() - 1) + "].");
    }

private:

    /*
     * Private methods
     */

    /** Read a file in 'tsplib' format. */
    void read_tsplib(std::ifstream& file)
    {
        std::string tmp;
        std::vector<std::string> line;
        LocationId number_of_locations = -1;
        std::string edge_weight_type;
        std::string edge_weight_format;
        for (;;) {
            getline(file, tmp);
            line = optimizationtools::split(tmp, ' ');
            if (line.size() == 0) {
            } else if (tmp.rfind("NAME", 0) == 0) {
            } else if (tmp.rfind("COMMENT", 0) == 0) {
            } else if (tmp.rfind("TYPE", 0) == 0) {
            } else if (tmp.rfind("DIMENSION", 0) == 0) {
                number_of_locations = std::stol(line.back());
                locations_ = std::vector<Location>(number_of_locations);
                distances_ = std::vector<std::vector<Distance>>(
                        number_of_locations, std::vector<Distance>(number_of_locations, -1));
                for (LocationId location_id = 0;
                        location_id < number_of_locations;
                        ++location_id)
                    distances_[location_id][location_id]
                        = std::numeric_limits<Distance>::max();
            } else if (tmp.rfind("EDGE_WEIGHT_TYPE", 0) == 0) {
                edge_weight_type = line.back();
            } else if (tmp.rfind("EDGE_WEIGHT_FORMAT", 0) == 0) {
                edge_weight_format = line.back();
            } else if (tmp.rfind("EDGE_WEIGHT_SECTION", 0) == 0) {
                if (edge_weight_format == "FULL_MATRIX") {
                    Distance distance;
                    file >> distance;
                    for (LocationId location_id_1 = 0;
                            location_id_1 < number_of_locations;
                            ++location_id_1) {
                        for (LocationId location_id_2 = 0;
                                location_id_2 < number_of_locations;
                                ++location_id_2) {
                            file >> distance;
                            if (distance == -1)
                                add_predecessor(location_id_1, location_id_2);
                            if (location_id_2 == location_id_1
                                    || distance == -1)
                                distance = std::numeric_limits<Distance>::max();
                            set_distance(
                                    location_id_1,
                                    location_id_2,
                                    distance);
                        }
                    }
                } else {
                    std::cerr << "\033[31m" << "ERROR, EDGE_WEIGHT_FORMAT \"" << edge_weight_format << "\" not implemented." << "\033[0m" << std::endl;
                }
            } else if (tmp.rfind("EOF", 0) == 0) {
                break;
            } else {
                std::cerr << "\033[31m" << "ERROR, ENTRY \"" << line[0] << "\" not implemented." << "\033[0m" << std::endl;
            }
        }

        // Compute distances.
        if (edge_weight_type == "EXPLICIT") {
        } else {
            std::cerr << "\033[31m" << "ERROR, EDGE_WEIGHT_TYPE \"" << edge_weight_type << "\" not implemented." << "\033[0m" << std::endl;
        }
    }

    /** Read a file in 'soplib' format. */
    void read_soplib(std::ifstream& file)
    {
        std::string tmp;
        std::vector<std::string> line;
        for (LocationId location_id_1 = 0; getline(file, tmp); ++location_id_1) {
            line = optimizationtools::split(tmp, '\t');
            if (location_id_1 == 0) {
                LocationId n = line.size();
                locations_ = std::vector<Location>(n);
                distances_ = std::vector<std::vector<Distance>>(n, std::vector<Distance>(n, -1));
            }
            for (LocationId location_id_2 = 0;
                    location_id_2 < number_of_locations();
                    ++location_id_2) {
                Distance distance = std::stol(line[location_id_2]);
                if (distance == -1)
                    add_predecessor(location_id_1, location_id_2);
                if (location_id_2 == location_id_1 || distance == -1)
                    distance = std::numeric_limits<Distance>::max();
                set_distance(
                        location_id_1,
                        location_id_2,
                        distance);
            }
        }
    }

    /*
     * Private attributes
     */

    /** Locations. */
    std::vector<Location> locations_;

    /** Distances. */
    std::vector<std::vector<Distance>> distances_;

    /*
     * Computed attributes
     */

    /** Maximum distance. */
    Distance distance_max_ = 0;

};

}

}

