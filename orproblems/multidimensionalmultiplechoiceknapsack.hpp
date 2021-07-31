#pragma once

/**
 * Multidimmensional Multiple-Choice Knapsack Problem.
 *
 * Input:
 * - TODO
 * Problem:
 * - TODO
 * Objective:
 * - TODO
 *
 */

#include "optimizationtools/indexed_set.hpp"

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
    GroupId group_id;
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
        Item item;
        item.id = items_.size();
        item.group_id = group_id;
        item.profit = profit;
        item.weights.resize(number_of_resources(), 0);
        items_.push_back(item);
        while ((GroupId)groups_.size() <= group_id)
            groups_.push_back({});
        groups_[group_id].push_back(item.id);
    }
    void set_weight(ItemId j, ResourceId r, Weight weight) { items_[j].weights[r] = weight; }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good()) {
            std::cerr << "\033[31m" << "ERROR, unable to open file \"" << instance_path << "\"" << "\033[0m" << std::endl;
            assert(false);
            return;
        }
        if (format == "" || format == "khan2002") {
            read_khan2002(file);
        } else if (format == "shojaei2013") {
            read_shojaei2013(file);
        } else if (format == "mansi2013") {
            read_mansi2013(file);
        } else {
            std::cerr << "\033[31m" << "ERROR, unknown instance format \"" << format << "\"" << "\033[0m" << std::endl;
        }
        file.close();
    }

    virtual ~Instance() { }

    inline ItemId number_of_items() const { return items_.size(); }
    inline GroupId number_of_groups() const { return groups_.size(); }
    inline ResourceId number_of_resources() const { return capacities_.size(); }
    inline const Item& item(ItemId j) const { return items_[j]; }
    inline const std::vector<ItemId>& items(GroupId group_id) const { return groups_[group_id]; }
    inline Weight capacity(ResourceId r) const { return capacities_[r]; }

    std::pair<bool, Profit> check(std::string certificate_path)
    {
        std::ifstream file(certificate_path);
        if (!file.good()) {
            std::cerr << "\033[31m" << "ERROR, unable to open file \"" << certificate_path << "\"" << "\033[0m" << std::endl;
            assert(false);
            return {false, 0};
        }

        optimizationtools::IndexedSet groups(number_of_groups());
        std::vector<Weight> weights(number_of_resources(), 0);
        Profit profit = 0;
        GroupId duplicates = 0;
        ItemId j = 0;
        while (file >> j) {
            if (groups.contains(item(j).group_id)) {
                duplicates++;
                std::cout << "GroupId " << item(j).group_id << " already in the knapsack." << std::endl;
            }
            groups.add(item(j).group_id);
            for (ResourceId r = 0; r < number_of_resources(); ++r)
                weights[r] += item(j).weights[r];
            profit += item(j).profit;
            std::cout << "Item: " << j
                << "; Group: " << item(j).group_id
                << "; Profit: " << item(j).profit
                << std::endl;
        }
        Weight overweight = 0;
        for (ResourceId r = 0; r < number_of_resources(); ++r)
            if (weights[r] > capacity(r))
                overweight += (weights[r] - capacity(r));
        bool feasible
            = (duplicates == 0)
            && (groups.size() == number_of_groups())
            && (overweight == 0);
        std::cout << "---" << std::endl;
        std::cout << "Groups:                     " << groups.size() << " / " << number_of_groups() << std::endl;
        std::cout << "Duplicates:                 " << duplicates << std::endl;
        std::cout << "Overweight:                 " << overweight << std::endl;
        std::cout << "Feasible:                   " << feasible << std::endl;
        std::cout << "Profit:                     " << profit << std::endl;
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
        Profit profit = -1;
        Weight weight = -1;
        ItemId j = 0;
        for (GroupId group_id = 0; group_id < number_of_groups; group_id++) {
            file >> tmp;
            for (ItemId j_pos = 0; j_pos < group_size; ++j_pos) {
                file >> profit;
                add_item(group_id, profit);
                for (ResourceId r = 0; r < number_of_resources; ++r) {
                    file >> weight;
                    set_weight(j, r, weight);
                }
                ++j;
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
        ItemId j = 0;
        for (GroupId group_id = 0; group_id < number_of_groups; group_id++) {
            file >> group_size;
            for (ItemId j_pos = 0; j_pos < group_size; ++j_pos) {
                file >> profit;
                add_item(group_id, profit);
                for (ResourceId r = 0; r < number_of_resources; ++r) {
                    file >> weight;
                    set_weight(j, r, weight);
                }
                ++j;
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
        ItemId j = 0;
        for (GroupId group_id = 0; group_id < number_of_groups; group_id++) {
            for (ItemId j_pos = 0; j_pos < group_size; ++j_pos) {
                file >> profit;
                add_item(group_id, profit);
                for (ResourceId r = 0; r < number_of_resources; ++r) {
                    file >> weight;
                    set_weight(j, r, weight);
                }
                ++j;
            }
        }
    }

    std::vector<Weight> capacities_;
    std::vector<Item> items_;
    std::vector<std::vector<ItemId>> groups_;

};

std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "number of items " << instance.number_of_items() << std::endl;
    os << "number of groups " << instance.number_of_groups() << std::endl;
    os << "number of resources " << instance.number_of_resources() << std::endl;
    os << "capacities";
    for (ResourceId r = 0; r < instance.number_of_resources(); ++r)
        os << " " << instance.capacity(r);
    os << std::endl;
    os << "items" << std::endl;
    for (ItemId j = 0; j < instance.number_of_items(); ++j) {
        os << "item " << instance.item(j).id
            << " group " << instance.item(j).group_id
            << " profit " << instance.item(j).profit
            << " weights";
        for (ResourceId r = 0; r < instance.number_of_resources(); ++r)
            os << " " << instance.item(j).weights[r];
        os << std::endl;
    }
    return os;
}

}

}

