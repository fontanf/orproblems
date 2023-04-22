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
#include <iomanip>

namespace orproblems
{

namespace multidimensionalmultiplechoiceknapsack
{

using ItemId = int64_t;
using GroupId = int64_t;
using Profit = int64_t;
using ResourceId = int64_t;
using Weight = int64_t;

/*
 * Structure for an item.
 */
struct Item
{
    /** Profit. */
    Profit profit;

    /** Weights. */
    std::vector<Weight> weights;
};

/**
 * Instance class for a 'multidimensionalmultiplechoiceknapsack' problem.
 */
class Instance
{

public:

    /*
     * Constructors and destructor
     */

    /** Constructor to build an instance manually. */
    Instance() { }

    /** Add a resource. */
    void add_resource(Weight capacity) { capacities_.push_back(capacity); }

    /** Add an item. */
    void add_item(
            GroupId group_id,
            Profit profit)
    {
        while ((GroupId)groups_.size() <= group_id)
            groups_.push_back({});

        Item item;
        item.profit = profit;
        item.weights.resize(number_of_resources(), 0);
        groups_[group_id].push_back(item);
        if (largest_group_size_ < (ItemId)groups_[group_id].size())
            largest_group_size_ = groups_[group_id].size();
        number_of_items_++;
    }

    /** Set the weight of an item. */
    void set_weight(
            GroupId group_id,
            ItemId item_id,
            ResourceId resource_id,
            Weight weight)
    {
        groups_[group_id][item_id].weights[resource_id] = weight;
    }

    /** Build an instance from a file. */
    Instance(
            std::string instance_path,
            std::string format = "")
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

    /*
     * Getters
     */

    /** Get the number of groups. */
    inline GroupId number_of_groups() const { return groups_.size(); }

    /** Get the number of items. */
    inline GroupId number_of_items() const { return number_of_items_; }

    /** Get an item. */
    inline const Item& item(
            GroupId group_id,
            ItemId item_id) const
    {
        return groups_[group_id][item_id];
    }

    /** Get the number of items in a group. */
    inline ItemId number_of_items(GroupId group_id) const { return groups_[group_id].size(); }

    /** Get the largest group size */
    inline ItemId largest_group_size() const { return largest_group_size_; }

    /** Get the number of resources. */
    inline ResourceId number_of_resources() const { return capacities_.size(); }

    /** Get the capacity of a resource. */
    inline Weight capacity(ResourceId resource_id) const { return capacities_[resource_id]; }

    /** Print the instance. */
    std::ostream& print(
            std::ostream& os,
            int verbose = 1) const
    {
        if (verbose >= 1) {
            os
                << "Number of groups:        " << number_of_groups() << std::endl
                << "Number of items:         " << number_of_items() << std::endl
                << "Number of resources:     " << number_of_resources() << std::endl
                ;
        }
        // Print resources.
        if (verbose >= 2) {
            os << std::endl
                << std::setw(12) << "Resource"
                << std::setw(12) << "Capacity"
                << std::endl
                << std::setw(12) << "--------"
                << std::setw(12) << "--------"
                << std::endl;
            for (ResourceId resource_id = 0;
                    resource_id < number_of_resources();
                    ++resource_id) {
                os
                    << std::setw(12) << resource_id
                    << std::setw(12) << capacity(resource_id)
                    << std::endl;
            }
        }
        // Print groups.
        if (verbose >= 2) {
            os << std::endl
                << std::setw(12) << "Group"
                << std::setw(12) << "# items"
                << std::endl
                << std::setw(12) << "-----"
                << std::setw(12) << "-------"
                << std::endl;
            for (GroupId group_id = 0;
                    group_id < number_of_groups();
                    ++group_id) {
                os
                    << std::setw(12) << group_id
                    << std::setw(12) << number_of_items(group_id)
                    << std::endl;
            }
        }
        // Print items.
        if (verbose >= 3) {
            os << std::endl
                << std::setw(12) << "Group"
                << std::setw(12) << "Item"
                << std::setw(12) << "Profit"
                << std::endl
                << std::setw(12) << "-----"
                << std::setw(12) << "----"
                << std::setw(12) << "------"
                << std::endl;
            for (GroupId group_id = 0; group_id < number_of_groups(); ++group_id) {
                for (ItemId item_id = 0;
                        item_id < number_of_items(group_id);
                        ++item_id) {
                    const Item& item = this->item(group_id, item_id);
                    os
                        << std::setw(12) << group_id
                        << std::setw(12) << item_id
                        << std::setw(12) << item.profit
                        << std::endl;
                }
            }
        }
        // Print weights.
        if (verbose >= 4) {
            os << std::endl
                << std::setw(12) << "Group"
                << std::setw(12) << "Item"
                << std::setw(12) << "Resource"
                << std::setw(12) << "Weight"
                << std::endl
                << std::setw(12) << "-----"
                << std::setw(12) << "----"
                << std::setw(12) << "--------"
                << std::setw(12) << "------"
                << std::endl;
            for (GroupId group_id = 0;
                    group_id < number_of_groups();
                    ++group_id) {
                for (ItemId item_id = 0;
                        item_id < number_of_items(group_id);
                        ++item_id) {
                    const Item& item = this->item(group_id, item_id);
                    for (ResourceId resource_id = 0;
                            resource_id < number_of_resources();
                            ++resource_id) {
                        os
                            << std::setw(12) << group_id
                            << std::setw(12) << item_id
                            << std::setw(12) << resource_id
                            << std::setw(12) << item.weights[resource_id]
                            << std::endl;
                    }
                }
            }
        }
        return os;
    }

