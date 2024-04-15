add_library(ORProblems_knapsack_with_conflicts INTERFACE)
target_link_libraries(ORProblems_knapsack_with_conflicts INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_knapsack_with_conflicts INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::knapsack_with_conflicts ALIAS ORProblems_knapsack_with_conflicts)

add_library(ORProblems_multidimensional_multiple_choice_knapsack INTERFACE)
target_link_libraries(ORProblems_multidimensional_multiple_choice_knapsack INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_multidimensional_multiple_choice_knapsack INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::multidimensional_multiple_choice_knapsack ALIAS ORProblems_multidimensional_multiple_choice_knapsack)

add_library(ORProblems_cutting_stock INTERFACE)
target_link_libraries(ORProblems_cutting_stock INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_cutting_stock INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::cutting_stock ALIAS ORProblems_cutting_stock)

add_library(ORProblems_multiple_knapsack INTERFACE)
target_link_libraries(ORProblems_multiple_knapsack INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_multiple_knapsack INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::multiple_knapsack ALIAS ORProblems_multiple_knapsack)

add_library(ORProblems_quadratic_multiple_knapsack INTERFACE)
target_link_libraries(ORProblems_quadratic_multiple_knapsack INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_quadratic_multiple_knapsack INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::quadratic_multiple_knapsack ALIAS ORProblems_quadratic_multiple_knapsack)

add_library(ORProblems_generalized_quadratic_multiple_knapsack INTERFACE)
target_link_libraries(ORProblems_generalized_quadratic_multiple_knapsack INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_generalized_quadratic_multiple_knapsack INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::generalized_quadratic_multiple_knapsack ALIAS ORProblems_generalized_quadratic_multiple_knapsack)

add_library(ORProblems_bin_packing_with_conflicts INTERFACE)
target_link_libraries(ORProblems_bin_packing_with_conflicts INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_bin_packing_with_conflicts INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::bin_packing_with_conflicts ALIAS ORProblems_bin_packing_with_conflicts)


add_library(ORProblems_quadratic_assignment INTERFACE)
target_link_libraries(ORProblems_quadratic_assignment INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_quadratic_assignment INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::quadratic_assignment ALIAS ORProblems_quadratic_assignment)


add_library(ORProblems_traveling_salesman_with_release_dates INTERFACE)
target_link_libraries(ORProblems_traveling_salesman_with_release_dates INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_traveling_salesman_with_release_dates INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::traveling_salesman_with_release_dates ALIAS ORProblems_traveling_salesman_with_release_dates)

add_library(ORProblems_traveling_repairman INTERFACE)
target_link_libraries(ORProblems_traveling_repairman INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_traveling_repairman INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::traveling_repairman ALIAS ORProblems_traveling_repairman)

add_library(ORProblems_time_dependent_orienteering INTERFACE)
target_link_libraries(ORProblems_time_dependent_orienteering INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils
    Boost::filesystem
    Boost::regex)
target_include_directories(ORProblems_time_dependent_orienteering INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::time_dependent_orienteering ALIAS ORProblems_time_dependent_orienteering)

add_library(ORProblems_orienteering_with_hotel_selection INTERFACE)
target_link_libraries(ORProblems_orienteering_with_hotel_selection INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_orienteering_with_hotel_selection INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::orienteering_with_hotel_selection ALIAS ORProblems_knapsack_with_conflicts)

add_library(ORProblems_capacitated_vehicle_routing INTERFACE)
target_link_libraries(ORProblems_capacitated_vehicle_routing INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils
    TravelingSalesmanSolver::distances)
target_include_directories(ORProblems_capacitated_vehicle_routing INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::capacitated_vehicle_routing ALIAS ORProblems_capacitated_vehicle_routing)

add_library(ORProblems_vehicle_routing_with_time_windows INTERFACE)
target_link_libraries(ORProblems_vehicle_routing_with_time_windows INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_vehicle_routing_with_time_windows INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::vehicle_routing_with_time_windows ALIAS ORProblems_vehicle_routing_with_time_windows)

