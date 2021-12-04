#pragma once

/**
 * Travelling Salesman Problem.
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

#include "optimizationtools/indexed_set.hpp"
#include "optimizationtools/utils.hpp"

#include <fstream>
#include <iostream>

namespace orproblems
{

namespace travellingsalesman
{

typedef int64_t VertexId;
typedef int64_t VertexPos;
typedef int64_t Distance;

struct Location
{
    double x;
    double y;
    double z;
};

class Instance
{

public:

    Instance(VertexId n):
        locations_(n),
        distances_(n, std::vector<Distance>(n, -1))
    {
        for (VertexId j = 0; j < n; ++j)
            distances_[j][j] = 0;
    }
    void set_xy(VertexId j, double x, double y, double z = -1)
    {
        locations_[j].x = x;
        locations_[j].y = y;
        locations_[j].z = z;
    }
    void set_distance(VertexId j1, VertexId j2, Distance d)
    {
        distances_[j1][j2] = d;
        distances_[j2][j1] = d;
        distance_max_ = std::max(distance_max_, d);
    }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        if (format == "" || format == "tsplib") {
            read_tsplib(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    virtual ~Instance() { }

    inline VertexId number_of_vertices() const { return locations_.size(); }
    inline double x(VertexId j) const { return locations_[j].x; }
    inline double y(VertexId j) const { return locations_[j].y; }
    inline Distance distance(VertexId j1, VertexId j2) const { return distances_[j1][j2]; }
    inline Distance maximum_distance() const { return distance_max_; }

    std::pair<bool, Distance> check(
            std::string certificate_path,
            int verbose = 1) const
    {
        // Initial display.
        if (verbose >= 1) {
            std::cout
                << "Checker" << std::endl
                << "-------" << std::endl;
        }

        std::ifstream file(certificate_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");

        VertexId n = number_of_vertices();
        VertexId j_prec = 0;
        VertexId j = -1;
        optimizationtools::IndexedSet vertices(n);
        vertices.add(0);
        VertexPos duplicates = 0;
        Distance total_distance = 0;
        while (file >> j) {
            if (vertices.contains(j)) {
                duplicates++;
                if (verbose == 2)
                    std::cout << "Vertex " << j << " has already been visited." << std::endl;
            }
            vertices.add(j);
            total_distance += distance(j_prec, j);
            if (verbose == 2)
                std::cout << "Vertex: " << j
                    << "; Distance: " << distance(j_prec, j)
                    << "; Total distance: " << total_distance
                    << std::endl;
            j_prec = j;
        }
        total_distance += distance(j_prec, 0);

        bool feasible
            = (vertices.size() == n)
            && (duplicates == 0);
        if (verbose == 2)
            std::cout << "---" << std::endl;
        if (verbose >= 1) {
            std::cout << "Number of vertices:     " << vertices.size() << " / " << n  << std::endl;
            std::cout << "Duplicates:             " << duplicates << std::endl;
            std::cout << "Feasible:               " << feasible << std::endl;
            std::cout << "Total distance:         " << total_distance << std::endl;
        }
        return {feasible, total_distance};
    }

private:

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

    std::vector<Location> locations_;
    std::vector<std::vector<Distance>> distances_;
    Distance distance_max_ = 0;

};

static inline std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "number of vertices " << instance.number_of_vertices() << std::endl;
    for (VertexId j1 = 0; j1 < instance.number_of_vertices(); ++j1) {
        os << "vertex " << j1 << ":";
        for (VertexId j2 = 0; j2 < instance.number_of_vertices(); ++j2)
            os << " " << instance.distance(j1, j2);
        os << std::endl;
    }
    return os;
}

}

}

