/**
 * Bin Packing Problem with Conflicts.
 *
 * Input:
 * - a capacity c
 * - n items; for each item j = 1..n, a weight wⱼ
 * - a graph G such that each node corresponds to an item
 * Problem:
 * - Pack all items into bins such that:
 *   - the total weight of the items of a bin does not exceed the capacity c
 *   - if there exists an edge between vertex j₁ and vertex j₂ in G, then item
 *     j₁ and item j₂ must not be in the same bin
 * Objective:
 * - Minimize the number of bin used.
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

namespace binpackingwithconflicts
{

using ItemId = int64_t;
using Weight = int64_t;
using BinId = int64_t;

/**
 * Structure for an item.
 */
struct Item
{
    /** Weight of the item. */
    Weight weight;

    /** Conflicting items. */
    std::vector<ItemId> neighbors;
};

/**
 * Instance class for a 'binpackingwithconflicts' problem.
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
    void add_item(Weight weight)
    {
        Item item;
        item.weight = weight;
        items_.push_back(item);
    }

    /** Add a conflict. */
    void add_conflict(
            ItemId item_id_1,
            ItemId item_id_2)
    {
        assert(item_id_1 >= 0);
        assert(item_id_2 >= 0);
        assert(item_id_1 < number_of_items());
        assert(item_id_2 < number_of_items());
        items_[item_id_1].neighbors.push_back(item_id_2);
        items_[item_id_2].neighbors.push_back(item_id_1);
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

        if (format == "" || format == "default") {
            read_default(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    /*
     * Getters
     */

    /** Get the number of items. */
    ItemId number_of_items() const { return items_.size(); }

    /** Get an item. */
    const Item& item(ItemId item_id) const { return items_[item_id]; }

    /** Get the capacity of the bins. */
    Weight capacity() const { return capacity_; }

    /** Print the instance. */
    std::ostream& print(
            std::ostream& os,
            int verbose = 1) const
    {
        if (verbose >= 1) {
            os << "Number of items:  " << number_of_items() << std::endl;
            os << "Capacity:         " << capacity() << std::endl;
        }

        // Print items.
        if (verbose >= 2) {
            os << std::endl
                << std::setw(12) << "Item"
                << std::setw(12) << "Weight"
                << std::setw(12) << "# confl."
                << std::endl
                << std::setw(12) << "----"
                << std::setw(12) << "------"
                << std::setw(12) << "--------"
                << std::endl;
            for (ItemId item_id = 0; item_id < number_of_items(); ++item_id) {
                const Item& item = this->item(item_id);
                os
                    << std::setw(12) << item_id
                    << std::setw(12) << item.weight
                    << std::setw(12) << item.neighbors.size()
                    << std::endl;
            }
        }

        // Print conflicts.
        if (verbose >= 3) {
            os << std::endl
                << std::setw(12) << "Item 1"
                << std::setw(12) << "Item 2"
                << std::endl
                << std::setw(12) << "------"
                << std::setw(12) << "------"
                << std::endl;
            for (ItemId item_id = 0; item_id < number_of_items(); ++item_id) {
                for (ItemId item_id_neighbor: item(item_id).neighbors) {
                    os
                        << std::setw(12) << item_id
                        << std::setw(12) << item_id_neighbor
                        << std::endl;
                }
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
                << std::setw(12) << "Item"
                << std::setw(12) << "Weight"
                << std::endl
                << std::setw(12) << "---"
                << std::setw(12) << "----"
                << std::setw(12) << "------"
                << std::endl;
        }

        BinId number_of_bins;
        optimizationtools::IndexedSet items(number_of_items());
        ItemId current_bin_number_of_items;
        optimizationtools::IndexedSet current_bin_items(number_of_items());
        ItemId item_id = -1;

        ItemId number_of_duplicates = 0;
        BinId number_of_overweighted_bins = 0;
        ItemId number_of_conflict_violations = 0;

        file >> number_of_bins;
        for (BinId bin_pos = 0; bin_pos < number_of_bins; ++bin_pos) {
            Weight weight = 0;
            current_bin_items.clear();
            file >> current_bin_number_of_items;
            for (ItemId item_pos = 0;
                    item_pos < current_bin_number_of_items;
                    ++item_pos) {
                file >> item_id;
                const Item& item = this->item(item_id);

                // Check conflicts.
                for (ItemId item_id_neighbor: item.neighbors) {
                    if (current_bin_items.contains(item_id_neighbor)) {
                        number_of_conflict_violations++;
                        if (verbose >= 2) {
                            os << "Item " << item_id
                                << " is packed with conflict item "
                                << item_id_neighbor << "." << std::endl;
                        }
                    }
                }
                current_bin_items.add(item_id);

                // Check duplicates.
                if (items.contains(item_id)) {
                    number_of_duplicates++;
                    if (verbose >= 2) {
                        os << "Item " << item_id
                            << " has already been packed." << std::endl;
                    }
                }
                items.add(item_id);

                weight += item.weight;

                if (verbose >= 2) {
                    os
                        << std::setw(12) << bin_pos
                        << std::setw(12) << item_id
                        << std::setw(12) << weight
                        << std::endl;
                }
            }

            // Check capacity.
            if (weight > capacity()) {
                number_of_overweighted_bins++;
                if (verbose >= 2) {
                    os << "Bin " << bin_pos
                        << " is overweighted." << std::endl;
                }
            }
        }

        bool feasible
            = (items.size() == this->number_of_items())
            && (number_of_duplicates == 0)
            && (number_of_overweighted_bins == 0)
            && (number_of_conflict_violations == 0);

        if (verbose >= 2)
            os << std::endl;
        if (verbose >= 1) {
            os
                << "Number of items:                " << items.size() << " / " << this->number_of_items()  << std::endl
                << "Number of duplicates:           " << number_of_duplicates << std::endl
                << "Number of conflict violations:  " << number_of_conflict_violations << std::endl
                << "Number of overweighted bins:    " << number_of_overweighted_bins << std::endl
                << "Feasible:                       " << feasible << std::endl
                << "Number of bins:                 " << number_of_bins << std::endl
                ;
        }
        return {feasible, number_of_bins};
    }

private:

    /** Read an instance from a file in 'default' format. */
    void read_default(std::ifstream& file)
    {
        std::string tmp;
        std::vector<std::string> line;

        ItemId number_of_items;
        Weight capacity;
        file >> number_of_items >> capacity;
        set_capacity(capacity);

        Weight weight = -1;
        ItemId item_id_tmp = -1;
        for (ItemId item_id = 0; item_id < number_of_items; ++item_id) {
            file >> item_id_tmp >> weight;
            add_item(weight);
            getline(file, tmp);
            line = optimizationtools::split(tmp, ' ');
            for (std::string s: line)
                if (std::stol(s) - 1 < item_id)
                    add_conflict(item_id, std::stol(s) - 1);
        }
    }

    /*
     * Private attributes
     */

    /** Items. */
    std::vector<Item> items_;

    /** Capacity of the bins. */
    Weight capacity_;

};

}

}
