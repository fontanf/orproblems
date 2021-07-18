#pragma once

#include "optimizationtools/utils.hpp"
#include "optimizationtools/sorted_on_demand_array.hpp"
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
 * Tree search:
 * - forward branching
 * - guide: current length + distance to the closest next child
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

    Instance(VertexId n):
        locations_(n),
        distances_(n, std::vector<Distance>(n, -1))
    {
        for (VertexId j = 0; j < n; ++j)
            distances_[j][j] = 0;
    }
    void set_distance(VertexId j1, VertexId j2, Distance d)
    {
        distances_[j1][j2] = d;
        distance_max_ = std::max(distance_max_, d);
    }
    void add_predecessor(VertexId j1, VertexId j2)
    {
        locations_[j1].predecessors.push_back(j2);
    }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            std::cerr << "\033[31m" << "ERROR, unable to open file \"" << instance_path << "\"" << "\033[0m" << std::endl;
            assert(false);
            return;
        }
        if (format == "" || format == "tsplib") {
            read_tsplib(file);
        } else if (format == "soplib") {
            read_soplib(file);
        } else {
            std::cerr << "\033[31m" << "ERROR, unknown instance format \"" << format << "\"" << "\033[0m" << std::endl;
        }
        file.close();
    }

    virtual ~Instance() { }

    inline VertexId vertex_number() const { return locations_.size(); }
    inline Distance distance(VertexId j1, VertexId j2) const { return distances_[j1][j2]; }
    inline const std::vector<VertexId>& predecessors(VertexId j) const { return locations_[j].predecessors; }
    inline Distance maximum_distance() const { return distance_max_; }

    std::pair<bool, Distance> check(std::string certificate_path)
    {
        std::ifstream file(certificate_path);
        if (!file.good()) {
            std::cerr << "\033[31m" << "ERROR, unable to open file \"" << certificate_path << "\"" << "\033[0m" << std::endl;
            assert(false);
            return {false, 0};
        }

        VertexId n = vertex_number();
        VertexId j_prec = 0;
        VertexId j = -1;
        optimizationtools::IndexedSet vertices(n);
        vertices.add(0);
        VertexPos duplicates = 0;
        VertexPos precedence_violation_number = 0;
        Distance total_distance = 0;
        while (file >> j) {
            if (vertices.contains(j)) {
                duplicates++;
                std::cout << "Vertex " << j << " has already been visited." << std::endl;
            }
            // Check predecessors.
            for (VertexId j_pred: predecessors(j)) {
                if (!vertices.contains(j_pred)) {
                    precedence_violation_number++;
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
            && (precedence_violation_number == 0);

        std::cout << "---" << std::endl;
        std::cout << "Vertices number:              " << vertices.size() << " / " << n  << std::endl;
        std::cout << "Duplicates:                   " << duplicates << std::endl;
        std::cout << "Precedence violation number:  " << precedence_violation_number << std::endl;
        std::cout << "Feasible:                     " << feasible << std::endl;
        std::cout << "Total distance:               " << total_distance << std::endl;
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
            for (VertexId j2 = 0; j2 < vertex_number(); ++j2) {
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
    os << "vertex number: " << instance.vertex_number() << std::endl;
    for (VertexId j = 0; j < instance.vertex_number(); ++j) {
        os << "vertex: " << j
            << "; predecessors:";
        for (VertexId j_pred: instance.predecessors(j))
            os << " " << j_pred;
        os << std::endl;
    }
    for (VertexId j1 = 0; j1 < instance.vertex_number(); ++j1) {
        os << "vertex " << j1 << ":";
        for (VertexId j2 = 0; j2 < instance.vertex_number(); ++j2)
            os << " " << instance.distance(j1, j2);
        os << std::endl;
    }
    return os;
}

}

}