    /** Check a certificate. */
    std::pair<bool, Profit> check(
            std::string certificate_path,
            std::ostream& os,
            int verbose = 1) const
    {
        std::ifstream file(certificate_path);
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");
        }

        if (verbose >= 2) {
            os << std::endl
                << std::setw(12) << "Group"
                << std::setw(12) << "Item"
                << std::setw(12) << "Profit"
                << std::endl
                << std::setw(12) << "-----"
                << std::setw(12) << "----"
                << std::setw(12) << "------"
                << std::endl;
        }

        std::vector<Weight> weights(number_of_resources(), 0);
        Profit profit = 0;
        GroupId group_id = 0;
        ItemId item_id = -1;
        while (file >> item_id) {
            const Item& item = this->item(group_id, item_id);
            for (ResourceId resource_id = 0;
                    resource_id < number_of_resources();
                    ++resource_id) {
                weights[resource_id] += item.weights[resource_id];
            }
            profit += item.profit;

            if (verbose >= 2) {
                os
                    << std::setw(12) << group_id
                    << std::setw(12) << item_id
                    << std::setw(12) << profit
                    << std::endl;
            }

            group_id++;
        }

        Weight overweight = 0;
        for (ResourceId resource_id = 0;
                resource_id < number_of_resources();
                ++resource_id) {
            if (weights[resource_id] > capacity(resource_id))
                overweight += (weights[resource_id] - capacity(resource_id));
        }

        bool feasible
            = (overweight == 0)
            && (group_id == number_of_groups());
        if (verbose >= 2)
            os << std::endl;
        if (verbose >= 1) {
            os
                << "Number of groups:           " << group_id << " / " << number_of_groups() << std::endl
                << "Overweight:                 " << overweight << std::endl
                << "Feasible:                   " << feasible << std::endl
                << "Profit:                     " << profit << std::endl
            ;
        }
        return {feasible, profit};
    }

private:

    /*
     * Private methods
     */

    /** Read an instance from a file in 'khan2002' format. */
    void read_khan2002(std::ifstream& file)
    {
        ItemId number_of_groups = -1;
        ItemId group_size = -1;
        ResourceId number_of_resources = -1;
        file >> number_of_groups >> group_size >> number_of_resources;

        ResourceId capacity = -1;
        for (ResourceId resource_id = 0;
                resource_id < number_of_resources;
                ++resource_id) {
            file >> capacity;
            add_resource(capacity);
        }

        std::string tmp;
        double profit = -1;
        Weight weight = -1;
        for (GroupId group_id = 0; group_id < number_of_groups; group_id++) {
            file >> tmp;
            for (ItemId item_id = 0; item_id < group_size; ++item_id) {
                file >> profit;
                add_item(group_id, std::round(profit));
                for (ResourceId resource_id = 0;
                        resource_id < number_of_resources;
                        ++resource_id) {
                    file >> weight;
                    set_weight(
                            group_id,
                            item_id,
                            resource_id,
                            weight);
                }
            }
        }
    }

    /** Read an instance from a file in 'shojaei2013' format. */
    void read_shojaei2013(std::ifstream& file)
    {
        ItemId number_of_groups = -1;
        ResourceId number_of_resources = -1;
        file >> number_of_groups >> number_of_resources;

        ResourceId capacity = -1;
        for (ResourceId resource_id = 0;
                resource_id < number_of_resources;
                ++resource_id) {
            file >> capacity;
            add_resource(capacity);
        }

        ItemId group_size = -1;
        Profit profit = -1;
        Weight weight = -1;
        for (GroupId group_id = 0; group_id < number_of_groups; group_id++) {
            file >> group_size;
            for (ItemId item_id = 0; item_id < group_size; ++item_id) {
                file >> profit;
                add_item(group_id, profit);
                for (ResourceId resource_id = 0;
                        resource_id < number_of_resources;
                        ++resource_id) {
                    file >> weight;
                    set_weight(
                            group_id,
                            item_id,
                            resource_id,
                            weight);
                }
            }
        }
    }

    /** Read an instance from a file in 'mansi2013' format. */
    void read_mansi2013(std::ifstream& file)
    {
        ItemId number_of_groups = -1;
        ItemId group_size = -1;
        ResourceId number_of_resources = -1;
        file >> number_of_groups >> group_size >> number_of_resources;

        ResourceId capacity = -1;
        for (ResourceId resource_id = 0;
                resource_id < number_of_resources;
                ++resource_id) {
            file >> capacity;
            add_resource(capacity);
        }

        Profit profit = -1;
        Weight weight = -1;
        for (GroupId group_id = 0; group_id < number_of_groups; group_id++) {
            for (ItemId item_id = 0; item_id < group_size; ++item_id) {
                file >> profit;
                add_item(group_id, profit);
                for (ResourceId resource_id = 0;
                        resource_id < number_of_resources;
                        ++resource_id) {
                    file >> weight;
                    set_weight(
                            group_id,
                            item_id,
                            resource_id,
                            weight);
                }
            }
        }
    }

    /*
     * Private attributes
     */

    /** Capacities. */
    std::vector<Weight> capacities_;

    /** Groups. */
    std::vector<std::vector<Item>> groups_;

    /** Number of items. */
    ItemId number_of_items_ = 0;

    /*
     * Computed attributes
     */

    /** Largest group size. */
    ItemId largest_group_size_ = 0;

};

}

}

