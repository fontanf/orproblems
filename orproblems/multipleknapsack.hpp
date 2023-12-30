/**
 * Multiple knapsack problem
 *
 * Input:
 * - m containers (knapsacks); for each knapsack i = 1..m,  a capacity cᵢ
 * - n items; for each item j = 1..n, a profit pⱼ and a weight wⱼ
 * Problem:
 * - select m disjoint subsets of items (one per knapsack) such that the total
 *   weight of the items in a knapsack does not exceed its capacity
 * Objective:
 * - Maximize the overall profit of the selected items
 *
 */

#pragma once

#include "optimizationtools/containers/indexed_set.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>

namespace orproblems
{
namespace multipleknapsack
{

using ItemId = int64_t;
using ItemPos = int64_t;
using KnapsackId = int64_t;
using Weight = int64_t;
using Profit = int64_t;

/**
 * Structure for an item.
 */
struct Item
{
    /** Weight of the item. */
    Weight weight;

    /** Profit of the item. */
    Profit profit;
};

/**
 * Instance class for a 'multipleknapsack' problem.
 */
class Instance
{

public:

    /*
     * Getters
     */

    /** Get the number of knapsacks. */
    KnapsackId number_of_knapsacks() const { return capacities_.size(); }

    /** Get the number of items. */
    ItemId number_of_items() const { return items_.size(); }

    /** Get an item. */
    const Item& item(ItemId item_id) const { return items_[item_id]; }

    /** Get the capacity of a knapsack. */
    Weight capacity(KnapsackId knapsack_id) const { return capacities_[knapsack_id]; }

    /** Get the total profit of the items. */
    Profit total_profit() const { return profit_sum_; }

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
                << "Number of knapsacks:  " << number_of_knapsacks() << std::endl
                << "Number of items:      " << number_of_items() << std::endl
                ;
        }

        if (verbosity_level >= 2) {
            os << std::endl
                << std::setw(12) << "Knapsack"
                << std::setw(12) << "Capacity"
                << std::endl
                << std::setw(12) << "--------"
                << std::setw(12) << "--------"
                << std::endl;
            for (KnapsackId knapsack_id = 0;
                    knapsack_id < number_of_knapsacks();
                    ++knapsack_id) {
                os
                    << std::setw(12) << knapsack_id
                    << std::setw(12) << capacity(knapsack_id)
                    << std::endl;
            }
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
            for (ItemId item_id = 0;
                    item_id < number_of_items();
                    ++item_id) {
                const Item& item = this->item(item_id);
                os
                    << std::setw(12) << item_id
                    << std::setw(12) << item.weight
                    << std::setw(12) << item.profit
                    << std::endl;
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
                << std::setw(12) << "Knapsack"
                << std::setw(12) << "Item"
                << std::setw(12) << "Weight"
                << std::setw(12) << "Profit"
                << std::endl
                << std::setw(12) << "--------"
                << std::setw(12) << "----"
                << std::setw(12) << "------"
                << std::setw(12) << "------"
                << std::endl;
        }

        Profit profit = 0;
        ItemId knapsack_cur_number_of_items = -1;
        ItemId item_id = -1;
        optimizationtools::IndexedSet items(number_of_items());

        KnapsackId number_of_overweighted_knapsacks = 0;
        ItemPos number_of_duplicates = 0;

        for (KnapsackId knapsack_id = 0;
                knapsack_id < number_of_knapsacks();
                ++knapsack_id) {
            Weight weight = 0;
            file >> knapsack_cur_number_of_items;
            for (ItemPos item_pos = 0;
                    item_pos < knapsack_cur_number_of_items;
                    ++item_pos) {
                file >> item_id;
                weight += item(item_id).weight;
                profit += item(item_id).profit;

                if (verbosity_level >= 2) {
                    os
                        << std::setw(12) << knapsack_id
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
                            << " has already scheduled." << std::endl;
                    }
                }
                items.add(item_id);
            }

            // Check capacity.
            if (weight > capacity(knapsack_id)) {
                number_of_overweighted_knapsacks++;
                if (verbosity_level >= 2) {
                    os << "Knapsack " << knapsack_id
                        << " is overweighted." << std::endl;
                }
            }
        }

        bool feasible
            = (number_of_duplicates == 0)
            && (number_of_overweighted_knapsacks == 0);

        if (verbosity_level >= 2)
            os << std::endl;
        if (verbosity_level >= 1) {
            os
                << "Number of items:                   " << items.size() << " / " << number_of_items() << std::endl
                << "Number of duplicates:              " << number_of_duplicates << std::endl
                << "Number of overweighted knapsacks:  " << number_of_overweighted_knapsacks << std::endl
                << "Feasible:                          " << feasible << std::endl
                << "Profit:                            " << profit << std::endl
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

    /** Capacities. */
    std::vector<Weight> capacities_;

    /*
     * Computed attributes
     */

    /** Profit sum. */
    Profit profit_sum_ = 0;

    friend class InstanceBuilder;
};

class InstanceBuilder
{

public:

    /** Constructor. */
    InstanceBuilder() { }

    /** Add a knapsack. */
    void add_knapsack(Weight capacity) { instance_.capacities_.push_back(capacity); }

    /** Add an item. */
    void add_item(
            Weight weight,
            Profit profit)
    {
        instance_.items_.push_back(Item{weight, profit});
    }

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
        if (format == "" || format == "dellamico2018") {
            read_dellamico2018(file);
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
        // Compute profit sum.
        instance_.profit_sum_ = 0;
        for (ItemId item_id = 0;
                item_id < instance_.number_of_items();
                ++item_id) {
            const Item& item = instance_.item(item_id);
            instance_.profit_sum_ += item.profit;
        }

        return std::move(instance_);
    }

private:

    /*
     * Private methods
     */

    /** Read an instance from a file in 'dellamico2018' format. */
    void read_dellamico2018(std::ifstream& file)
    {
        KnapsackId number_of_knapsacks;
        ItemId number_of_items;
        file >> number_of_knapsacks >> number_of_items;
        Weight capacity;
        for (KnapsackId knapsack_id = 0;
                knapsack_id < number_of_knapsacks;
                ++knapsack_id) {
            file >> capacity;
            add_knapsack(capacity);
        }

        Weight weight;
        Profit profit;
        for (ItemId item_id = 0;
                item_id < number_of_items;
                ++item_id) {
            file >> weight >> profit;
            add_item(weight, profit);
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
