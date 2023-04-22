/**
 * Quadratic Multiple Knapsack Problem.
 *
 * Input:
 * - m containers (knapsacks); for each knapsack i = 1..m, a capacity cᵢ
 * - n items; for each item j = 1..n, a profit pⱼ and a weight wⱼ
 * - for all pairs of items (j₁, j₂) with j₁ ≠ j₂, a profit pⱼ₁ⱼ₂
 * Problem:
 * - select m disjoint subsets of items (one per knapsack) such that the total
 *   weight of the items in a knapsack does not exceed its capacity
 * Objective:
 * - Maximize the overall profit of the knapsacks.
 *   The profit of a knapsack is the sum of the profits of the items and profit
 *   of the pairs of items it contains.
 *
 */

#pragma once

#include "optimizationtools/containers/indexed_set.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>

namespace orproblems
{

namespace quadraticmultipleknapsack
{

using ItemId = int64_t;
using ItemPos = int64_t;
using KnapsackId = int64_t;
using Weight = int64_t;
using Profit = int64_t;

/**
 * Instance class for a 'quadraticmultipleknapsack' problem.
 */
class Instance
{

public:

    /*
     * Constructors and destructor
     */

    /** Constructor to build an instance manually. */
    Instance() {  }

    /** Add a knapsack. */
    void add_knapsack(Weight capacity) { capacities_.push_back(capacity); }

    /** Add an item. */
    void add_item(Weight weight)
    {
        weights_.push_back(weight);
        profits_.push_back(std::vector<Profit>(weights_.size()));
    }

    /** Set the weight of an item. */
    void set_weight(
            ItemId item_id,
            Weight weight)
    {
        weights_[item_id] = weight;
    }

    /** Set the profit of an item. */
    void set_profit(
            ItemId item_id,
            Profit profit)
    {
        profits_[item_id][item_id] = profit;
    }

    /** Set the profit of packing two items. */
    void set_profit(
            ItemId item_id_1,
            ItemId item_id_2,
            Profit profit)
    {
        profits_[std::min(item_id_1, item_id_2)][std::max(item_id_1, item_id_2)] = profit;
    }

