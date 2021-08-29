#pragma once

#include "optimizationtools/utils.hpp"
#include "optimizationtools/indexed_set.hpp"

/**
 * Sequential Ordering Problem.
 * (Asymmetric Travelling Salesman Problem with Precedence Constraints)
 *
 * Input:
 * - n cities and an n×n matrix containing the distances between each pair of
 *   cities (not necessarily symmetric)
 * - a directed acyclic graph such that each vertex represents a city and an
 *   arc from vertex j1 to vertex j2 indicates that city j1 must be visited
 *   before city j2
 * Problem:
 * - find a route from city 1 such that:
 *   - each city is visited exactly once
 *   - precedence constraints are satisfied
 * Objective:
 * - minimize the total length of the tour
 *
 */

namespace orproblems
{

namespace sequentialordering
{

typedef int64_t VertexId;
typedef int64_t VertexPos;
typedef int64_t Distance;

struct Location
{
    std::vector<VertexId> predecessors;
};

class Instance
{

public:

    /** Create an instance manually. */
    Instance(VertexId n):
        locations_(n),
        distances_(n, std::vector<Distance>(n, -1))
    {
        for (VertexId j = 0; j < n; ++j)
            distances_[j][j] = 0;
    }
    /** Set the distance between vertex 'j1' and vertex 'j2' to 'd'. */
    void set_distance(VertexId j1, VertexId j2, Distance d)
    {
        check_vertex_index(j1);
        check_vertex_index(j2);
        distances_[j1][j2] = d;
        distance_max_ = std::max(distance_max_, d);
    }
    /** Add vertex 'j2' as predecessor of vertex 'j1'. */
    void add_predecessor(VertexId j1, VertexId j2)
    {
        check_vertex_index(j1);
        check_vertex_index(j2);
        locations_[j1].predecessors.push_back(j2);
    }

    /** Create an instance from a file. */
    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");

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

    /** Destructor. */
    virtual ~Instance() { }

    /** Get the number of vertices */
    inline VertexId number_of_vertices() const { return locations_.size(); }
    /** Get the distance between vertex 'j1' and vertex 'j2'. */
    inline Distance distance(VertexId j1, VertexId j2) const { return distances_[j1][j2]; }
    /** Get the predecessors of vertex 'j'. */
    inline const std::vector<VertexId>& predecessors(VertexId j) const { return locations_[j].predecessors; }
    /** Get the maximum distance between two vertices. */
    inline Distance maximum_distance() const { return distance_max_; }

    /** Check a certificate file 'certificate_path'. */
    std::pair<bool, Distance> check(std::string certificate_path)
    {
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
        VertexPos number_of_precedence_violations = 0;
        Distance total_distance = 0;
        while (file >> j) {
            if (vertices.contains(j)) {
                duplicates++;
                std::cout << "Vertex " << j << " has already been visited." << std::endl;
            }
            // Check predecessors.
            for (VertexId j_pred: predecessors(j)) {
                if (!vertices.contains(j_pred)) {
                    number_of_precedence_violations++;
                    std::cout << std::endl << "Vertex " << j << " depends on vertex "
                        << j_pred << " which has not been visited yet."
                        << std::endl;
                }
            }
            vertices.add(j);
            total_distance += distance(j_prec, j);
            std::cout << "Job: " << j
                << "; Distance: " << distance(j_prec, j)
                << "; Total distance: " << total_distance
                << std::endl;
            j_prec = j;
        }
        bool feasible
            = (vertices.size() == n)
            && (duplicates == 0)
            && (number_of_precedence_violations == 0);

        std::cout << "---" << std::endl;
        std::cout << "Number of Vertices:               " << vertices.size() << " / " << n  << std::endl;
        std::cout << "Duplicates:                       " << duplicates << std::endl;
        std::cout << "Number of precedence violations:  " << number_of_precedence_violations << std::endl;
        std::cout << "Feasible:                         " << feasible << std::endl;
        std::cout << "Total distance:                   " << total_distance << std::endl;
        return {feasible, total_distance};
    }

    /** Check if vertex index 'j' is within the correct range. */
    inline void check_vertex_index(VertexId j)
    {
        if (j < 0 || j >= number_of_vertices())
            throw std::out_of_range(
                    "Invalid vertex index: \"" + std::to_string(j) + "\"."
                    + " Vertex indices should belong to [0, "
                    + std::to_string(number_of_vertices() - 1) + "].");
    }

private:

    /** Read a file in 'tsplib' format. */
    void read_tsplib(std::ifstream& file)
    {
        std::string tmp;
        std::vector<std::string> line;
        VertexId n = -1;
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
                n = std::stol(line.back());
                locations_ = std::vector<Location>(n);
                distances_ = std::vector<std::vector<Distance>>(n, std::vector<Distance>(n, -1));
                for (VertexId j = 0; j < n; ++j)
                    distances_[j][j] = std::numeric_limits<Distance>::max();
            } else if (tmp.rfind("EDGE_WEIGHT_TYPE", 0) == 0) {
                edge_weight_type = line.back();
            } else if (tmp.rfind("EDGE_WEIGHT_FORMAT", 0) == 0) {
                edge_weight_format = line.back();
            } else if (tmp.rfind("EDGE_WEIGHT_SECTION", 0) == 0) {
                if (edge_weight_format == "FULL_MATRIX") {
                    Distance d;
                    file >> d;
                    for (VertexId j1 = 0; j1 < n; ++j1) {
                        for (VertexId j2 = 0; j2 < n; ++j2) {
                            file >> d;
                            if (d == -1)
                                add_predecessor(j1, j2);
                            if (j2 == j1 || d == -1)
                                d = std::numeric_limits<Distance>::max();
                            set_distance(j1, j2, d);
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
        for (VertexId j1 = 0; getline(file, tmp); ++j1) {
            line = optimizationtools::split(tmp, '\t');
            if (j1 == 0) {
                VertexId n = line.size();
                locations_ = std::vector<Location>(n);
                distances_ = std::vector<std::vector<Distance>>(n, std::vector<Distance>(n, -1));
            }
            for (VertexId j2 = 0; j2 < number_of_vertices(); ++j2) {
                Distance d = std::stol(line[j2]);
                if (d == -1)
                    add_predecessor(j1, j2);
                if (j2 == j1 || d == -1)
                    d = std::numeric_limits<Distance>::max();
                set_distance(j1, j2, d);
            }
        }
    }

    std::vector<Location> locations_;
    std::vector<std::vector<Distance>> distances_;
    Distance distance_max_ = 0;

};

std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "number of vertices: " << instance.number_of_vertices() << std::endl;
    for (VertexId j = 0; j < instance.number_of_vertices(); ++j) {
        os << "vertex: " << j
            << "; predecessors:";
        for (VertexId j_pred: instance.predecessors(j))
            os << " " << j_pred;
        os << std::endl;
    }
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

