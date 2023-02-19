/**
 * Multidimmensional Multiple-choice Knapsack Problem.
 *
 * Input:
 * - m resources with capacity cᵢ
 * - o groups
 * - n items; for each item j = 1..n:
 *   - a group gⱼ
 *   - a profit pⱼ
 *   - for each resource i = 1..m, a weight wⱼᵢ
 * Problem:
 * - Select one item from each group such that:
 *   - for each resource, the total weight of the selected items does not
 *     exceed the capacity of the resource
 * Objective:
 * - Maximize the total profit of the selected items
 *
 */

#pragma once

#include "optimizationtools/containers/indexed_set.hpp"

#include <iostream>
#include <fstream>

namespace orproblems
{

namespace multidimensionalmultiplechoiceknapsack
{

using ItemId = int64_t;
using GroupId = int64_t;
using Profit = int64_t;
using ResourceId = int64_t;
using Weight = int64_t;

struct Item
{
    ItemId id;
    Profit profit;
    std::vector<Weight> weights;
};

class Instance
{

public:

    Instance() { }
    void add_resource(Weight capacity) { capacities_.push_back(capacity); }
    void add_item(GroupId group_id, Profit profit)
    {
        while ((GroupId)groups_.size() <= group_id)
            groups_.push_back({});
        Item item;
        item.id = groups_[group_id].size();
        item.profit = profit;
        item.weights.resize(number_of_resources(), 0);
        groups_[group_id].push_back(item);
        if (largest_group_size_ < (ItemId)groups_[group_id].size())
            largest_group_size_ = groups_[group_id].size();
    }
    void set_weight(GroupId group_id, ItemId j, ResourceId r, Weight weight)
    {
        groups_[group_id][j].weights[r] = weight;
    }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        }
        if (format == "" || format == "khan2002") {
            read_khan2002(file);
        } else if (format == "shojaei2013") {
            read_shojaei2013(file);
        } else if (format == "mansi2013") {
            read_mansi2013(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    virtual ~Instance() { }

    inline GroupId number_of_groups() const { return groups_.size(); }
    inline ItemId number_of_items(GroupId group_id) const { return groups_[group_id].size(); }
    inline ItemId largest_group_size() const { return largest_group_size_; }
    inline ResourceId number_of_resources() const { return capacities_.size(); }
    inline const Item& item(GroupId group_id, ItemId j) const { return groups_[group_id][j]; }
    inline Weight capacity(ResourceId r) const { return capacities_[r]; }

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

        std::vector<Weight> weights(number_of_resources(), 0);
        Profit profit = 0;
        GroupId group_id = 0;
        ItemId j = -1;
        while (file >> j) {
            for (ResourceId r = 0; r < number_of_resources(); ++r)
                weights[r] += item(group_id, j).weights[r];
            profit += item(group_id, j).profit;
            if (verbose == 2)
                std::cout << "Group: " << group_id
                    << "; Item: " << j
                    << "; Profit: " << item(group_id, j).profit
                    << std::endl;
            group_id++;
        }
        Weight overweight = 0;
        for (ResourceId r = 0; r < number_of_resources(); ++r)
            if (weights[r] > capacity(r))
                overweight += (weights[r] - capacity(r));

        bool feasible
            = (overweight == 0)
            && (group_id == number_of_groups());
        if (verbose == 2)
            std::cout << "---" << std::endl;
        if (verbose >= 1) {
            std::cout << "Number of groups:           " << group_id << " / " << number_of_groups() << std::endl;
            std::cout << "Overweight:                 " << overweight << std::endl;
            std::cout << "Feasible:                   " << feasible << std::endl;
            std::cout << "Profit:                     " << profit << std::endl;
        }
        return {feasible, profit};
    }

private:

    void read_khan2002(std::ifstream& file)
    {
        ItemId number_of_groups = -1;
        ItemId group_size = -1;
        ResourceId number_of_resources = -1;
        file >> number_of_groups >> group_size >> number_of_resources;

        ResourceId capacity = -1;
        for (ResourceId r = 0; r < number_of_resources; ++r) {
            file >> capacity;
            add_resource(capacity);
        }

        std::string tmp;
        double profit = -1;
        Weight weight = -1;
        for (GroupId group_id = 0; group_id < number_of_groups; group_id++) {
            file >> tmp;
            for (ItemId j = 0; j < group_size; ++j) {
                file >> profit;
                add_item(group_id, std::round(profit));
                for (ResourceId r = 0; r < number_of_resources; ++r) {
                    file >> weight;
                    set_weight(group_id, j, r, weight);
                }
            }
        }
    }

    void read_shojaei2013(std::ifstream& file)
    {
        ItemId number_of_groups = -1;
        ResourceId number_of_resources = -1;
        file >> number_of_groups >> number_of_resources;

        ResourceId capacity = -1;
        for (ResourceId r = 0; r < number_of_resources; ++r) {
            file >> capacity;
            add_resource(capacity);
        }

        ItemId group_size = -1;
        Profit profit = -1;
        Weight weight = -1;
        for (GroupId group_id = 0; group_id < number_of_groups; group_id++) {
            file >> group_size;
            for (ItemId j = 0; j < group_size; ++j) {
                file >> profit;
                add_item(group_id, profit);
                for (ResourceId r = 0; r < number_of_resources; ++r) {
                    file >> weight;
                    set_weight(group_id, j, r, weight);
                }
            }
        }
    }

    void read_mansi2013(std::ifstream& file)
    {
        ItemId number_of_groups = -1;
        ItemId group_size = -1;
        ResourceId number_of_resources = -1;
        file >> number_of_groups >> group_size >> number_of_resources;

        ResourceId capacity = -1;
        for (ResourceId r = 0; r < number_of_resources; ++r) {
            file >> capacity;
            add_resource(capacity);
        }

        Profit profit = -1;
        Weight weight = -1;
        for (GroupId group_id = 0; group_id < number_of_groups; group_id++) {
            for (ItemId j = 0; j < group_size; ++j) {
                file >> profit;
                add_item(group_id, profit);
                for (ResourceId r = 0; r < number_of_resources; ++r) {
                    file >> weight;
                    set_weight(group_id, j, r, weight);
                }
            }
        }
    }

    std::vector<Weight> capacities_;
    std::vector<std::vector<Item>> groups_;
    ItemId largest_group_size_ = 0;

};

static inline std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "number of groups " << instance.number_of_groups() << std::endl;
    os << "number of resources " << instance.number_of_resources() << std::endl;
    os << "capacities";
    for (ResourceId r = 0; r < instance.number_of_resources(); ++r)
        os << " " << instance.capacity(r);
    os << std::endl;
    os << "items" << std::endl;
    for (GroupId group_id = 0; group_id < instance.number_of_groups(); ++group_id) {
        for (ItemId j = 0; j < instance.number_of_items(group_id); ++j) {
            os << "item " << j
                << " group " << group_id
                << " profit " << instance.item(group_id, j).profit
                << " weights";
            for (ResourceId r = 0; r < instance.number_of_resources(); ++r)
                os << " " << instance.item(group_id, j).weights[r];
            os << std::endl;
        }
    }
    return os;
}

}

}