    /** Build an instance from a file. */
    Instance(
            std::string instance_path,
            std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        if (format == "" || format == "hiley2006") {
            read_hiley2006(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    /*
     * Getters
     */

    /** Get the number of knapsacks. */
    KnapsackId number_of_knapsacks() const { return capacities_.size(); }

    /** Get the number of items. */
    ItemId number_of_items() const { return weights_.size(); }

    /** Get the weight of an item. */
    Weight weight(ItemId item_id) const { return weights_[item_id]; }

    /** Get the profit of an item. */
    Profit profit(ItemId item_id) const { return profits_[item_id][item_id]; }

    /** Get the profit of two items. */
    Profit profit(
            ItemId item_id_1,
            ItemId item_id_2) const
    {
        return profits_[std::min(item_id_1, item_id_2)][std::max(item_id_1, item_id_2)];
    }

    /** Get the capacity of a knapsack. */
    Weight capacity(KnapsackId knapsack_id) const { return capacities_[knapsack_id]; }

    /** Print the instance. */
    std::ostream& print(
            std::ostream& os,
            int verbose = 1) const
    {
        if (verbose >= 1) {
            os
                << "Number of knapsacks:  " << number_of_knapsacks() << std::endl
                << "Number of items:      " << number_of_items() << std::endl
                ;
        }

        if (verbose >= 2) {
            os << std::endl
                << std::setw(12) << "Knapsack"
                << std::setw(12) << "Capacity"
                << std::endl
                << std::setw(12) << "--------"
                << std::setw(12) << "--------"
                << std::endl;
            for (KnapsackId knapsack_id = 0;
                    knapsack_id < number_of_knapsacks();
                    knapsack_id++) {
                os
                    << std::setw(12) << knapsack_id
                    << std::setw(12) << capacity(knapsack_id)
                    << std::endl;
            }
        }

        if (verbose >= 2) {
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
                os
                    << std::setw(12) << item_id
                    << std::setw(12) << weight(item_id)
                    << std::setw(12) << profit(item_id)
                    << std::endl;
            }
        }

        if (verbose >= 2) {
            os << std::endl
                << std::setw(12) << "Item 1"
                << std::setw(12) << "Item 2"
                << std::setw(12) << "Profit"
                << std::endl
                << std::setw(12) << "------"
                << std::setw(12) << "------"
                << std::setw(12) << "------"
                << std::endl;
            for (ItemId item_id_1 = 0;
                    item_id_1 < number_of_items();
                    ++item_id_1) {
                for (ItemId item_id_2 = 0;
                        item_id_2 < number_of_items();
                        ++item_id_2) {
                    os
                        << std::setw(12) << item_id_1
                        << std::setw(12) << item_id_2
                        << std::setw(12) << profit(item_id_1, item_id_2)
                        << std::endl;
                }
            }
        }

        return os;
    }

    /** Check a certificate. */
    std::pair<bool, Profit> check(
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

        Weight overweight = 0;
        Profit total_profit = 0;
        ItemId number_of_items = -1;
        ItemId item_id = -1;
        optimizationtools::IndexedSet items(this->number_of_items());
        ItemPos number_of_duplicates = 0;
        for (KnapsackId knapsack_id = 0;
                knapsack_id < number_of_knapsacks();
                ++knapsack_id) {
            Weight total_weight = 0;
            file >> number_of_items;
            std::vector<ItemId> current_knapsack_items;
            for (ItemPos item_pos = 0; item_pos < number_of_items; ++item_pos) {
                file >> item_id;
                current_knapsack_items.push_back(item_id);
                total_weight += weight(item_id);
                for (ItemId j2: current_knapsack_items)
                    total_profit += profit(item_id, j2);

                if (verbose >= 2) {
                    os
                        << std::setw(12) << knapsack_id
                        << std::setw(12) << item_id
                        << std::setw(12) << total_weight
                        << std::setw(12) << total_profit
                        << std::endl;
                }

                if (items.contains(item_id)) {
                    number_of_duplicates++;
                    if (verbose >= 2) {
                        os << "Item " << item_id
                            << " has already been packed." << std::endl;
                    }
                }
                items.add(item_id);
            }
            if (total_weight > capacity(knapsack_id)) {
                if (verbose >= 2) {
                    os << "Knapsack " << knapsack_id
                        << " has overweight: " << total_weight
                        << "/" << capacity(knapsack_id)
                        << std::endl;
                }
                overweight += (capacity(knapsack_id) - total_weight);
            }
        }

        bool feasible
            = (number_of_duplicates == 0)
            && (overweight == 0);

        if (verbose >= 2)
            os << std::endl;
        if (verbose >= 1) {
            os
                << "Number of items:            " << items.size() << " / " << this->number_of_items() << std::endl
                << "Number of duplicates:       " << number_of_duplicates << std::endl
                << "Overweight:                 " << overweight << std::endl
                << "Feasible:                   " << feasible << std::endl
                << "Profit:                     " << total_profit << std::endl
            ;
        }
        return {feasible, total_profit};
    }

private:

    /*
     * Private methods
     */

    /** Read an instance from a file in 'hiley2006' format. */
    void read_hiley2006(std::ifstream& file)
    {
        std::string tmp;
        file >> tmp;
        KnapsackId number_of_knapsacks;
        ItemId number_of_items;
        file >> number_of_knapsacks >> number_of_items;

        for (ItemId item_id = 0; item_id < number_of_items; ++item_id)
            add_item(0);

        Profit profit;
        for (ItemId item_id = 0; item_id < number_of_items; ++item_id) {
            file >> profit;
            set_profit(item_id, profit);
        }
        for (ItemId item_id_1 = 0;
                item_id_1 < number_of_items;
                ++item_id_1) {
            for (ItemId item_id_2 = item_id_1 + 1;
                    item_id_2 < number_of_items;
                    ++item_id_2) {
                file >> profit;
                set_profit(item_id_1, item_id_2, profit);
            }
        }

        Weight capacity = -1;
        file >> capacity;
        file >> capacity;
        for (KnapsackId knapsack_id = 0;
                knapsack_id < number_of_knapsacks;
                ++knapsack_id) {
            add_knapsack(capacity);
        }

        Weight weight = -1;
        for (ItemId item_id = 0; item_id < number_of_items; ++item_id) {
            file >> weight;
            set_weight(item_id, weight);
        }
    }

    /*
     * Private attributes
     */

    /** Weights. */
    std::vector<Weight> weights_;

    /** Profits. */
    std::vector<std::vector<Profit>> profits_;

    /** Capacities. */
    std::vector<Weight> capacities_;

};

}

}
