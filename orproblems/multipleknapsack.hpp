#pragma once

/**
 * Multiple Knapsack Problem.
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

#include "optimizationtools/indexed_set.hpp"

#include <fstream>
#include <iostream>

namespace orproblems
{

namespace multipleknapsack
{

typedef int64_t ItemId;
typedef int64_t ItemPos;
typedef int64_t KnapsackId;
typedef int64_t Weight;
typedef int64_t Profit;

struct Item
{
    Weight weight;
    Profit profit;
};

class Instance
{

public:

    Instance() {  }
    void add_knapsack(Weight capacity) { capacities_.push_back(capacity); }
    void add_item(Weight weight, Profit profit)
    {
        items_.push_back(Item{weight, profit});
        profit_sum_ += profit;
    }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        if (format == "" || format == "dellamico2018") {
            read_dellamico2018(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    virtual ~Instance() { }

    KnapsackId number_of_knapsacks() const { return capacities_.size(); }
    ItemId number_of_items() const { return items_.size(); }
    const Item& item(ItemId j) const { return items_[j]; }
    Weight weight(ItemId j) const { return items_[j].weight; }
    Weight profit(ItemId j) const { return items_[j].profit; }
    Weight capacity(KnapsackId i) const { return capacities_[i]; }
    Profit total_profit() const { return profit_sum_; }

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

        Weight overweight = 0;
        Profit profit = 0;
        ItemId n = -1;  // Number of items in knapsack i.
        ItemId j = -1;
        optimizationtools::IndexedSet items(n);
        ItemPos duplicates = 0;
        for (KnapsackId i = 0; i < number_of_knapsacks(); ++i) {
            Weight weight = 0;
            file >> n;
            for (ItemPos j_pos = 0; j_pos < n; ++j_pos) {
                file >> j;
                weight += item(j).weight;
                profit += item(j).profit;
                if (verbose == 2)
                    std::cout << "Job: " << j
                        << "; Weight: " << weight
                        << "; Profit: " << profit
                        << std::endl;
                if (items.contains(j)) {
                    duplicates++;
                    if (verbose == 2)
                        std::cout << "Job " << j << " already scheduled." << std::endl;
                }
                items.add(j);
            }
            if (weight > capacity(i)) {
                if (verbose == 2)
                    std::cout << "Knapsack " << i
                        << " has overweight: " << weight << "/" << capacity(i)
                        << std::endl;
                overweight += (capacity(i) - weight);
            }
        }

        bool feasible
            = (duplicates == 0)
            && (overweight == 0);
        if (verbose == 2)
            std::cout << "---" << std::endl;
        if (verbose >= 1) {
            std::cout << "Number of items:            " << items.size() << " / " << number_of_items() << std::endl;
            std::cout << "Duplicates:                 " << duplicates << std::endl;
            std::cout << "Overweight:                 " << overweight << std::endl;
            std::cout << "Feasible:                   " << feasible << std::endl;
            std::cout << "Profit:                     " << profit << std::endl;
        }
        return {feasible, profit};
    }

private:

    void read_dellamico2018(std::ifstream& file)
    {
        KnapsackId m;
        ItemId n;
        file >> m >> n;
        Weight c;
        for (KnapsackId i = 0; i < m; ++i) {
            file >> c;
            add_knapsack(c);
        }
        Weight w;
        Profit p;
        for (ItemId j = 0; j < n; ++j) {
            file >> w >> p;
            add_item(w, p);
        }
    }

    std::vector<Item> items_;
    std::vector<Weight> capacities_;
    Profit profit_sum_ = 0;

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
            << " weight " << instance.item(j).weight
            << " profit " << instance.item(j).profit
            << std::endl;
    }
    return os;
}

}

}
