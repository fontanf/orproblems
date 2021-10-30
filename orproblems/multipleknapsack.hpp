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
    Weight weight(ItemId j) const { return items_[j].weight; }
    Weight profit(ItemId j) const { return items_[j].profit; }
    Weight capacity(KnapsackId i) const { return capacities_[i]; }
    Profit total_profit() const { return profit_sum_; }

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

}

}
