/**
 * Knapsack problem with conflicts
 *
 * Input:
 * - a knapsack with capacity C
 * - n items; for each item j = 1..n, a weight wⱼ and a profit pⱼ
 * - a graph G such that each node corresponds to an item
 * Problem:
 * - Select a subset of items such that:
 *   - the total weight of the selected items does not exceed the knapsack
 *     capacity
 *   - if there exists an edge between vertex j₁ and vertex j₂ in G, then item
 *     j₁ and item j₂ must not be both selected
 * Objective:
 * - Maximize the total profit of the selected items
 *
 */

#pragma once

#include "optimizationtools/containers/indexed_set.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>

namespace orproblems
{
namespace knapsackwithconflicts
{

using ItemId = int64_t;
using ItemPos = int64_t;
using Weight = int64_t;
using Profit = double;

/*
 * Structure for an item.
 */
struct Item
{
    /** Weight of the item. */
    Weight weight = 0;

    /** Profit of the item. */
    Profit profit = 0;

    /** Conflicting items. */
    std::vector<ItemId> neighbors;
};

/**
 * Instance class for a 'knapsackwithconflicts' problem.
 */
class Instance
{

public:

    /*
     * Getters
     */

    /** Get the number of items. */
    inline ItemId number_of_items() const { return items_.size(); }

    /** Get an item. */
    inline const Item& item(ItemId item_id) const { return items_[item_id]; }

    /** Get the capacity of the knapsack. */
    inline Weight capacity() const { return capacity_; }

    /** Get the total weight of the items. */
    inline Weight total_weight() const { return total_weight_; }

    /** Get the number of conflicts. */
    inline ItemPos number_of_conflicts() const { return number_of_conflicts_; }

    /*
     * Outputs
     */

    /** Print the instance. */
    void format(
            std::ostream& os,
            int verbosity_level = 1) const
    {
        if (verbosity_level >= 1) {
            os
                << "Number of items:         " << number_of_items() << std::endl
                << "Capacity:                " << capacity() << std::endl
                << "Number of conflicts:     " << number_of_conflicts() << std::endl
                << "Weight ratio:            " << (double)total_weight() / capacity() << std::endl
                << "Average # of conflicts:  " << (double)number_of_conflicts() / number_of_items() << std::endl
                ;
        }

        // Print items.
        if (verbosity_level >= 2) {
            os << std::endl
                << std::setw(12) << "Item"
                << std::setw(12) << "Profit"
                << std::setw(12) << "Weight"
                << std::setw(12) << "Efficiency"
                << std::setw(12) << "# conflicts"
                << std::endl
                << std::setw(12) << "----"
                << std::setw(12) << "------"
                << std::setw(12) << "------"
                << std::setw(12) << "----------"
                << std::setw(12) << "-----------"
                << std::endl;
            for (ItemId item_id = 0; item_id < number_of_items(); ++item_id) {
                const Item& item = this->item(item_id);
                os
                    << std::setw(12) << item_id
                    << std::setw(12) << item.profit
                    << std::setw(12) << item.weight
                    << std::setw(12) << (double)item.profit / item.weight
                    << std::setw(12) << item.neighbors.size()
                    << std::endl;
            }
        }

        // Print conflicts.
        if (verbosity_level >= 3) {
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
    }

    /** Check a certificate. */
    std::pair<bool, Profit> check(
            const std::string& certificate_path,
            std::ostream& os,
            int verbosity_level = 1) const
    {
        std::ifstream file(certificate_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");
        }

        if (verbosity_level >= 2) {
            os << std::endl
                << std::setw(12) << "Item"
                << std::setw(12) << "Weight"
                << std::setw(12) << "Profit"
                << std::endl
                << std::setw(12) << "----"
                << std::setw(12) << "------"
                << std::setw(12) << "------"
                << std::endl;
        }

        Weight weight = 0;
        Profit profit = 0;
        ItemId item_id = -1;
        optimizationtools::IndexedSet items(number_of_items());
        ItemPos number_of_duplicates = 0;
        ItemPos number_of_conflict_violations = 0;
        while (file >> item_id) {
            weight += item(item_id).weight;
            profit += item(item_id).profit;

            if (verbosity_level >= 2) {
                os
                    << std::setw(12) << item_id
                    << std::setw(12) << weight
                    << std::setw(12) << profit
                    << std::endl;
            }

            // Check duplicates.
            if (items.contains(item_id)) {
                number_of_duplicates++;
                if (verbosity_level >= 2) {
                    os << "Item " << item_id
                        << " has already been packed." << std::endl;
                }
            }
            items.add(item_id);

            // Check conflict violations.
            for (ItemId item_id_con: item(item_id).neighbors) {
                if (items.contains(item_id_con)) {
                    number_of_conflict_violations++;
                    if (verbosity_level >= 2) {
                        os << "Item " << item_id
                            << " is in conflict with item "
                            << item_id_con << "."
                            << std::endl;
                    }
                }
            }
        }

        bool feasible
            = (number_of_duplicates == 0)
            && (weight <= capacity())
            && (number_of_conflict_violations == 0);
        if (verbosity_level >= 2)
            os << std::endl;
        if (verbosity_level >= 1) {
            os
                << "Number of Items:                " << items.size() << " / " << number_of_items() << std::endl
                << "Number of duplicates:           " << number_of_duplicates << std::endl
                << "Number of conflict violations:  " << number_of_conflict_violations << std::endl
                << "Weight:                         " << weight << " / " << capacity() << std::endl
                << "Feasible:                       " << feasible << std::endl
                << "Profit:                         " << profit << std::endl
                ;
        }
        return {feasible, profit};
    }

private:

    /*
     * Private methods
     */

    /** Constructor to build an instance manually. */
    Instance() { }

    /*
     * Private attributes
     */

    /** Items. */
    std::vector<Item> items_;

    /** Capacity. */
    Weight capacity_ = 0;

    /*
     * Computed attributes
     */

    /** Number of conflicts. */
    ItemPos number_of_conflicts_ = 0;

    /** Total weight of the items. */
    Weight total_weight_ = 0;

    friend class InstanceBuilder;
};

class InstanceBuilder
{

public:

