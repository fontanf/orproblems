/**
 * Cutting Stock Problem.
 *
 * Input:
 * - a capacity c
 * - n items; for each item j = 1..n, a weight wⱼ and a demand qⱼ
 * Problem:
 * - pack all items such that the total weight of the items in a bin does not
 *   exceed the capacity.
 * Objective:
 * - minimize the number of bin used.
 *
 */

#pragma once

#include "optimizationtools/containers/indexed_set.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>

namespace orproblems
{

namespace cuttingstock
{

using ItemTypeId = int64_t;
using ItemPos = int64_t;
using Weight = int64_t;
using Demand = int64_t;
using BinId = int64_t;

/**
 * Structure for an item type.
 */
struct ItemType
{
    /** Weight of the item. */
    Weight weight;

    /** Demand of the item. */
    Demand demand;
};

/**
 * Instance class for a 'cuttingstock' problem.
 */
class Instance
{

public:


    /*
     * Constructors and destructor
     */

    /** Constructor to build an instance manually. */
    Instance() { }

    /** Set the capacity of the bins. */
    void set_capacity(Weight capacity) { capacity_ = capacity; }

    /** Add an item. */
    void add_item_type(
            Weight weight,
            Demand demand = 1)
    {
        ItemType item_type;
        item_type.weight = weight;
        item_type.demand = demand;
        item_types_.push_back(item_type);

        demand_max_ = std::max(demand_max_, demand);
        demand_sum_ += demand;
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
        if (format == "" || format == "bpplib_bpp") {
            read_bpplib_bpp(file);
        } else if (format == "bpplib_csp") {
            read_bpplib_csp(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    /*
     * Getters
     */

    /** Get the number of item types. */
    ItemTypeId number_of_item_types() const { return item_types_.size(); }

    /** Get the capacity. */
    Weight capacity() const { return capacity_; }

    /** Get an item type. */
    const ItemType& item_type(ItemTypeId item_type_id) const { return item_types_[item_type_id]; }

    /** Get the maximum demand. */
    Demand maximum_demand() const { return demand_max_; }

    /** Get the total demand. */
    Demand total_demand() const { return demand_sum_; }

    /** Print the instance. */
    std::ostream& print(
            std::ostream& os,
            int verbose = 1) const
    {
        if (verbose >= 1) {
            os
                << "Number of item_types:  " << number_of_item_types() << std::endl
                << "Capacity:              " << capacity() << std::endl
                ;
        }

        if (verbose >= 2) {
            os << std::endl
                << std::setw(12) << "Item type"
                << std::setw(12) << "Weight"
                << std::setw(12) << "Demand"
                << std::endl
                << std::setw(12) << "---------"
                << std::setw(12) << "------"
                << std::setw(12) << "------"
                << std::endl;
            for (ItemTypeId item_type_id = 0;
                    item_type_id < number_of_item_types();
                    ++item_type_id) {
                const ItemType& item_type = this->item_type(item_type_id);
                os
                    << std::setw(12) << item_type_id
                    << std::setw(12) << item_type.weight
                    << std::setw(12) << item_type.demand
                    << std::endl;
            }
        }

        return os;
    }

    /** Check a certificate. */
    std::pair<bool, BinId> check(
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
                << std::setw(12) << "Bin"
                << std::setw(12) << "Item type"
                << std::setw(12) << "Weight"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "---------"
                << std::setw(12) << "------"
                << std::endl;
        }

        std::vector<Demand> demands(number_of_item_types(), 0);
        BinId number_of_bins = -1;
        BinId bin_number_of_copies = -1;
        ItemPos bin_number_of_items = -1;
        ItemTypeId item_type_id = -1;
        Demand item_copies = -1;

        ItemPos number_of_unsatisfied_demands = 0;
        BinId number_of_overweighted_bins = 0;

        file >> number_of_bins;
        for (BinId bin_pos = 0; bin_pos < number_of_bins; ++bin_pos) {
            file >> bin_number_of_copies >> bin_number_of_items;

            Weight bin_weight = 0;
            for (ItemPos item_pos = 0;
                    item_pos < bin_number_of_items;
                    ++item_pos) {
                file >> item_type_id >> item_copies;
                demands[item_type_id] += bin_number_of_copies * item_copies;
                bin_weight += item_copies * item_type(item_type_id).weight;

                if (verbose >= 2) {
                    os
                        << std::setw(12) << number_of_bins
                        << std::setw(12) << item_type_id
                        << std::setw(12) << bin_weight
                        << std::endl;
                }
            }

            if (bin_weight > capacity()) {
                number_of_overweighted_bins++;
                if (verbose >= 2) {
                    os << "Bin " << number_of_bins - 1
                        << " is overloaded." << std::endl;
                }
            }
        }

        for (ItemTypeId item_type_id = 0;
                item_type_id < number_of_item_types();
                ++item_type_id) {
            if (demands[item_type_id] != item_type(item_type_id).demand) {
                number_of_unsatisfied_demands++;
                if (verbose >= 2)
                    os << "Item type " << item_type_id
                        << ", demand is not satisfied: "
                        << demands[item_type_id]
                        << " / " << item_type(item_type_id).demand
                        << "." << std::endl;
            }
        }

        bool feasible
            = (number_of_unsatisfied_demands == 0)
            && (number_of_overweighted_bins == 0);

        if (verbose >= 2)
            os << std::endl;
        if (verbose >= 1) {
            os
                << "Number of unsatisfied demands:  " << number_of_unsatisfied_demands  << std::endl
                << "Number of overweighted bins:    " << number_of_overweighted_bins << std::endl
                << "Feasible:                       " << feasible << std::endl
                << "Number of bins:                 " << number_of_bins << std::endl
                ;
        }
        return {feasible, number_of_bins};
    }

private:

    /*
     * Private methods
     */

    /** Read an instance from a file in 'bpplib_bpp' format. */
    void read_bpplib_bpp(std::ifstream& file)
    {
        ItemTypeId n;
        Weight c;
        file >> n >> c;
        set_capacity(c);
        Weight w;
        for (ItemTypeId j = 0; j < n; ++j) {
            file >> w;
            add_item_type(w);
        }
    }

    /** Read an instance from a file in 'bpplib_csp' format. */
    void read_bpplib_csp(std::ifstream& file)
    {
        ItemTypeId n;
        Weight c;
        file >> n >> c;
        set_capacity(c);
        Weight w;
        Demand q;
        for (ItemTypeId j = 0; j < n; ++j) {
            file >> w >> q;
            add_item_type(w, q);
        }
    }

    /*
     * Private attributes
     */

    /** Item types. */
    std::vector<ItemType> item_types_;

    /** Capacity. */
    Weight capacity_;

    /*
     * Computed attributes
     */

    /** Maximum demand. */
    Demand demand_max_ = 0;

    /** Total demand. */
    Demand demand_sum_ = 0;

};

}

}
