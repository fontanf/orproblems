/**
 * Generalized quadratic multiple knapsack problem
 *
 * Input:
 * - m containers (knapsacks); for each knapsack i = 1..m, a capacity cᵢ
 * - o classes; for each class k = 1..o
 *   - a setup time sₖ
 *   - a maximum number of knapsack mₖ
 * - n items; for each item j = 1..n
 *   - a weight wⱼ
 *   - a class rⱼ
 * - for each item j = 1..n, for each knapsack i = 1..m, a profit pⱼᵢ
 * - for each pair of items (j₁, j₂) with j₁ ≠ j₂, a profit pⱼ₁ⱼ₂
 * Problem:
 * - select m disjoint subsets of items (one per knapsack) such that
 *   - for each knapsack i = 1..m, the total weight of the items + the total
 *     setup times of each class in knapsack i does not exceed its capacity cᵢ
 *   - for each class k = 1..o, the items from class k are not in more than mₖ
 *     different knapsacks
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
namespace generalized_quadratic_multiple_knapsack
{

using ItemId = int64_t;
using ItemPos = int64_t;
using ClassId = int64_t;
using KnapsackId = int64_t;
using Weight = int64_t;
using Profit = double;

/*
 * Structure for a class.
 */
struct ItemClass
{
    /** Setup time of the class of items. */
    Weight setup_time;

    /** Maximum number of knapsacks. */
    KnapsackId maximum_number_of_knapsacks;

    /** Items of the class. */
    std::vector<ItemId> item_ids;
};

/*
 * Structure for an item.
 */
struct Item
{
    /** Weight of the item. */
    Weight weight;

    /** Class of the item. */
    ClassId class_id;

    /** For each knapsack, the profit of assinging the item to this knapsack. */
    std::vector<Profit> profits;
};

/**
 * Instance class for a 'generalized_quadratic_multiple_knapsack' problem.
 */
class Instance
{

public:

    /** Get the number of knapsacks. */
    KnapsackId number_of_knapsacks() const { return capacities_.size(); }

    /** Get the number of classes. */
    ClassId number_of_classes() const { return classes_.size(); }

    /** Get the number of items. */
    ItemId number_of_items() const { return items_.size(); }

    /** Get a class. */
    const ItemClass& item_class(ClassId class_id) const { return classes_[class_id]; }

    /** Get an item. */
    const Item& item(ItemId item_id) const { return items_[item_id]; }

    /** Get the profit of assigning an item to a knapsack. */
    Profit item_profit(
            ItemId item_id,
            KnapsackId knapsack_id) const
    {
        return items_[item_id].profits[knapsack_id];
    }

    /** Get the profit of a pair of items. */
    Profit pair_profit(
            ItemId item_id_1,
            ItemId item_id_2) const
    {
        return profits_[std::max(item_id_1, item_id_2)][std::min(item_id_1, item_id_2)];
    }

