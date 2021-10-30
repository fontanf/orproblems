#pragma once

/**
 * Cutting Stock Problem.
 *
 * Input:
 * - a capacity c
 * - n items; for each item j = 1..n, a weight wⱼ and a demand qⱼ
 * Problem:
 * - pack all items such that the total weight of the items in a bin does not
 *   exceed the capacity.
 * Objective:
 * - minimize the number of bin used.
 *
 */

#include "optimizationtools/indexed_set.hpp"

#include <fstream>
#include <iostream>

namespace orproblems
{

namespace cuttingstock
{

typedef int64_t ItemTypeId;
typedef int64_t Weight;
typedef int64_t Demand;
typedef int64_t BinId;

struct Item
{
    Weight weight;
    Demand demand;
};

class Instance
{

public:

    Instance() { }
    void set_capacity(Weight capacity) { capacity_ = capacity; }
    void add_item_type(Weight weight, Demand demand = 1)
    {
        item_types_.push_back(Item{weight, demand});
        demand_max_ = std::max(demand_max_, demand);
        demand_sum_ += demand;
    }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        if (format == "" || format == "bpplib_bpp") {
            read_bpplib_bpp(file);
        } else if (format == "bpplib_csp") {
            read_bpplib_csp(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    virtual ~Instance() { }

    ItemTypeId number_of_item_types() const { return item_types_.size(); }
    Weight capacity() const { return capacity_; }
    Weight weight(ItemTypeId j) const { return item_types_[j].weight; }
    Demand demand(ItemTypeId j) const { return item_types_[j].demand; }
    Demand maximum_demand() const { return demand_max_; }
    Demand total_demand() const { return demand_sum_; }

private:

    void read_bpplib_bpp(std::ifstream& file)
    {
        ItemTypeId n;
        Weight c;
        file >> n >> c;
        set_capacity(c);
        Weight w;
        for (ItemTypeId j = 0; j < n; ++j) {
            file >> w;
            add_item_type(w);
        }
    }

    void read_bpplib_csp(std::ifstream& file)
    {
        ItemTypeId n;
        Weight c;
        file >> n >> c;
        set_capacity(c);
        Weight w;
        Demand q;
        for (ItemTypeId j = 0; j < n; ++j) {
            file >> w >> q;
            add_item_type(w, q);
        }
    }

    std::vector<Item> item_types_;
    Weight capacity_;
    Demand demand_max_ = 0;
    Demand demand_sum_ = 0;

};

}

}
