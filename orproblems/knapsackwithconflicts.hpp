#pragma once

/**
 * Knapsack Problem with Conflicts.
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

#include "optimizationtools/indexed_set.hpp"

#include <fstream>
#include <iostream>

namespace orproblems
{

namespace knapsackwithconflicts
{

typedef int64_t ItemId;
typedef int64_t ItemPos;
typedef int64_t Weight;
typedef double Profit;

struct Item
{
    ItemId id;
    Weight weight = 0;
    Profit profit = 0;
    std::vector<ItemId> neighbors;
};

class Instance
{

public:

    Instance() { }
    void add_item(Weight w, Profit p)
    {
        Item item;
        item.id = items_.size();
        item.weight = w;
        total_weight_ += w;
        item.profit = p;
        items_.push_back(item);
    }
    void set_weight(ItemId j, Weight w)
    {
        total_weight_ -= items_[j].weight;
        items_[j].weight = w;
        total_weight_ += items_[j].weight;
    }
    void set_profit(ItemId j, Profit p) { items_[j].profit = p; }
    void add_conflict(ItemId j1, ItemId j2)
    {
        assert(j1 >= 0);
        assert(j2 >= 0);
        assert(j1 < number_of_items());
        assert(j2 < number_of_items());
        items_[j1].neighbors.push_back(j2);
        items_[j2].neighbors.push_back(j1);
        number_of_conflicts_++;
    }
    void set_capacity(Weight capacity) { capacity_ = capacity; }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
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

    virtual ~Instance() { }

    inline ItemId number_of_items() const { return items_.size(); }
    inline const Item& item(ItemId j) const { return items_[j]; }
    inline Weight capacity() const { return capacity_; }
    inline Weight total_weight() const { return total_weight_; }
    inline ItemPos number_of_conflicts() const { return number_of_conflicts_; }

    std::pair<bool, Profit> check(
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

        ItemId n = number_of_items();
        Weight weight = 0;
        Profit profit = 0;
        ItemId j = -1;
        optimizationtools::IndexedSet items(n);
        ItemPos number_of_duplicates = 0;
        ItemPos number_of_conflict_violations = 0;
        while (file >> j) {
            weight += item(j).weight;
            profit += item(j).profit;
            if (verbose == 2)
                std::cout << "Job: " << j
                    << "; Weight: " << weight
                    << "; Profit: " << profit
                    << std::endl;
            if (items.contains(j)) {
                number_of_duplicates++;
                if (verbose == 2)
                    std::cout << "Job " << j << " already scheduled." << std::endl;
            }
            for (ItemId j_con: item(j).neighbors) {
                if (items.contains(j_con)) {
                    number_of_conflict_violations++;
                    if (verbose == 2)
                        std::cout << "Job " << j << " is in conflict with job " << j_con << "." << std::endl;
                }
            }
            items.add(j);
        }

        bool feasible
            = (number_of_duplicates == 0)
            && (weight <= capacity())
            && (number_of_conflict_violations == 0);
        if (verbose == 2)
            std::cout << "---" << std::endl;
        if (verbose >= 1) {
            std::cout << "Number of Items:                " << items.size() << " / " << n << std::endl;
            std::cout << "Number of duplicates:           " << number_of_duplicates << std::endl;
            std::cout << "Number of conflict violations:  " << number_of_conflict_violations << std::endl;
            std::cout << "Weight:                         " << weight << " / " << capacity() << std::endl;
            std::cout << "Feasible:                       " << feasible << std::endl;
            std::cout << "Profit:                         " << profit << std::endl;
        }
        return {feasible, profit};
    }

private:

    void read_hifi2006(std::ifstream& file)
    {
        ItemId n = -1;
        file >> n;

        ItemPos number_of_conflicts = -1;
        file >> number_of_conflicts;

        Weight c = -1;
        file >> c;
        set_capacity(c);

        Profit p = -1;
        for (ItemId j = 0; j < n; ++j) {
            file >> p;
            add_item(0, p);
        }

        Weight w = -1;
        for (ItemId j = 0; j < n; ++j) {
            file >> w;
            set_weight(j, w);
        }

        ItemId j1 = -1;
        ItemId j2 = -1;
        for (ItemPos conflict_id = 0; conflict_id < number_of_conflicts; ++conflict_id) {
            file >> j1 >> j2;
            add_conflict(j1 - 1, j2 - 1);
        }
    }

    void read_bettinelli2017(std::ifstream& file)
    {
        ItemId n = -1;
        Weight c = -1;
        std::string tmp;
        file >> tmp >> tmp >> tmp >> n >> tmp;
        file >> tmp >> tmp >> tmp >> c >> tmp;
        set_capacity(c);
        if (tmp == ";")
            file >> tmp;
        file >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp;

        Weight w = -1;
        Profit p = -1;
        for (ItemId j = 0; j < n; ++j) {
            file >> tmp >> p >> w;
            add_item(w, p);
        }

        file >> tmp >> tmp >> tmp >> tmp;
        ItemId j1 = -1;
        ItemId j2 = -1;
        for (;;) {
            file >> j1 >> j2;
            if (!file)
                break;
            add_conflict(j1, j2);
        }
    }

    std::vector<Item> items_;
    Weight capacity_ = 0;
    ItemPos number_of_conflicts_ = 0;
    Weight total_weight_ = 0;

};

static inline std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "capacity " << instance.capacity() << std::endl;
    os << "number of items " << instance.number_of_items() << std::endl;
    for (ItemId j = 0; j < instance.number_of_items(); ++j) {
        os << "item " << j
            << " w " << instance.item(j).weight
            << " p " << instance.item(j).profit
            << " neighbors";
        for (ItemId j2: instance.item(j).neighbors)
            os << " " << j2;
        os << std::endl;
    }
    return os;
}

}

}