add_library(ORProblems_capacitated_open_vehicle_routing INTERFACE)
target_link_libraries(ORProblems_capacitated_open_vehicle_routing INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils
    TravelingSalesmanSolver::distances)
target_include_directories(ORProblems_capacitated_open_vehicle_routing INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::capacitated_open_vehicle_routing ALIAS ORProblems_capacitated_open_vehicle_routing)

add_library(ORProblems_heterogeneous_fleet_vehicle_routing INTERFACE)
target_link_libraries(ORProblems_heterogeneous_fleet_vehicle_routing INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils
    TravelingSalesmanSolver::distances)
target_include_directories(ORProblems_heterogeneous_fleet_vehicle_routing INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::heterogeneous_fleet_vehicle_routing ALIAS ORProblems_heterogeneous_fleet_vehicle_routing)

add_library(ORProblems_team_orienteering INTERFACE)
target_link_libraries(ORProblems_team_orienteering INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_team_orienteering INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::team_orienteering ALIAS ORProblems_team_orienteering)


add_library(ORProblems_sequential_ordering INTERFACE)
target_link_libraries(ORProblems_sequential_ordering INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_sequential_ordering INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::sequential_ordering ALIAS ORProblems_sequential_ordering)

add_library(ORProblems_scheduling_with_sdst_twt INTERFACE)
target_link_libraries(ORProblems_scheduling_with_sdst_twt INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_scheduling_with_sdst_twt INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::scheduling_with_sdst_twt ALIAS ORProblems_scheduling_with_sdst_twt)

add_library(ORProblems_order_acceptance_and_scheduling INTERFACE)
target_link_libraries(ORProblems_order_acceptance_and_scheduling INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_order_acceptance_and_scheduling INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::order_acceptance_and_scheduling ALIAS ORProblems_order_acceptance_and_scheduling)

add_library(ORProblems_job_sequencing_and_tool_switching INTERFACE)
target_link_libraries(ORProblems_job_sequencing_and_tool_switching INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_job_sequencing_and_tool_switching INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::job_sequencing_and_tool_switching ALIAS ORProblems_job_sequencing_and_tool_switching)

add_library(ORProblems_batch_scheduling_total_completion_time INTERFACE)
target_link_libraries(ORProblems_batch_scheduling_total_completion_time INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_batch_scheduling_total_completion_time INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::batch_scheduling_total_completion_time ALIAS ORProblems_batch_scheduling_total_completion_time)

add_library(ORProblems_batch_scheduling_total_weighted_tardiness INTERFACE)
target_link_libraries(ORProblems_batch_scheduling_total_weighted_tardiness INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_batch_scheduling_total_weighted_tardiness INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::batch_scheduling_total_weighted_tardiness ALIAS ORProblems_batch_scheduling_total_weighted_tardiness)

add_library(ORProblems_parallel_scheduling_with_family_setup_times_twct INTERFACE)
target_link_libraries(ORProblems_parallel_scheduling_with_family_setup_times_twct INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_parallel_scheduling_with_family_setup_times_twct INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::parallel_scheduling_with_family_setup_times_twct ALIAS ORProblems_parallel_scheduling_with_family_setup_times_twct)

add_library(ORProblems_permutation_flowshop_scheduling_makespan INTERFACE)
target_link_libraries(ORProblems_permutation_flowshop_scheduling_makespan INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_permutation_flowshop_scheduling_makespan INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::permutation_flowshop_scheduling_makespan ALIAS ORProblems_permutation_flowshop_scheduling_makespan)

add_library(ORProblems_permutation_flowshop_scheduling_tct INTERFACE)
target_link_libraries(ORProblems_permutation_flowshop_scheduling_tct INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_permutation_flowshop_scheduling_tct INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::permutation_flowshop_scheduling_tct ALIAS ORProblems_permutation_flowshop_scheduling_tct)

