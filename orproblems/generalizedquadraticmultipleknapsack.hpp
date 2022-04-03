#pragma once

/**
 * Generalized Quadratic Multiple Knapsack Problem.
 *
 * Input:
 * - m containers (knapsacks); for each knapsack i = 1..m, a capacity cᵢ
 * - o classes; for each class k = 1..o
 *   - a setup time sₖ
 *   - a maximum number of knapsack mₖ
 * - n items; for each item j = 1..n
 *   - a weight wⱼ
 *   - a class rⱼ
 * - for each item j = 1..n, for each knapsack i = 1..m, a profit pⱼᵢ
 * - for each pair of items (j₁, j₂) with j₁ ≠ j₂, a profit pⱼ₁ⱼ₂
 * Problem:
 * - select m disjoint subsets of items (one per knapsack) such that
 *   - for each knapsack i = 1..m, the total weight of the items + the total
 *     setup times of each class in knapsack i does not exceed its capacity cᵢ
 *   - for each class k = 1..o, the items from class k are not in more than mₖ
 *     different knapsacks
 * Objective:
 * - Maximize the overall profit of the knapsacks.
 *   The profit of a knapsack is the sum of the profits of the items and profit
 *   of the pairs of items it contains.
 *
 */

#include "optimizationtools/containers/indexed_set.hpp"

#include <fstream>
#include <iostream>

namespace orproblems
{

namespace generalizedquadraticmultipleknapsack
{

typedef int64_t ItemId;
typedef int64_t ItemPos;
typedef int64_t ClassId;
typedef int64_t KnapsackId;
typedef int64_t Weight;
typedef double Profit;

struct Class
{
    ClassId id;
    Weight setup_time;
    KnapsackId maximum_number_of_knapsacks;
};

struct Item
{
    ItemId id;
    Weight weight;
    ClassId class_id;
    std::vector<Profit> profits;
};

class Instance
{

public:

    Instance() {  }
    void add_knapsack(Weight capacity) { capacities_.push_back(capacity); }
    void add_class(Weight setup_time, KnapsackId maximum_number_of_knapsacks)
    {
        Class item_class;
        item_class.id = classes_.size();
        item_class.setup_time = setup_time;
        item_class.maximum_number_of_knapsacks = maximum_number_of_knapsacks;
        classes_.push_back(item_class);
    }
    void add_item(Weight weight, ClassId k)
    {
        Item item;
        item.id = items_.size();
        item.weight = weight;
        item.class_id = k;
        item.profits = std::vector<Profit>(number_of_knapsacks(), 0);
        items_.push_back(item);
        profits_.push_back(std::vector<Profit>(items_.size()));
    }
    void set_item_profit(ItemId j, KnapsackId i, Profit profit) { items_[j].profits[i] = profit; }
    void set_pair_profit(ItemId j1, ItemId j2, Profit profit)
    {
        profits_[std::min(j1, j2)][std::max(j1, j2)] = profit;
    }

    Instance(std::string instance_path, std::string format = "")
    {
        std::ifstream file(instance_path);
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        if (format == "" || format == "sarac2014") {
            read_sarac2014(file);
        } else {
            throw std::invalid_argument(
                    "Unknown instance format \"" + format + "\".");
        }
        file.close();
    }

    virtual ~Instance() { }

    KnapsackId number_of_knapsacks() const { return capacities_.size(); }
    ClassId number_of_classes() const { return classes_.size(); }
    ItemId number_of_items() const { return items_.size(); }
    const Class& item_class(ClassId k) const { return classes_[k]; }
    const Item& item(ItemId j) const { return items_[j]; }
    Profit item_profit(ItemId j, KnapsackId i) const { return items_[j].profits[i]; }
    Profit pair_profit(ItemId j1, ItemId j2) const { return profits_[std::min(j1, j2)][std::max(j1, j2)]; }
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
        if (!file.good())
            throw std::runtime_error(
                    "Unable to open file \"" + certificate_path + "\".");

