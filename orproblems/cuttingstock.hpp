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

#include "optimizationtools/containers/indexed_set.hpp"

#include <fstream>
#include <iostream>

namespace orproblems
{

namespace cuttingstock
{

typedef int64_t ItemTypeId;
typedef int64_t ItemPos;
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
        if (!file.good()) {
            throw std::runtime_error(
                    "Unable to open file \"" + instance_path + "\".");
        }
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

    std::pair<bool, BinId> check(
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

        std::vector<Demand> demands(number_of_item_types(), 0);
        ItemPos number_of_unsatisfied_demands = 0;
        BinId number_of_overweighted_bins = 0;
        BinId number_of_bins = 0;
        BinId bin_number_of_copies = -1;
        ItemPos bin_number_of_items = -1;
        while (file >> bin_number_of_copies >> bin_number_of_items) {
            ItemTypeId j = -1;
            Weight bin_weight = 0;
            number_of_bins++;
            if (verbose == 2)
                std::cout << "Bin: " << number_of_bins - 1 << "; Jobs";
            for (ItemPos j_pos = 0; j_pos < bin_number_of_items; ++j_pos) {
                file >> j;
                demands[j] += bin_number_of_copies;
                if (verbose == 2)
                    std::cout << " " << j;
                bin_weight += weight(j);
            }
            if (verbose == 2)
                std::cout << "; Weight: " << bin_weight << " / " << capacity() << std::endl;
            if (bin_weight > capacity()) {
                number_of_overweighted_bins++;
                if (verbose == 2)
                    std::cout << "Bin " << number_of_bins - 1 << " is overloaded." << std::endl;
            }
        }
        for (ItemTypeId j = 0; j < number_of_item_types(); ++j) {
            if (demands[j] != demand(j)) {
                number_of_unsatisfied_demands++;
                if (verbose == 2)
                    std::cout << "Item type " << j
                        << "; Demand: " << demands[j] << " / " << demand(j)
                        << "." << std::endl;
            }
        }

        bool feasible
            = (number_of_unsatisfied_demands == 0)
            && (number_of_overweighted_bins);
        if (verbose == 2)
            std::cout << "---" << std::endl;
        if (verbose >= 1) {
            std::cout << "Number of unsatisfied demands:  " << number_of_unsatisfied_demands  << std::endl;
            std::cout << "Number of overweighted bins:    " << number_of_overweighted_bins << std::endl;
            std::cout << "Feasible:                       " << feasible << std::endl;
            std::cout << "Number of bins:                 " << number_of_bins << std::endl;
        }
        return {feasible, number_of_bins};
    }

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

static inline std::ostream& operator<<(
        std::ostream &os, const Instance& instance)
{
    os << "Number of item types: " << instance.number_of_item_types() << std::endl;
    os << "Capacity: " << instance.capacity() << std::endl;
    for (ItemTypeId j = 0; j < instance.number_of_item_types(); ++j) {
        os << "Item " << j
            << ": weight " << instance.weight(j)
            << "; demand" << instance.demand(j)
            << std::endl;
    }
    return os;
}

}

}
