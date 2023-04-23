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

#pragma once

#include "optimizationtools/containers/indexed_set.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>

namespace orproblems
{

namespace quadraticassignment
{

using FacilityId = int64_t;
using LocationId = int64_t;
using Cost = int64_t;

/**
 * Instance class for a 'quadraticassignment' problem.
 */
class Instance
{

public:

    /*
     * Constructors and destructor
     */

    /** Constructor to build an instance manually. */
    Instance(FacilityId number_of_facilities):
        flows_(number_of_facilities, std::vector<Cost>(number_of_facilities, 0)),
        distances_(number_of_facilities, std::vector<Cost>(number_of_facilities, 0))
    { }

    /** Set the flow between two facilities. */
    void set_flow(
            FacilityId facility_id_1,
            FacilityId facility_id_2,
            Cost flow)
    {
        flows_[facility_id_1][facility_id_2] = flow;
    }

    /** Set the distance between two locations. */
    void set_distance(
            LocationId location_id_1,
            LocationId location_id_2,
            Cost distance)
    {
        distances_[location_id_1][location_id_2] = distance;
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

        if (format == "" || format == "qaplib") {
            read_qaplib(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    /*
     * Getters
     */

    /** Get the number of facilities. */
    inline FacilityId number_of_facilities() const { return flows_.size(); }

    /** Get the flow between two facilities. */
    inline Cost flow(
            FacilityId facility_id_1,
            FacilityId facility_id_2) const
    {
        return flows_[facility_id_1][facility_id_2];
    }

    /** Get the distance between two locations. */
    inline Cost distance(
            LocationId location_id_1,
            LocationId location_id_2) const
    {
        return distances_[location_id_1][location_id_2];
    }

    /** Print the instance. */
    std::ostream& print(
            std::ostream& os,
            int verbose = 1) const
    {
        if (verbose >= 1) {
            os << "Number of facilities:  " << number_of_facilities() << std::endl;
        }

        if (verbose >= 2) {
            os << std::endl
                << std::setw(12) << "Fac. 1"
                << std::setw(12) << "Fac. 2"
                << std::setw(12) << "Flow"
                << std::endl
                << std::setw(12) << "------"
                << std::setw(12) << "------"
                << std::setw(12) << "----"
                << std::endl;
            for (FacilityId facility_id_1 = 0;
                    facility_id_1 < number_of_facilities();
                    ++facility_id_1) {
                for (FacilityId facility_id_2 = 0;
                        facility_id_2 < number_of_facilities();
                        ++facility_id_2) {
                    os
                        << std::setw(12) << facility_id_1
                        << std::setw(12) << facility_id_2
                        << std::setw(12) << flow(facility_id_1, facility_id_2)
                        << std::endl;
                }
            }
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
                    location_id_1 < number_of_facilities();
                    ++location_id_1) {
                for (LocationId location_id_2 = 0;
                        location_id_2 < number_of_facilities();
                        ++location_id_2) {
                    os
                        << std::setw(12) << location_id_1
                        << std::setw(12) << location_id_2
                        << std::setw(12) << distance(location_id_1, location_id_2)
                        << std::endl;
                }
            }
        }

        return os;
    }

    /** Check a certificate. */
    std::pair<bool, Cost> check(
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
                << std::setw(12) << "Facility"
                << std::setw(12) << "Location"
                << std::endl
                << std::setw(12) << "--------"
                << std::setw(12) << "--------"
                << std::endl;
        }

        LocationId location_id = -1;
        optimizationtools::IndexedSet location_set(number_of_facilities());
        std::vector<LocationId> locations(number_of_facilities(), -1);
        LocationId number_of_duplicates = 0;
        FacilityId facility_id = 0;
        while (file >> location_id) {
            if (location_id < 0 || location_id >= number_of_facilities()) {
                if (verbose >= 2) {
                    os << "Invalid location: " << location_id << "."
                        << std::endl;
                }
                continue;
            }

            // Check duplicates.
            if (location_set.contains(location_id)) {
                number_of_duplicates++;
                if (verbose >= 2) {
                    os << "Location " << location_id
                        << " has already been assigned." << std::endl;
                }
            }
            location_set.add(location_id);

            locations[facility_id] = location_id;
            facility_id++;
            if (verbose >= 2) {
                os
                    << std::setw(12) << facility_id
                    << std::setw(12) << location_id
                    << std::endl;
            }
        }

        // Compute cost.
        Cost cost = 0;
        for (FacilityId facility_id_1 = 0;
                facility_id_1 < number_of_facilities();
                ++facility_id_1) {
            for (FacilityId facility_id_2 = 0;
                    facility_id_2 < number_of_facilities();
                    ++facility_id_2) {
                if (locations[facility_id_1] != -1
                        && locations[facility_id_2] != -1) {
                    cost += flow(facility_id_1, facility_id_2)
                        * distance(
                                locations[facility_id_1],
                                locations[facility_id_2]);
                }
            }
        }

        bool feasible
            = (number_of_duplicates == 0)
            && (location_set.size() == number_of_facilities());
        if (verbose >= 2)
            os << std::endl;
        if (verbose >= 1) {
            os
                << "Number of facilities:       " << location_set.size() << " / " << number_of_facilities() << std::endl
                << "Number of duplicates:       " << number_of_duplicates << std::endl
                << "Feasible:                   " << feasible << std::endl
                << "Cost:                       " << cost << std::endl
                ;
        }
        return {feasible, cost};
    }

private:


    /*
     * Private methods
     */

    /** Read an instance from a file in 'qaplib' format. */
    void read_qaplib(std::ifstream& file)
    {
        FacilityId number_of_facilities = -1;
        file >> number_of_facilities;
        flows_ = std::vector<std::vector<Cost>>(
                number_of_facilities,
                std::vector<Cost>(number_of_facilities, 0));
        distances_ = std::vector<std::vector<Cost>>(
                number_of_facilities,
                std::vector<Cost>(number_of_facilities, 0));

        Cost cost = -1;
        for (FacilityId facility_id_1 = 0;
                facility_id_1 < number_of_facilities;
                ++facility_id_1) {
            for (FacilityId facility_id_2 = 0;
                    facility_id_2 < number_of_facilities;
                    ++facility_id_2) {
                file >> cost;
                set_flow(facility_id_1, facility_id_2, cost);
            }
        }
        for (LocationId location_id_1 = 0;
                location_id_1 < number_of_facilities;
                ++location_id_1) {
            for (LocationId location_id_2 = 0;
                    location_id_2 < number_of_facilities;
                    ++location_id_2) {
                file >> cost;
                set_distance(location_id_1, location_id_2, cost);
            }
        }
    }

    /*
     * Private attributes
     */

    /** Flows between facilities. */
    std::vector<std::vector<Cost>> flows_;

    /** Distances between locations. */
    std::vector<std::vector<Cost>> distances_;

};

}

}