    /** Get the capacity of a knapsack. */
    Weight capacity(KnapsackId knapsack_id) const { return capacities_[knapsack_id]; }

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
                << "Number of classes:    " << number_of_classes() << std::endl
                << "Number of items:      " << number_of_items() << std::endl
                ;
        }

        // Print knapsacks.
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

        // Print classes.
        if (verbosity_level >= 2) {
            os << std::endl
                << std::setw(12) << "Class"
                << std::setw(12) << "setup"
                << std::setw(12) << "Max # knap."
                << std::setw(12) << "# items"
                << std::endl
                << std::setw(12) << "-----"
                << std::setw(12) << "-----"
                << std::setw(12) << "-----------"
                << std::setw(12) << "-------"
                << std::endl;
            for (ClassId class_id = 0;
                    class_id < number_of_classes();
                    ++class_id) {
                const ItemClass& item_class = this->item_class(class_id);
                os
                    << std::setw(12) << class_id
                    << std::setw(12) << item_class.setup_time
                    << std::setw(12) << item_class.maximum_number_of_knapsacks
                    << std::setw(12) << item_class.item_ids.size()
                    << std::endl;
            }
        }

        // Print items.
        if (verbosity_level >= 2) {
            os << std::endl
                << std::setw(12) << "Item"
                << std::setw(12) << "Weight"
                << std::setw(12) << "Class"
                << std::endl
                << std::setw(12) << "----"
                << std::setw(12) << "------"
                << std::setw(12) << "-----"
                << std::endl;
            for (ItemId item_id = 0; item_id < number_of_items(); ++item_id) {
                const Item& item = this->item(item_id);
                os
                    << std::setw(12) << item_id
                    << std::setw(12) << item.weight
                    << std::setw(12) << item.class_id
                    << std::endl;
            }
        }

        // Print item profits.
        if (verbosity_level >= 3) {
            os << std::endl
                << std::setw(12) << "Item"
                << std::setw(12) << "Knapsack"
                << std::setw(12) << "Profit"
                << std::endl
                << std::setw(12) << "----"
                << std::setw(12) << "--------"
                << std::setw(12) << "------"
                << std::endl;
            for (ItemId item_id = 0; item_id < number_of_items(); ++item_id) {
                const Item& item = this->item(item_id);
                for (KnapsackId knapsack_id = 0;
                        knapsack_id < number_of_knapsacks();
                        ++knapsack_id) {
                    os
                        << std::setw(12) << item_id
                        << std::setw(12) << knapsack_id
                        << std::setw(12) << item.profits[knapsack_id]
                        << std::endl;
                }
            }
        }

        // Print item pairs profits
        if (verbosity_level >= 4) {
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
                for (ItemId item_id_2 = item_id_1 + 1;
                        item_id_2 < number_of_items();
                        ++item_id_2) {
                    os
                        << std::setw(12) << item_id_1
                        << std::setw(12) << item_id_2
                        << std::setw(12) << pair_profit(item_id_1, item_id_2)
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
        // Initial display.
        if (verbosity_level >= 1) {
            os
                << "Checker" << std::endl
                << "-------" << std::endl;
        }

        std::ifstream file(certificate_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");
        }

        Weight overweight = 0;
        Profit total_profit = 0;
        ItemId n = -1;  // Number of items in knapsack i.
        ItemId job_id = -1;
        optimizationtools::IndexedSet items(n);
        optimizationtools::IndexedSet knapsack_classes(number_of_classes());
        std::vector<KnapsackId> class_number_of_knapsacks(number_of_classes(), 0);
        ItemPos number_of_duplicates = 0;
        for (KnapsackId i = 0; i < number_of_knapsacks(); ++i) {
            Weight total_weight = 0;
            file >> n;
            std::vector<ItemId> current_knapsack_items;
            for (ItemPos j_pos = 0; j_pos < n; ++j_pos) {
                file >> job_id;
                total_weight += item(job_id).weight;
                total_profit += item_profit(job_id, i);
                for (ItemId item_id_2: current_knapsack_items)
                    total_profit += pair_profit(job_id, item_id_2);
                current_knapsack_items.push_back(job_id);
                if (verbosity_level == 2)
                    os << "Job: " << job_id
                        << "; Weight: " << total_weight
                        << "; Profit: " << total_profit
                        << std::endl;
                knapsack_classes.add(item(job_id).class_id);

                // Check duplicates.
                if (items.contains(job_id)) {
                    number_of_duplicates++;
                    if (verbosity_level >= 2) {
                        os << "Job " << job_id
                            << " has already been scheduled." << std::endl;
                    }
                }
                items.add(job_id);

            }
            if (total_weight > capacity(i)) {
                if (verbosity_level == 2)
                    os << "Knapsack " << i
                        << " has overweight: " << total_weight << "/" << capacity(i)
                        << std::endl;
                overweight += (capacity(i) - total_weight);
            }
            for (ClassId k: knapsack_classes)
                class_number_of_knapsacks[k]++;
        }
        ClassId number_of_class_maximum_number_of_knapsacks_violations = 0;
        for (ClassId k = 0; k < number_of_classes(); ++k) {
            if (class_number_of_knapsacks[k] > item_class(k).maximum_number_of_knapsacks) {
                if (verbosity_level == 2)
                    os << "Class " << k
                        << " number of knapsacks " << class_number_of_knapsacks[k]
                        << " / " << item_class(k).maximum_number_of_knapsacks
                        << std::endl;
                number_of_class_maximum_number_of_knapsacks_violations++;
            }
        }

        bool feasible
            = (number_of_duplicates == 0)
            && (overweight == 0)
            && (number_of_class_maximum_number_of_knapsacks_violations == 0);

        if (verbosity_level >= 2)
            os << std::endl;
        if (verbosity_level >= 1) {
            os
                << "Number of items:                          " << items.size() << " / " << number_of_items() << std::endl
                << "Number of duplicates:                     " << number_of_duplicates << std::endl
                << "Overweight:                               " << overweight << std::endl
                << "Number of max # of knapsacks violations:  " << number_of_class_maximum_number_of_knapsacks_violations << std::endl
                << "Feasible:                                 " << feasible << std::endl
                << "Profit:                                   " << total_profit << std::endl
                ;
        }
        return {feasible, total_profit};
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

    /** Classes. */
    std::vector<ItemClass> classes_;

    /** Items. */
    std::vector<Item> items_;

    /** Profits of pairs of items. */
    std::vector<std::vector<Profit>> profits_;

    /** Capacities of the knapsacks. */
    std::vector<Weight> capacities_;

    friend class InstanceBuilder;
};

class InstanceBuilder
{

public:

    /** Constructor. */
    InstanceBuilder() { }

    /**
     * Set the number of knapsacks.
     *
     * This method resets all the items.
     */
    void set_number_of_knapsacks(KnapsackId number_of_knapsacks)
    {
        instance_.items_.clear();
        instance_.capacities_ = std::vector<Weight>(number_of_knapsacks, 0);
    }

    /** Set the capacity of a knapsack. */
    void set_knapsack_capacity(Weight capacity)
    {
        instance_.capacities_.push_back(capacity);
    }

    /** Add a class. */
    void add_class(
            Weight setup_time,
            KnapsackId maximum_number_of_knapsacks)
    {
        ItemClass item_class;
        item_class.setup_time = setup_time;
        item_class.maximum_number_of_knapsacks = maximum_number_of_knapsacks;
        instance_.classes_.push_back(item_class);
    }

    /** Add an item. */
    void add_item(
            Weight weight,
            ClassId class_id)
    {
        Item item;
        item.weight = weight;
        item.class_id = class_id;
        item.profits = std::vector<Profit>(instance_.number_of_knapsacks(), 0);
        instance_.items_.push_back(item);
        instance_.profits_.push_back(std::vector<Profit>(instance_.items_.size()));
    }

    /** Set the profit of assigning an item to a knapsack. */
    void set_item_profit(
            ItemId item_id,
            KnapsackId knapsack_id,
            Profit profit)
    {
        instance_.items_[item_id].profits[knapsack_id] = profit;
    }

    /** Set the profit of a pair of items. */
    void set_pair_profit(
            ItemId item_id_1,
            ItemId item_id_2,
            Profit profit)
    {
        instance_.profits_[std::max(item_id_1, item_id_2)][std::min(item_id_1, item_id_2)] = profit;
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
        if (format == "" || format == "sarac2014") {
            read_sarac2014(file);
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
        // Compute class.item_ids.
        for (ItemId item_id = 0;
                item_id < instance_.number_of_items();
                ++item_id) {
            const Item& item = instance_.item(item_id);
            instance_.classes_[item.class_id].item_ids.push_back(item_id);
        }

        return std::move(instance_);
    }

private:

    /*
     * Private methods
     */

    void read_sarac2014(std::ifstream& file)
    {
        //std::string tmp;
        //file >> tmp;
        //KnapsackId m;
        //ItemId n;
        //file >> m >> n;

        //for (ItemId j = 0; j < n; ++j)
        //    add_item(0);

        //Profit p;
        //for (ItemId j = 0; j < n; ++j) {
        //    file >> p;
        //    set_profit(j, p);
        //}
        //for (ItemId item_id_1 = 0; item_id_1 < n; ++item_id_1) {
        //    for (ItemId item_id_2 = item_id_1 + 1; item_id_2 < n; ++item_id_2) {
        //        file >> p;
        //        set_profit(item_id_1, item_id_2, p);
        //    }
        //}

        //Weight c = -1;
        //file >> c;
        //file >> c;
        //for (KnapsackId i = 0; i < m; ++i)
        //    add_knapsack(c);

        //Weight w = -1;
        //for (ItemId j = 0; j < n; ++j) {
        //    file >> w;
        //    set_weight(j, w);
        //}
    }

    /*
     * Private attributes
     */

    /** Instance. */
    Instance instance_;

};

}
}
