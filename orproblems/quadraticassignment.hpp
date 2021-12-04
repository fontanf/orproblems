#pragma once

/**
 * Quadratic Assignment Problem.
 *
 * Input:
 * - TODO
 * Problem:
 * - TODO
 * Objective:
 * - TODO
 *
 */

#include "optimizationtools/indexed_set.hpp"

namespace orproblems
{

namespace quadraticassignment
{

using FacilityId = int64_t;
using LocationId = int64_t;
using Cost = int64_t;

class Instance
{

public:

    Instance(FacilityId number_of_facilities):
        flows_(number_of_facilities, std::vector<Cost>(number_of_facilities, 0)),
        distances_(number_of_facilities, std::vector<Cost>(number_of_facilities, 0))
    { }
    void set_flow(FacilityId facility_id_1, FacilityId facility_id_2, Cost flow)
    {
        flows_[facility_id_1][facility_id_2] = flow;
    }
    void set_distance(LocationId location_id_1, LocationId location_id_2, Cost distance)
    {
        distances_[location_id_1][location_id_2] = distance;
    }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");

        if (format == "" || format == "qaplib") {
            read_qaplib(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    virtual ~Instance() { }

    inline FacilityId number_of_facilities() const { return flows_.size(); }
    inline Cost flow(FacilityId facility_id_1, FacilityId facility_id_2) const { return flows_[facility_id_1][facility_id_2]; }
    inline Cost distance(LocationId location_id_1, LocationId location_id_2) const { return distances_[location_id_1][location_id_2]; }

    std::pair<bool, Cost> check(
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

        FacilityId n = number_of_facilities();
        LocationId location_id = -1;
        optimizationtools::IndexedSet location_set(n);
        std::vector<LocationId> locations(n, -1);
        LocationId duplicates = 0;
        FacilityId facility_id = 0;
        while (file >> location_id) {
            if (location_id < 0 || location_id >= number_of_facilities()) {
                if (verbose == 2)
                    std::cout << "Invalid location: " << location_id << "." << std::endl;
                continue;
            }
            if (location_set.contains(location_id)) {
                duplicates++;
                if (verbose == 2)
                    std::cout << "Location " << location_id << " already assigned." << std::endl;
            }
            location_set.add(location_id);
            locations[facility_id] = location_id;
            facility_id++;
            if (verbose == 2)
                std::cout << "Facility: " << facility_id
                    << "; Location: " << location_id
                    << std::endl;
        }
        Cost cost = 0;
        for (FacilityId facility_id_1 = 0; facility_id_1 < n; ++facility_id_1)
            for (FacilityId facility_id_2 = 0; facility_id_2 < n; ++facility_id_2)
                if (locations[facility_id_1] != -1
                        && locations[facility_id_2] != -1)
                    cost += flow(facility_id_1, facility_id_2)
                        * distance(
                                locations[facility_id_1],
                                locations[facility_id_2]);

        bool feasible
            = (duplicates == 0)
            && (location_set.size() == n);
        if (verbose == 2)
            std::cout << "---" << std::endl;
        if (verbose >= 1) {
            std::cout << "Facilities:                 " << location_set.size() << " / " << n  << std::endl;
            std::cout << "Duplicates:                 " << duplicates << std::endl;
            std::cout << "Feasible:                   " << feasible << std::endl;
            std::cout << "Cost:                       " << cost << std::endl;
        }
        return {feasible, cost};
    }

private:

    void read_qaplib(std::ifstream& file)
    {
        FacilityId n = -1;
        file >> n;
        flows_ = std::vector<std::vector<Cost>>(n, std::vector<Cost>(n, 0));
        distances_ = std::vector<std::vector<Cost>>(n, std::vector<Cost>(n, 0));

        Cost c = -1;
        for (FacilityId facility_id_1 = 0; facility_id_1 < n; ++facility_id_1) {
            for (FacilityId facility_id_2 = 0; facility_id_2 < n; ++facility_id_2) {
                file >> c;
                set_flow(facility_id_1, facility_id_2, c);
            }
        }
        for (LocationId location_id_1 = 0; location_id_1 < n; ++location_id_1) {
            for (LocationId location_id_2 = 0; location_id_2 < n; ++location_id_2) {
                file >> c;
                set_distance(location_id_1, location_id_2, c);
            }
        }
    }

    std::vector<std::vector<Cost>> flows_;
    std::vector<std::vector<Cost>> distances_;

};

static inline std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    FacilityId n = instance.number_of_facilities();
    os << "number of facilities " << n << std::endl;
    os << "flows" << std::endl;
    for (FacilityId facility_id_1 = 0; facility_id_1 < n; ++facility_id_1) {
        for (FacilityId facility_id_2 = 0; facility_id_2 < n; ++facility_id_2)
            os << instance.flow(facility_id_1, facility_id_2) << " ";
        os << std::endl;
    }
    os << "distances" << std::endl;
    for (LocationId location_id_1 = 0; location_id_1 < n; ++location_id_1) {
        for (LocationId location_id_2 = 0; location_id_2 < n; ++location_id_2)
            os << instance.distance(location_id_1, location_id_2) << " ";
        os << std::endl;
    }
    return os;
}

}

}

