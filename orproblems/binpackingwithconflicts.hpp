#pragma once

/**
 * Bin Packing Problem with Conflicts.
 *
 * Input:
 * - a capacity c
 * - n items with weight wⱼ (j = 1..n)
 * - a graph G such that each node corresponds to an item
 * Problem:
 * - Pack all items into bins such that:
 *   - the total weight of the items of a bin does not exceed the capacity c
 *   - if there exists an edge between j₁ to j₂ in G, then j₁ and j₂ must not
 *     be in the same bin
 * Objective:
 * - Minimize the number of bin used.
 *
 */

#include "optimizationtools/indexed_set.hpp"
#include "optimizationtools/utils.hpp"

#include <fstream>
#include <iostream>

namespace orproblems
{

namespace binpackingwithconflicts
{

typedef int64_t ItemId;
typedef int64_t Weight;
typedef int64_t BinId;

struct Item
{
    ItemId id;
    Weight weight;
    std::vector<ItemId> neighbors;
};

class Instance
{

public:

    Instance() { }
    void set_capacity(Weight capacity) { capacity_ = capacity; }
    void add_item(Weight weight)
    {
        Item item;
        item.id = items_.size();
        item.weight = weight;
        items_.push_back(item);
    }
    void add_conflict(ItemId j1, ItemId j2)
    {
        assert(j1 >= 0);
        assert(j2 >= 0);
        assert(j1 < number_of_items());
        assert(j2 < number_of_items());
        items_[j1].neighbors.push_back(j2);
        items_[j2].neighbors.push_back(j1);
    }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            std::cerr << "\033[31m" << "ERROR, unable to open file \"" << instance_path << "\"" << "\033[0m" << std::endl;
            assert(false);
            return;
        }
        if (format == "" || format == "default") {
            read_default(file);
        } else {
            std::cerr << "\033[31m" << "ERROR, unknown instance format \"" << format << "\"" << "\033[0m" << std::endl;
        }
        file.close();
    }

    virtual ~Instance() { }

    ItemId number_of_items() const { return items_.size(); }
    Weight capacity() const { return capacity_; }
    const Item& item(ItemId j) const { return items_[j]; }

private:

    void read_default(std::ifstream& file)
    {
        std::string tmp;
        std::vector<std::string> line;

        ItemId n;
        Weight c;
        file >> n >> c;
        set_capacity(c);

        Weight w = -1;
        ItemId j_tmp = -1;
        for (ItemId j = 0; j < n; ++j) {
            file >> j_tmp >> w;
            add_item(w);
            getline(file, tmp);
            line = optimizationtools::split(tmp, ' ');
            for (std::string s: line)
                if (std::stol(s) - 1 < j)
                    add_conflict(j, std::stol(s) - 1);
        }
    }

    std::vector<Item> items_;
    Weight capacity_;

};

}

}
