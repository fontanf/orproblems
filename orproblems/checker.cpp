#include "orproblems/packing/knapsack_with_conflicts.hpp"
#include "orproblems/packing/multidimensional_multiple_choice_knapsack.hpp"
#include "orproblems/packing/cutting_stock.hpp"
#include "orproblems/packing/multiple_knapsack.hpp"
#include "orproblems/packing/quadratic_multiple_knapsack.hpp"
#include "orproblems/packing/generalized_quadratic_multiple_knapsack.hpp"
#include "orproblems/packing/bin_packing_with_conflicts.hpp"

#include "orproblems/assignment/quadratic_assignment.hpp"

#include "orproblems/routing/traveling_salesman_with_release_dates.hpp"
#include "orproblems/routing/traveling_repairman.hpp"
#include "orproblems/routing/time_dependent_orienteering.hpp"
#include "orproblems/routing/orienteering_with_hotel_selection.hpp"
#include "orproblems/routing/capacitated_vehicle_routing.hpp"
#include "orproblems/routing/vehicle_routing_with_time_windows.hpp"
#include "orproblems/routing/capacitated_open_vehicle_routing.hpp"

#include "orproblems/scheduling/sequential_ordering.hpp"
#include "orproblems/scheduling/scheduling_with_sdst_twt.hpp"
#include "orproblems/scheduling/order_acceptance_and_scheduling.hpp"
#include "orproblems/scheduling/job_sequencing_and_tool_switching.hpp"
#include "orproblems/scheduling/batch_scheduling_total_completion_time.hpp"
#include "orproblems/scheduling/batch_scheduling_total_weighted_tardiness.hpp"
#include "orproblems/scheduling/parallel_scheduling_with_family_setup_times_twct.hpp"
#include "orproblems/scheduling/permutation_flowshop_scheduling_makespan.hpp"
#include "orproblems/scheduling/permutation_flowshop_scheduling_tct.hpp"
#include "orproblems/scheduling/permutation_flowshop_scheduling_tt.hpp"
#include "orproblems/scheduling/distributed_pfss_makespan.hpp"
#include "orproblems/scheduling/distributed_pfss_tct.hpp"
#include "orproblems/scheduling/no_wait_job_shop_scheduling_makespan.hpp"
#include "orproblems/scheduling/simple_assembly_line_balancing_1.hpp"
#include "orproblems/scheduling/u_shaped_assembly_line_balancing_1.hpp"

#include <boost/program_options.hpp>

using namespace orproblems;

namespace po = boost::program_options;

template<typename InstanceBuilder>
void check(
        InstanceBuilder instance_builder,
        const std::string& instance_path,
        const std::string& instance_format,
        const std::string& certificate_path,
        int verbosity_level)
{
    instance_builder.read(instance_path, instance_format);
    auto instance = instance_builder.build();
    if (verbosity_level > 0) {
        std::cout
            << "Instance" << std::endl
            << "--------" << std::endl;
        instance.format(std::cout, verbosity_level);
    }
    if (verbosity_level > 0) {
        std::cout
            << std::endl
            << "Checker" << std::endl
            << "-------" << std::endl;
        instance.check(certificate_path, std::cout, verbosity_level);
    }
}

int main(int argc, char *argv[])
{
    // Parse program options

    std::string problem = "";
    std::string instance_path = "";
    std::string instance_format = "";
    std::string certificate_path = "";
    int verbosity_level = 1;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("problem,p", po::value<std::string>(&problem)->required(), "set problem (required)")
        ("input,i", po::value<std::string>(&instance_path)->required(), "set input path (required)")
        ("format,f", po::value<std::string>(&instance_format), "set input file format (default: orlibrary)")
        ("certificate,c", po::value<std::string>(&certificate_path), "set certificate path")
        ("verbosity-level,v", po::value<int>(&verbosity_level), "print instance")
        ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    if (vm.count("help")) {
        std::cout << desc << std::endl;;
        return 1;
    }
    try {
        po::notify(vm);
    } catch (const po::required_option& e) {
        std::cout << desc << std::endl;;
        return 1;
    }

    if (problem == "knapsack_with_conflicts") {
        check(
                knapsack_with_conflicts::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "multidimensional_multiple_choice_knapsack") {
        check(
                multidimensional_multiple_choice_knapsack::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "quadratic_assignment") {
        check(
                quadratic_assignment::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "cutting_stock") {
        check(
                cutting_stock::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "multiple_knapsack") {
        check(
                multiple_knapsack::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "quadratic_multiple_knapsack") {
        check(
                quadratic_multiple_knapsack::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "generalized_quadratic_multiple_knapsack") {
        check(
                generalized_quadratic_multiple_knapsack::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "bin_packing_with_conflicts") {
        check(
                bin_packing_with_conflicts::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "sequential_ordering") {
        check(
                sequential_ordering::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "traveling_repairman") {
        check(
                traveling_repairman::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "traveling_salesman_with_release_dates") {
        check(
                traveling_salesman_with_release_dates::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "time_dependent_orienteering") {
        check(
                time_dependent_orienteering::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "orienteering_with_hotel_selection") {
        check(
                orienteering_with_hotel_selection::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "capacitated_vehicle_routing") {
        check(
                capacitated_vehicle_routing::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "vehicle_routing_with_time_windows") {
        check(
                vehicle_routing_with_time_windows::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "capacitated_open_vehicle_routing") {
        check(
                capacitated_open_vehicle_routing::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "scheduling_with_sdst_twt") {
        check(
                scheduling_with_sdst_twt::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "order_acceptance_and_scheduling") {
        check(
                order_acceptance_and_scheduling::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "job_sequencing_and_tool_switching") {
        check(
                job_sequencing_and_tool_switching::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "batch_scheduling_total_completion_time") {
        check(
                batch_scheduling_total_completion_time::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "batch_scheduling_total_weighted_tardiness") {
        check(
                batch_scheduling_total_weighted_tardiness::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "parallel_scheduling_with_family_setup_times_twct") {
        check(
                parallel_scheduling_with_family_setup_times_twct::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "permutation_flowshop_scheduling_makespan") {
        check(
                permutation_flowshop_scheduling_makespan::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "permutation_flowshop_scheduling_tct") {
        check(
                permutation_flowshop_scheduling_tct::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "permutation_flowshop_scheduling_tt") {
        check(
                permutation_flowshop_scheduling_tt::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "distributed_pfss_makespan") {
        check(
                distributed_pfss_makespan::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "distributed_pfss_tct") {
        check(
                distributed_pfss_tct::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "no_wait_job_shop_scheduling_makespan") {
        check(
                no_wait_job_shop_scheduling_makespan::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "simple_assembly_line_balancing_1") {
        check(
                simple_assembly_line_balancing_1::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "u_shaped_assembly_line_balancing_1") {
        check(
                u_shaped_assembly_line_balancing_1::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else {
        throw std::invalid_argument(
                "Unknown problem: '" + problem + "'.");
        return 1;
    }

    return 0;
}