    /** Constructor. */
    InstanceBuilder() { }

    /** Add an item. */
    void add_item(
            Weight weight,
            Profit profit)
    {
        Item item;
        item.weight = weight;
        item.profit = profit;
        instance_.items_.push_back(item);
    }

    /** Set the weight of an item. */
    void set_weight(
            ItemId item_id,
            Weight w)
    {
        instance_.items_[item_id].weight = w;
    }

    /** Set the profit of an item. */
    void set_profit(
            ItemId item_id,
            Profit profit)
    {
        instance_.items_[item_id].profit = profit;
    }

    /** Add a conflict between two items. */
    void add_conflict(
            ItemId item_id_1,
            ItemId item_id_2)
    {
        instance_.items_[item_id_1].neighbors.push_back(item_id_2);
        instance_.items_[item_id_2].neighbors.push_back(item_id_1);
        instance_.number_of_conflicts_++;
    }

    /** Set the capacity of the knapsack. */
    void set_capacity(Weight capacity) { instance_.capacity_ = capacity; }

    /** Build an instance from a file. */
    void read(
            const std::string& instance_path,
            const std::string& format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        }
        if (format == "" || format == "default" || format == "hifi2006") {
            read_hifi2006(file);
        } else if (format == "bettinelli2017") {
            read_bettinelli2017(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    /*
     * Build
     */

    /** Build the instance. */
    Instance build()
    {
        // Compute total weight.
        instance_.total_weight_ = 0;
        for (ItemId item_id = 0;
                item_id < instance_.number_of_items();
                ++item_id) {
            const Item& item = instance_.item(item_id);
            instance_.total_weight_ += item.weight;
        }

        return std::move(instance_);
    }

private:

    /*
     * Private methods
     */

    /** Read an instance from a file in 'hifi2006' format. */
    void read_hifi2006(std::ifstream& file)
    {
        ItemId number_of_items = -1;
        file >> number_of_items;

        ItemPos number_of_conflicts = -1;
        file >> number_of_conflicts;

        Weight capacity = -1;
        file >> capacity;
        set_capacity(capacity);

        Profit profit = -1;
        for (ItemId item_id = 0; item_id < number_of_items; ++item_id) {
            file >> profit;
            add_item(0, profit);
        }

        Weight weight = -1;
        for (ItemId item_id = 0; item_id < number_of_items; ++item_id) {
            file >> weight;
            set_weight(item_id, weight);
        }

        ItemId item_id_1 = -1;
        ItemId item_id_2 = -1;
        for (ItemPos conflict_id = 0; conflict_id < number_of_conflicts; ++conflict_id) {
            file >> item_id_1 >> item_id_2;
            add_conflict(item_id_1 - 1, item_id_2 - 1);
        }
    }

    /** Read an instance from a file in 'bettinelli2017' format. */
    void read_bettinelli2017(std::ifstream& file)
    {
        ItemId number_of_items = -1;
        Weight capacity = -1;
        std::string tmp;
        file >> tmp >> tmp >> tmp >> number_of_items >> tmp;
        file >> tmp >> tmp >> tmp >> capacity >> tmp;
        set_capacity(capacity);
        if (tmp == ";")
            file >> tmp;
        file >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp;

        Weight weight = -1;
        Profit profit = -1;
        for (ItemId item_id = 0; item_id < number_of_items; ++item_id) {
            file >> tmp >> profit >> weight;
            add_item(weight, profit);
        }

        file >> tmp >> tmp >> tmp >> tmp;
        ItemId item_id_1 = -1;
        ItemId item_id_2 = -1;
        for (;;) {
            file >> item_id_1 >> item_id_2;
            if (!file)
                break;
            add_conflict(item_id_1, item_id_2);
        }
    }

    /*
     * Private attributes
     */

    /** Instance. */
    Instance instance_;

};

}
}