add_library(ORProblems_permutation_flowshop_scheduling_tt INTERFACE)
target_link_libraries(ORProblems_permutation_flowshop_scheduling_tt INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_permutation_flowshop_scheduling_tt INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::permutation_flowshop_scheduling_tt ALIAS ORProblems_permutation_flowshop_scheduling_tt)

add_library(ORProblems_distributed_pfss_makespan INTERFACE)
target_link_libraries(ORProblems_distributed_pfss_makespan INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_distributed_pfss_makespan INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::distributed_pfss_makespan ALIAS ORProblems_distributed_pfss_makespan)

add_library(ORProblems_distributed_pfss_tct INTERFACE)
target_link_libraries(ORProblems_distributed_pfss_tct INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_distributed_pfss_tct INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::distributed_pfss_tct ALIAS ORProblems_distributed_pfss_tct)

add_library(ORProblems_no_wait_job_shop_scheduling_makespan INTERFACE)
target_link_libraries(ORProblems_no_wait_job_shop_scheduling_makespan INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils
    interval-tree)
target_include_directories(ORProblems_no_wait_job_shop_scheduling_makespan INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::no_wait_job_shop_scheduling_makespan ALIAS ORProblems_no_wait_job_shop_scheduling_makespan)

add_library(ORProblems_simple_assembly_line_balancing_1 INTERFACE)
target_link_libraries(ORProblems_simple_assembly_line_balancing_1 INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_simple_assembly_line_balancing_1 INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::simple_assembly_line_balancing_1 ALIAS ORProblems_simple_assembly_line_balancing_1)

add_library(ORProblems_u_shaped_assembly_line_balancing_1 INTERFACE)
target_link_libraries(ORProblems_u_shaped_assembly_line_balancing_1 INTERFACE
    OptimizationTools::containers
    OptimizationTools::utils)
target_include_directories(ORProblems_u_shaped_assembly_line_balancing_1 INTERFACE
    ${PROJECT_SOURCE_DIR}/include)
add_library(ORProblems::u_shaped_assembly_line_balancing_1 ALIAS ORProblems_u_shaped_assembly_line_balancing_1)


add_executable(ORProblems_checker_main)
target_sources(ORProblems_checker_main PRIVATE
    checker.cpp)
target_link_libraries(ORProblems_checker_main PUBLIC
    ORProblems_knapsack_with_conflicts
    ORProblems_multidimensional_multiple_choice_knapsack
    ORProblems_cutting_stock
    ORProblems_multiple_knapsack
    ORProblems_quadratic_multiple_knapsack
    ORProblems_generalized_quadratic_multiple_knapsack
    ORProblems_bin_packing_with_conflicts

    ORProblems_quadratic_assignment

    ORProblems_traveling_salesman_with_release_dates
    ORProblems_traveling_repairman
    ORProblems_time_dependent_orienteering
    ORProblems_orienteering_with_hotel_selection
    ORProblems_capacitated_vehicle_routing
    ORProblems_vehicle_routing_with_time_windows
    ORProblems_capacitated_open_vehicle_routing
    ORProblems_heterogeneous_fleet_vehicle_routing
    ORProblems_team_orienteering

    ORProblems_sequential_ordering
    ORProblems_scheduling_with_sdst_twt
    ORProblems_order_acceptance_and_scheduling
    ORProblems_job_sequencing_and_tool_switching
    ORProblems_batch_scheduling_total_completion_time
    ORProblems_batch_scheduling_total_weighted_tardiness
    ORProblems_parallel_scheduling_with_family_setup_times_twct
    ORProblems_permutation_flowshop_scheduling_makespan
    ORProblems_permutation_flowshop_scheduling_tct
    ORProblems_permutation_flowshop_scheduling_tt
    ORProblems_distributed_pfss_makespan
    ORProblems_distributed_pfss_tct
    ORProblems_no_wait_job_shop_scheduling_makespan
    ORProblems_simple_assembly_line_balancing_1
    ORProblems_u_shaped_assembly_line_balancing_1

    Boost::program_options)
set_target_properties(ORProblems_checker_main PROPERTIES OUTPUT_NAME "orproblems_checker")
install(TARGETS ORProblems_checker_main DESTINATION bin)
