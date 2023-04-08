/**
 * Traveling Salesman Problem.
 *
 * Input:
 * - n locations
 * - an n×n symmetric matrix containing the distances between each pair of
 *   locations
 * Problem:
 * - find a tour from location 1 to location 1 such that
 *   - each other location is visited exactly once
 * Objective:
 * - minimize the total length of the tour
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

namespace travelingsalesman
{

using VertexId = int64_t;
using VertexPos = int64_t;
using Distance = int64_t;

/*
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
};

/**
 * Instance class for a 'travelingsalesman' problem.
 */
class Instance
{

public:

    /*
     * Constructors and destructor
     */

    /** Constructor to build an instance manually. */
    Instance(VertexId number_of_vertices):
        locations_(number_of_vertices),
        distances_(number_of_vertices, std::vector<Distance>(number_of_vertices, -1))
    {
        for (VertexId vertex_id = 0; vertex_id < number_of_vertices; ++vertex_id)
            distances_[vertex_id][vertex_id] = 0;
    }

    /** Set the coordinates of a vertex. */
    void set_xy(
            VertexId vertex_id,
            double x,
            double y,
            double z = -1)
    {
        locations_[vertex_id].x = x;
        locations_[vertex_id].y = y;
        locations_[vertex_id].z = z;
    }

