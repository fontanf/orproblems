#pragma once

/**
 * Knapsack Problem with Conflicts.
 *
 * Input:
 * - a knapsack with capacity C
 * - n items with weight wⱼ and profit pⱼ (j = 1..n)
 * - a graph G such that each node corresponds to an item
 * Problem:
 * - Select a subset of items such that:
 *   - the total weight of the selected items does not exceed the knapsack
 *     capacity
 *   - if there exists an edge between j₁ to j₂ in G, then j₁ and j₂ must not
 *     be both selected
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
    Weight weight;
    Profit profit;
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
        item.profit = p;
        items_.push_back(item);
    }
    void set_weight(ItemId j, Weight w) { items_[j].weight = w; }
    void set_profit(ItemId j, Profit p) { items_[j].profit = p; }
    void add_conflict(ItemId j1, ItemId j2)
    {
        assert(j1 >= 0);
        assert(j2 >= 0);
        assert(j1 < item_number());
        assert(j2 < item_number());
        items_[j1].neighbors.push_back(j2);
        items_[j2].neighbors.push_back(j1);
    }
    void set_capacity(Weight capacity) { capacity_ = capacity; }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            std::cerr << "\033[31m" << "ERROR, unable to open file \"" << instance_path << "\"" << "\033[0m" << std::endl;
            assert(false);
            return;
        }
        if (format == "" || format == "default" || format == "hifi2006") {
            read_hifi2006(file);
        } else if (format == "bettinelli2017") {
            read_bettinelli2017(file);
        } else {
            std::cerr << "\033[31m" << "ERROR, unknown instance format \"" << format << "\"" << "\033[0m" << std::endl;
        }
        file.close();
    }

    virtual ~Instance() { }

    inline ItemId item_number() const { return items_.size(); }
    inline const Item& item(ItemId j) const { return items_[j]; }
    inline Weight capacity() const { return capacity_; }

    std::pair<bool, Profit> check(std::string certificate_path)
    {
        std::ifstream file(certificate_path);
        if (!file.good()) {
            std::cerr << "\033[31m" << "ERROR, unable to open file \"" << certificate_path << "\"" << "\033[0m" << std::endl;
            assert(false);
            return {false, 0};
        }

        ItemId n = item_number();
        Weight weight = 0;
        Profit profit = 0;
        ItemId j = 0;
        optimizationtools::IndexedSet items(n);
        ItemPos duplicates = 0;
        ItemPos conflict_violation_number = 0;
        while (file >> j) {
            if (items.contains(j)) {
                duplicates++;
                std::cout << "Job " << j << " already scheduled." << std::endl;
            }
            for (ItemId j_con: item(j).neighbors) {
                if (items.contains(j_con)) {
                    conflict_violation_number++;
                    std::cout << "Job " << j << " is in conflict with job " << j_con << "." << std::endl;
                }
            }
            items.add(j);
            weight += item(j).weight;
            profit += item(j).profit;
            std::cout << "Job: " << j
                << "; Weight: " << weight
                << "; Profit: " << profit
                << std::endl;
        }
        bool feasible
            = (duplicates == 0)
            && (weight <= capacity())
            && (conflict_violation_number == 0);
        std::cout << "---" << std::endl;
        std::cout << "Item number:                " << items.size() << " / " << n  << std::endl;
        std::cout << "Duplicates:                 " << duplicates << std::endl;
        std::cout << "Conflict violation number:  " << conflict_violation_number << std::endl;
        std::cout << "Weight:                     " << weight << " / " << capacity() << std::endl;
        std::cout << "Feasible:                   " << feasible << std::endl;
        std::cout << "Profit:                     " << profit << std::endl;
        return {feasible, profit};
    }

private:

    void read_hifi2006(std::ifstream& file)
    {
        ItemId n = -1;
        file >> n;

        ItemPos conflict_number = -1;
        file >> conflict_number;

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
        for (ItemPos conflict_id = 0; conflict_id < conflict_number; ++conflict_id) {
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

};

std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "capacity " << instance.capacity() << std::endl;
    os << "item number " << instance.item_number() << std::endl;
    for (ItemId j = 0; j < instance.item_number(); ++j) {
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

