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

namespace orproblems
{

namespace quadraticmultipleknapsack
{

using ItemId = int64_t;
using ItemPos = int64_t;
using KnapsackId = int64_t;
using Weight = int64_t;
using Profit = int64_t;

class Instance
{

public:

    Instance() {  }
    void add_knapsack(Weight capacity) { capacities_.push_back(capacity); }
    void add_item(Weight weight)
    {
        weights_.push_back(weight);
        profits_.push_back(std::vector<Profit>(weights_.size()));
    }
    void set_weight(ItemId j, Weight weight) { weights_[j] = weight; }
    void set_profit(ItemId j, Profit profit) { profits_[j][j] = profit; }
    void set_profit(ItemId j1, ItemId j2, Profit profit)
    {
        profits_[std::min(j1, j2)][std::max(j1, j2)] = profit;
    }

    Instance(std::string instance_path, std::string format = "")
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

    virtual ~Instance() { }

    KnapsackId number_of_knapsacks() const { return capacities_.size(); }
    ItemId number_of_items() const { return weights_.size(); }
    Weight weight(ItemId j) const { return weights_[j]; }
    Profit profit(ItemId j) const { return profits_[j][j]; }
    Profit profit(ItemId j1, ItemId j2) const { return profits_[std::min(j1, j2)][std::max(j1, j2)]; }
    Weight capacity(KnapsackId i) const { return capacities_[i]; }

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
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");
        }

        Weight overweight = 0;
        Profit total_profit = 0;
        ItemId n = -1;  // Number of items in knapsack i.
        ItemId j = -1;
        optimizationtools::IndexedSet items(n);
        ItemPos number_of_duplicates = 0;
        for (KnapsackId i = 0; i < number_of_knapsacks(); ++i) {
            Weight total_weight = 0;
            file >> n;
            std::vector<ItemId> current_knapsack_items;
            for (ItemPos j_pos = 0; j_pos < n; ++j_pos) {
                file >> j;
                current_knapsack_items.push_back(j);
                total_weight += weight(j);
                for (ItemId j2: current_knapsack_items)
                    total_profit += profit(j, j2);
                if (verbose == 2)
                    std::cout << "Job: " << j
                        << "; Weight: " << total_weight
                        << "; Profit: " << total_profit
                        << std::endl;
                if (items.contains(j)) {
                    number_of_duplicates++;
                    if (verbose == 2)
                        std::cout << "Job " << j << " already scheduled." << std::endl;
                }
                items.add(j);
            }
            if (total_weight > capacity(i)) {
                if (verbose == 2)
                    std::cout << "Knapsack " << i
                        << " has overweight: " << total_weight << "/" << capacity(i)
                        << std::endl;
                overweight += (capacity(i) - total_weight);
            }
        }
        bool feasible
            = (number_of_duplicates == 0)
            && (overweight == 0);
        if (verbose == 2)
            std::cout << "---" << std::endl;
        if (verbose >= 1) {
            std::cout << "Number of items:            " << items.size() << " / " << number_of_items() << std::endl;
            std::cout << "Number of duplicates:       " << number_of_duplicates << std::endl;
            std::cout << "Overweight:                 " << overweight << std::endl;
            std::cout << "Feasible:                   " << feasible << std::endl;
            std::cout << "Profit:                     " << total_profit << std::endl;
        }
        return {feasible, total_profit};
    }

private:

    void read_hiley2006(std::ifstream& file)
    {
        std::string tmp;
        file >> tmp;
        KnapsackId m;
        ItemId n;
        file >> m >> n;

        for (ItemId j = 0; j < n; ++j)
            add_item(0);

        Profit p;
        for (ItemId j = 0; j < n; ++j) {
            file >> p;
            set_profit(j, p);
        }
        for (ItemId j1 = 0; j1 < n; ++j1) {
            for (ItemId j2 = j1 + 1; j2 < n; ++j2) {
                file >> p;
                set_profit(j1, j2, p);
            }
        }

        Weight c = -1;
        file >> c;
        file >> c;
        for (KnapsackId i = 0; i < m; ++i)
            add_knapsack(c);

        Weight w = -1;
        for (ItemId j = 0; j < n; ++j) {
            file >> w;
            set_weight(j, w);
        }
    }

    std::vector<Weight> weights_;
    std::vector<std::vector<Profit>> profits_;
    std::vector<Weight> capacities_;

};

static inline std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "number of knapsacks " << instance.number_of_knapsacks() << std::endl;
    os << "number of items " << instance.number_of_items() << std::endl;
    for (KnapsackId i = 0; i < instance.number_of_knapsacks(); ++i) {
        os << "knapsack " << i
            << " capacity " << instance.capacity(i)
            << std::endl;
    }
    for (ItemId j = 0; j < instance.number_of_items(); ++j) {
        os << "item " << j
            << " weight " << instance.weight(j)
            << " profits";
        for (ItemId j2 = j; j2 < instance.number_of_items(); ++j2)
            os << " " << instance.profit(j, j2);
        os << std::endl;
    }
    return os;
}

}

}
