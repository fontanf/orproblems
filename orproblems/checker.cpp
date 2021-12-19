#include "orproblems/knapsackwithconflicts.hpp"
#include "orproblems/multidimensionalmultiplechoiceknapsack.hpp"
#include "orproblems/quadraticassignment.hpp"
#include "orproblems/cuttingstock.hpp"
#include "orproblems/multipleknapsack.hpp"
#include "orproblems/quadraticmultipleknapsack.hpp"
#include "orproblems/generalizedquadraticmultipleknapsack.hpp"
#include "orproblems/binpackingwithconflicts.hpp"

#include "orproblems/travellingsalesman.hpp"
#include "orproblems/sequentialordering.hpp"
#include "orproblems/travellingrepairman.hpp"
#include "orproblems/thieforienteering.hpp"
#include "orproblems/capacitatedvehiclerouting.hpp"
#include "orproblems/vehicleroutingwithtimewindows.hpp"
#include "orproblems/capacitatedopenvehiclerouting.hpp"

#include "orproblems/schedulingwithsdsttwt.hpp"
#include "orproblems/orderacceptanceandscheduling.hpp"
#include "orproblems/batchschedulingtotalcompletiontime.hpp"
#include "orproblems/batchschedulingtotalweightedtardiness.hpp"
#include "orproblems/parallelschedulingwithfamilysetuptimestwct.hpp"
#include "orproblems/starobservationscheduling.hpp"
#include "orproblems/permutationflowshopschedulingmakespan.hpp"
#include "orproblems/permutationflowshopschedulingtct.hpp"
#include "orproblems/permutationflowshopschedulingtt.hpp"
#include "orproblems/simpleassemblylinebalancing1.hpp"
#include "orproblems/ushapedassemblylinebalancing1.hpp"

#include <boost/program_options.hpp>

using namespace orproblems;

namespace po = boost::program_options;

int main(int argc, char *argv[])
{

    // Parse program options

    std::string problem = "";
    std::string instance_path = "";
    std::string format = "";
    std::string certificate_path = "";
    int verbose = 1;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("problem,p", po::value<std::string>(&problem)->required(), "set problem (required)")
        ("input,i", po::value<std::string>(&instance_path)->required(), "set input path (required)")
        ("certificate,c", po::value<std::string>(&certificate_path), "set certificate path")
        ("format,f", po::value<std::string>(&format), "set input file format (default: orlibrary)")
        ("print-instance", "")
        ("verbose,v", po::value<int>(&verbose), "set verbose level")
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
        knapsackwithconflicts::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "multidimensionalmultiplechoiceknapsack") {
        multidimensionalmultiplechoiceknapsack::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "quadraticassignment") {
        quadraticassignment::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "cuttingstock") {
        cuttingstock::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "multipleknapsack") {
        multipleknapsack::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "quadraticmultipleknapsack") {
        quadraticmultipleknapsack::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "generalizedquadraticmultipleknapsack") {
        generalizedquadraticmultipleknapsack::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "binpackingwithconflicts") {
        binpackingwithconflicts::Instance instance(instance_path, format);
        //if (vm.count("print-instance"))
        //    std::cout << instance << std::endl; TODO
        //instance.check(certificate_path, verbose); TODO

    } else if (problem == "travellingsalesman") {
        travellingsalesman::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "sequentialordering") {
        sequentialordering::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "travellingrepairman") {
        travellingrepairman::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "thieforienteering") {
        thieforienteering::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "capacitatedvehiclerouting") {
        capacitatedvehiclerouting::Instance instance(instance_path, format);
        //if (vm.count("print-instance"))
        //    std::cout << instance << std::endl; TODO
        //instance.check(certificate_path, verbose); TODO

    } else if (problem == "vehicleroutingwithtimewindows") {
        vehicleroutingwithtimewindows::Instance instance(instance_path, format);
        //if (vm.count("print-instance"))
        //    std::cout << instance << std::endl; TODO
        //instance.check(certificate_path, verbose); TODO

    } else if (problem == "capacitatedopenvehiclerouting") {
        capacitatedopenvehiclerouting::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        //instance.check(certificate_path, verbose); TODO

    } else if (problem == "schedulingwithsdsttwt") {
        schedulingwithsdsttwt::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "orderacceptanceandscheduling") {
        orderacceptanceandscheduling::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "batchschedulingtotalcompletiontime") {
        batchschedulingtotalcompletiontime::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "batchschedulingtotalweightedtardiness") {
        batchschedulingtotalweightedtardiness::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "parallelschedulingwithfamilysetuptimestwct") {
        parallelschedulingwithfamilysetuptimestwct::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        //instance.check(certificate_path, verbose); TODO

    } else if (problem == "starobservationscheduling") {
        starobservationscheduling::Instance instance(instance_path, format);
        //if (vm.count("print-instance"))
        //    std::cout << instance << std::endl; TODO
        //instance.check(certificate_path, verbose); TODO

    } else if (problem == "permutationflowshopschedulingmakespan") {
        permutationflowshopschedulingmakespan::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "permutationflowshopschedulingtct") {
        permutationflowshopschedulingtct::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "permutationflowshopschedulingtt") {
        permutationflowshopschedulingtt::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "simpleassemblylinebalancing1") {
        simpleassemblylinebalancing1::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else if (problem == "ushapedassemblylinebalancing1") {
        ushapedassemblylinebalancing1::Instance instance(instance_path, format);
        if (vm.count("print-instance"))
            std::cout << instance << std::endl;
        instance.check(certificate_path, verbose);

    } else {
        throw std::invalid_argument(
                "Unknown problem: '" + problem + "'.");
        return 1;
    }

    return 0;
}

