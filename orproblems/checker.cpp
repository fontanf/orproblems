#include "orproblems/knapsackwithconflicts.hpp"
#include "orproblems/multidimensionalmultiplechoiceknapsack.hpp"
#include "orproblems/quadraticassignment.hpp"
#include "orproblems/cuttingstock.hpp"
#include "orproblems/multipleknapsack.hpp"
#include "orproblems/quadraticmultipleknapsack.hpp"
#include "orproblems/generalizedquadraticmultipleknapsack.hpp"
#include "orproblems/binpackingwithconflicts.hpp"

#include "orproblems/sequentialordering.hpp"
#include "orproblems/travelingsalesmanwithreleasedates.hpp"
#include "orproblems/travelingrepairman.hpp"
#include "orproblems/timedependentorienteering.hpp"
#include "orproblems/orienteeringwithhotelselection.hpp"
#include "orproblems/capacitatedvehiclerouting.hpp"
#include "orproblems/vehicleroutingwithtimewindows.hpp"
#include "orproblems/capacitatedopenvehiclerouting.hpp"

#include "orproblems/schedulingwithsdsttwt.hpp"
#include "orproblems/orderacceptanceandscheduling.hpp"
#include "orproblems/batchschedulingtotalcompletiontime.hpp"
#include "orproblems/batchschedulingtotalweightedtardiness.hpp"
#include "orproblems/parallelschedulingwithfamilysetuptimestwct.hpp"
#include "orproblems/permutationflowshopschedulingmakespan.hpp"
#include "orproblems/permutationflowshopschedulingtct.hpp"
#include "orproblems/permutationflowshopschedulingtt.hpp"
#include "orproblems/distributedpfssmakespan.hpp"
#include "orproblems/distributedpfsstct.hpp"
#include "orproblems/nowaitjobshopschedulingmakespan.hpp"
#include "orproblems/simpleassemblylinebalancing1.hpp"
#include "orproblems/ushapedassemblylinebalancing1.hpp"

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

    if (problem == "knapsackwithconflicts") {
        check(
                knapsackwithconflicts::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "multidimensionalmultiplechoiceknapsack") {
        check(
                multidimensionalmultiplechoiceknapsack::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "quadraticassignment") {
        check(
                quadraticassignment::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "cuttingstock") {
        check(
                cuttingstock::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "multipleknapsack") {
        check(
                multipleknapsack::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "quadraticmultipleknapsack") {
        check(
                quadraticmultipleknapsack::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "generalizedquadraticmultipleknapsack") {
        check(
                generalizedquadraticmultipleknapsack::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "binpackingwithconflicts") {
        check(
                binpackingwithconflicts::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "sequentialordering") {
        check(
                sequentialordering::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "travelingrepairman") {
        check(
                travelingrepairman::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "travelingsalesmanwithreleasedates") {
        check(
                travelingsalesmanwithreleasedates::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "timedependentorienteering") {
        check(
                timedependentorienteering::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "orienteeringwithhotelselection") {
        check(
                orienteeringwithhotelselection::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "capacitatedvehiclerouting") {
        check(
                capacitatedvehiclerouting::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "vehicleroutingwithtimewindows") {
        check(
                vehicleroutingwithtimewindows::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "capacitatedopenvehiclerouting") {
        check(
                capacitatedopenvehiclerouting::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "schedulingwithsdsttwt") {
        check(
                schedulingwithsdsttwt::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "orderacceptanceandscheduling") {
        check(
                orderacceptanceandscheduling::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "batchschedulingtotalcompletiontime") {
        check(
                batchschedulingtotalcompletiontime::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "batchschedulingtotalweightedtardiness") {
        check(
                batchschedulingtotalweightedtardiness::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "parallelschedulingwithfamilysetuptimestwct") {
        check(
                parallelschedulingwithfamilysetuptimestwct::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "permutationflowshopschedulingmakespan") {
        check(
                permutationflowshopschedulingmakespan::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "permutationflowshopschedulingtct") {
        check(
                permutationflowshopschedulingtct::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "permutationflowshopschedulingtt") {
        check(
                permutationflowshopschedulingtt::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "distributedpfssmakespan") {
        check(
                distributedpfssmakespan::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "distributedpfsstct") {
        check(
                distributedpfsstct::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "nowaitjobshopschedulingmakespan") {
        check(
                nowaitjobshopschedulingmakespan::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "simpleassemblylinebalancing1") {
        check(
                simpleassemblylinebalancing1::InstanceBuilder(),
                instance_path,
                instance_format,
                certificate_path,
                verbosity_level);

    } else if (problem == "ushapedassemblylinebalancing1") {
        check(
                ushapedassemblylinebalancing1::InstanceBuilder(),
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