    /** Set the distance between two vertices. */
    void set_distance(
            VertexId vertex_id_1,
            VertexId vertex_id_2,
            Distance distance)
    {
        distances_[vertex_id_1][vertex_id_2] = distance;
        distances_[vertex_id_2][vertex_id_1] = distance;
        distance_max_ = std::max(distance_max_, distance);
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
        if (format == "" || format == "tsplib") {
            read_tsplib(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    /*
     * Getters
     */

    /** Get the number of vertices. */
    inline VertexId number_of_vertices() const { return locations_.size(); }

    /** Get the x-coordinate of a vertex. */
    inline double x(VertexId vertex_id) const { return locations_[vertex_id].x; }

    /** Get the y-coordinate of a vertex. */
    inline double y(VertexId vertex_id) const { return locations_[vertex_id].y; }

    /** Get the distance between two vertices. */
    inline Distance distance(
            VertexId vertex_id_1,
            VertexId vertex_id_2) const
    {
        return distances_[vertex_id_1][vertex_id_2];
    }

    /** Get the maximum distance between two vertices. */
    inline Distance maximum_distance() const { return distance_max_; }

    /** Print the instance. */
    std::ostream& print(
            std::ostream& os,
            int verbose = 1) const
    {
        if (verbose >= 1) {
            os << "Number of vertices:  " << number_of_vertices() << std::endl;
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
            for (VertexId vertex_id_1 = 0; vertex_id_1 < number_of_vertices(); ++vertex_id_1) {
                for (VertexId vertex_id_2 = vertex_id_1 + 1; vertex_id_2 < number_of_vertices(); ++vertex_id_2) {
                    os
                        << std::setw(12) << vertex_id_1
                        << std::setw(12) << vertex_id_2
                        << std::setw(12) << distance(vertex_id_1, vertex_id_2)
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

        VertexId vertex_id_pred = 0;
        VertexId vertex_id = -1;
        optimizationtools::IndexedSet vertices(number_of_vertices());
        vertices.add(0);
        VertexPos number_of_duplicates = 0;
        Distance total_distance = 0;
        while (file >> vertex_id) {
            if (vertices.contains(vertex_id)) {
                number_of_duplicates++;
                if (verbose == 2)
                    os << "Vertex " << vertex_id << " has already been visited." << std::endl;
            }
            vertices.add(vertex_id);
            total_distance += distance(vertex_id_pred, vertex_id);
            if (verbose == 2)
                os << "Vertex: " << vertex_id
                    << "; Distance: " << distance(vertex_id_pred, vertex_id)
                    << "; Total distance: " << total_distance
                    << std::endl;
            vertex_id_pred = vertex_id;
        }
        total_distance += distance(vertex_id_pred, 0);

        bool feasible
            = (vertices.size() == number_of_vertices())
            && (number_of_duplicates == 0);
        if (verbose == 2)
            os << std::endl;
        if (verbose >= 1) {
            os << "Number of vertices:     " << vertices.size() << " / " << number_of_vertices()  << std::endl;
            os << "Number of duplicates:   " << number_of_duplicates << std::endl;
            os << "Feasible:               " << feasible << std::endl;
            os << "Total distance:         " << total_distance << std::endl;
        }
        return {feasible, total_distance};
    }

private:

    /*
     * Private methods
     */

    /** Read an instance from a file in 'tsplib' format. */
    void read_tsplib(std::ifstream& file)
    {
        std::string tmp;
        std::vector<std::string> line;
        VertexId n = -1;
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
                distances_ = std::vector<std::vector<Distance>>(n, std::vector<Distance>(n, -1));
            } else if (tmp.rfind("EDGE_WEIGHT_TYPE", 0) == 0) {
                edge_weight_type = line.back();
            } else if (tmp.rfind("EDGE_WEIGHT_FORMAT", 0) == 0) {
                edge_weight_format = line.back();
            } else if (tmp.rfind("NODE_COORD_TYPE", 0) == 0) {
                node_coord_type = line.back();
            } else if (tmp.rfind("EDGE_WEIGHT_SECTION", 0) == 0) {
                if (edge_weight_format == "UPPER_ROW") {
                    Distance d;
                    for (VertexId j1 = 0; j1 < n - 1; ++j1) {
                        for (VertexId j2 = j1 + 1; j2 < n; ++j2) {
                            file >> d;
                            set_distance(j1, j2, d);
                        }
                    }
                } else if (edge_weight_format == "LOWER_ROW") {
                    Distance d;
                    for (VertexId j1 = 1; j1 < n; ++j1) {
                        for (VertexId j2 = 0; j2 < j1; ++j2) {
                            file >> d;
                            set_distance(j1, j2, d);
                        }
                    }
                } else if (edge_weight_format == "UPPER_DIAG_ROW") {
                    Distance d;
                    for (VertexId j1 = 0; j1 < n; ++j1) {
                        for (VertexId j2 = j1; j2 < n; ++j2) {
                            file >> d;
                            set_distance(j1, j2, d);
                        }
                    }
                } else if (edge_weight_format == "LOWER_DIAG_ROW") {
                    Distance d;
                    for (VertexId j1 = 0; j1 < n; ++j1) {
                        for (VertexId j2 = 0; j2 <= j1; ++j2) {
                            file >> d;
                            set_distance(j1, j2, d);
                        }
                    }
                } else if (edge_weight_format == "FULL_MATRIX") {
                    Distance d;
                    for (VertexId j1 = 0; j1 < n; ++j1) {
                        for (VertexId j2 = 0; j2 < n; ++j2) {
                            file >> d;
                            set_distance(j1, j2, d);
                        }
                    }
                } else {
                    std::cerr << "\033[31m" << "ERROR, EDGE_WEIGHT_FORMAT \"" << edge_weight_format << "\" not implemented." << "\033[0m" << std::endl;
                }
            } else if (tmp.rfind("NODE_COORD_SECTION", 0) == 0) {
                if (node_coord_type == "TWOD_COORDS") {
                    VertexId tmp;
                    double x, y;
                    for (VertexId j = 0; j < n; ++j) {
                        file >> tmp >> x >> y;
                        set_xy(j, x, y);
                    }
                } else if (node_coord_type == "THREED_COORDS") {
                    VertexId tmp;
                    double x, y, z;
                    for (VertexId j = 0; j < n; ++j) {
                        file >> tmp >> x >> y >> z;
                        set_xy(j, x, y, z);
                    }
                }
            } else if (tmp.rfind("DISPLAY_DATA_SECTION", 0) == 0) {
                VertexId tmp;
                double x, y;
                for (VertexId j = 0; j < n; ++j) {
                    file >> tmp >> x >> y;
                    set_xy(j, x, y);
                }
            } else if (tmp.rfind("EOF", 0) == 0) {
                break;
            } else {
                std::cerr << "\033[31m" << "ERROR, ENTRY \"" << line[0] << "\" not implemented." << "\033[0m" << std::endl;
            }
        }

        // Compute distances.
        if (edge_weight_type == "EUC_2D") {
            for (VertexId j1 = 0; j1 < n; ++j1) {
                for (VertexId j2 = j1 + 1; j2 < n; ++j2) {
                    double xd = x(j2) - x(j1);
                    double yd = y(j2) - y(j1);
                    Distance d = std::round(std::sqrt(xd * xd + yd * yd));
                    set_distance(j1, j2, d);
                }
            }
        } else if (edge_weight_type == "CEIL_2D") {
            for (VertexId j1 = 0; j1 < n; ++j1) {
                for (VertexId j2 = j1 + 1; j2 < n; ++j2) {
                    double xd = x(j2) - x(j1);
                    double yd = y(j2) - y(j1);
                    Distance d = std::ceil(std::sqrt(xd * xd + yd * yd));
                    set_distance(j1, j2, d);
                }
            }
        } else if (edge_weight_type == "GEO") {
            std::vector<double> latitudes(n, 0);
            std::vector<double> longitudes(n, 0);
            for (VertexId j = 0; j < n; ++j) {
                double pi = 3.141592;
                int deg_x = std::round(x(j));
                double min_x = x(j) - deg_x;
                latitudes[j] = pi * (deg_x + 5.0 * min_x / 3.0) / 180.0;
                int deg_y = std::round(y(j));
                double min_y = y(j) - deg_y;
                longitudes[j] = pi * (deg_y + 5.0 * min_y / 3.0) / 180.0;
            }
            double rrr = 6378.388;
            for (VertexId j1 = 0; j1 < n; ++j1) {
                for (VertexId j2 = j1 + 1; j2 < n; ++j2) {
                    double q1 = cos(longitudes[j1] - longitudes[j2]);
                    double q2 = cos(latitudes[j1] - latitudes[j2]);
                    double q3 = cos(latitudes[j1] + latitudes[j2]);
                    Distance d = (Distance)(rrr * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);
                    set_distance(j1, j2, d);
                }
            }
        } else if (edge_weight_type == "ATT") {
            for (VertexId j1 = 0; j1 < n; ++j1) {
                for (VertexId j2 = j1 + 1; j2 < n; ++j2) {
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
        for (VertexId j = 0; j < n; ++j)
            distances_[j][j] = std::numeric_limits<Distance>::max();
    }

    /*
     * Private attributes
     */

    /** Locations. */
    std::vector<Location> locations_;

    /** Distances between locations. */
    std::vector<std::vector<Distance>> distances_;

    /** Maximum distance. */
    Distance distance_max_ = 0;
};

}

}