        Weight overweight = 0;
        Profit total_profit = 0;
        ItemId n = -1;  // Number of items in knapsack i.
        ItemId j = -1;
        optimizationtools::IndexedSet items(n);
        optimizationtools::IndexedSet knapsack_classes(number_of_classes());
        std::vector<KnapsackId> class_number_of_knapsacks(number_of_classes(), 0);
        ItemPos number_of_duplicates = 0;
        for (KnapsackId i = 0; i < number_of_knapsacks(); ++i) {
            Weight total_weight = 0;
            file >> n;
            std::vector<ItemId> current_knapsack_items;
            for (ItemPos j_pos = 0; j_pos < n; ++j_pos) {
                file >> j;
                total_weight += item(j).weight;
                total_profit += item_profit(j, i);
                for (ItemId j2: current_knapsack_items)
                    total_profit += pair_profit(j, j2);
                current_knapsack_items.push_back(j);
                if (verbose == 2)
                    std::cout << "Job: " << j
                        << "; Weight: " << total_weight
                        << "; Profit: " << total_profit
                        << std::endl;
                knapsack_classes.add(item(j).class_id);
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
            for (ClassId k: knapsack_classes)
                class_number_of_knapsacks[k]++;
        }
        ClassId number_of_class_maximum_number_of_knapsacks_violations = 0;
        for (ClassId k = 0; k < number_of_classes(); ++k) {
            if (class_number_of_knapsacks[k] > item_class(k).maximum_number_of_knapsacks) {
                if (verbose == 2)
                    std::cout << "Class " << k
                        << " number of knapsacks " << class_number_of_knapsacks[k]
                        << " / " << item_class(k).maximum_number_of_knapsacks
                        << std::endl;
                number_of_class_maximum_number_of_knapsacks_violations++;
            }
        }
        bool feasible
            = (number_of_duplicates == 0)
            && (overweight == 0)
            && (number_of_class_maximum_number_of_knapsacks_violations == 0);
        if (verbose == 2)
            std::cout << "---" << std::endl;
        if (verbose >= 1) {
            std::cout << "Number of items:                          " << items.size() << " / " << number_of_items() << std::endl;
            std::cout << "Number of duplicates:                     " << number_of_duplicates << std::endl;
            std::cout << "Overweight:                               " << overweight << std::endl;
            std::cout << "Number of max # of knapsacks violations:  " << number_of_class_maximum_number_of_knapsacks_violations << std::endl;
            std::cout << "Feasible:                                 " << feasible << std::endl;
            std::cout << "Profit:                                   " << total_profit << std::endl;
        }
        return {feasible, total_profit};
    }

private:

    void read_sarac2014(std::ifstream& file)
    {
        //std::string tmp;
        //file >> tmp;
        //KnapsackId m;
        //ItemId n;
        //file >> m >> n;

        //for (ItemId j = 0; j < n; ++j)
        //    add_item(0);

        //Profit p;
        //for (ItemId j = 0; j < n; ++j) {
        //    file >> p;
        //    set_profit(j, p);
        //}
        //for (ItemId j1 = 0; j1 < n; ++j1) {
        //    for (ItemId j2 = j1 + 1; j2 < n; ++j2) {
        //        file >> p;
        //        set_profit(j1, j2, p);
        //    }
        //}

        //Weight c = -1;
        //file >> c;
        //file >> c;
        //for (KnapsackId i = 0; i < m; ++i)
        //    add_knapsack(c);

        //Weight w = -1;
        //for (ItemId j = 0; j < n; ++j) {
        //    file >> w;
        //    set_weight(j, w);
        //}
    }

    std::vector<Class> classes_;
    std::vector<Item> items_;
    std::vector<std::vector<Profit>> profits_;
    std::vector<Weight> capacities_;

};

static inline std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "number of knapsacks " << instance.number_of_knapsacks() << std::endl;
    os << "number of classes " << instance.number_of_classes() << std::endl;
    os << "number of items " << instance.number_of_items() << std::endl;
    for (KnapsackId i = 0; i < instance.number_of_knapsacks(); ++i) {
        os << "knapsack " << i
            << " capacity " << instance.capacity(i)
            << std::endl;
    }
    for (ClassId k = 0; k < instance.number_of_classes(); ++k) {
        os << "class " << k
            << " setup time " << instance.item_class(k).setup_time
            << " maximum number of knapsacks " << instance.item_class(k).maximum_number_of_knapsacks
            << std::endl;
    }
    for (ItemId j = 0; j < instance.number_of_items(); ++j) {
        os << "item " << j
            << " weight " << instance.item(j).weight
            << " class " << instance.item(j).class_id;
        os << "item profits";
        for (KnapsackId i = 0; i < instance.number_of_knapsacks(); ++i)
            os << " " << instance.item_profit(j, i);
        os << std::endl;
        os << "pair profits";
        for (ItemId j2 = j; j2 < instance.number_of_items(); ++j2)
            os << " " << instance.pair_profit(j, j2);
        os << std::endl;
    }
    return os;
}

}

}
