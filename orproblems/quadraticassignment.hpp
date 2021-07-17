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

    Instance(FacilityId facility_number):
        flows_(facility_number, std::vector<Cost>(facility_number, 0)),
        distances_(facility_number, std::vector<Cost>(facility_number, 0))
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
        if (!file.good()) {
            std::cerr << "\033[31m" << "ERROR, unable to open file \"" << instance_path << "\"" << "\033[0m" << std::endl;
            assert(false);
            return;
        }
        if (format == "" || format == "qaplib") {
            read_qaplib(file);
        } else {
            std::cerr << "\033[31m" << "ERROR, unknown instance format \"" << format << "\"" << "\033[0m" << std::endl;
        }
        file.close();
    }

    virtual ~Instance() { }

    inline FacilityId facility_number() const { return flows_.size(); }
    inline Cost flow(FacilityId facility_id_1, FacilityId facility_id_2) const { return flows_[facility_id_1][facility_id_2]; }
    inline Cost distance(LocationId location_id_1, LocationId location_id_2) const { return distances_[location_id_1][location_id_2]; }

    std::pair<bool, Cost> check(std::string certificate_path)
    {
        std::ifstream file(certificate_path);
        if (!file.good()) {
            std::cerr << "\033[31m" << "ERROR, unable to open file \"" << certificate_path << "\"" << "\033[0m" << std::endl;
            assert(false);
            return {false, 0};
        }

        FacilityId n = facility_number();
        LocationId location_id = -1;
        optimizationtools::IndexedSet location_set(n);
        std::vector<LocationId> locations(n, -1);
        LocationId duplicates = 0;
        FacilityId facility_id = 0;
        while (file >> location_id) {
            if (location_set.contains(location_id)) {
                duplicates++;
                std::cout << "Location " << location_id << " already assigned." << std::endl;
            }
            location_set.add(location_id);
            locations[facility_id] = location_id;
            facility_id++;
            std::cout << "Facility: " << facility_id
                << "; Location: " << location_id
                << std::endl;
        }
        Cost cost = 0;
        for (FacilityId facility_id_1 = 0; facility_id_1 < n; ++facility_id_1)
            for (FacilityId facility_id_2 = 0; facility_id_2 < n; ++facility_id_2)
                cost += flow(facility_id_1, facility_id_2)
                    * distance(locations[facility_id_1], locations[facility_id_2]);
        bool feasible
            = (duplicates == 0)
            && (location_set.size() == n);
        std::cout << "---" << std::endl;
        std::cout << "Facilities:                 " << location_set.size() << " / " << n  << std::endl;
        std::cout << "Duplicates:                 " << duplicates << std::endl;
        std::cout << "Feasible:                   " << feasible << std::endl;
        std::cout << "Cost:                       " << cost << std::endl;
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

std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    FacilityId n = instance.facility_number();
    os << "facility number " << n << std::endl;
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

