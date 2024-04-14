# Operations research problems

Data, C++ parsers and solution checkers for various operations research problems.

These are the problems used as examples for [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver), [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver) and [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver).

The data also include CSV files listing the instances for each problem and their best known bounds which can be used with the benchmark scripts from [fontanf/optimizationtools](https://github.com/fontanf/optimizationtools).

Packing:

* [Knapsack problem with conflicts / disjunctively constrained knapsack problem](include/orproblems/packing/knapsack_with_conflicts.hpp)
* [Multidimensional multiple-choice knapsack problem](include/orproblems/packing/multidimensional_multiple_choice_knapsack.hpp)
* [Cutting stock problem](include/orproblems/packing/cutting_stock.hpp)
* [Multiple knapsack problem](include/orproblems/packing/multiple_knapsack.hpp)
* [Quadratic multiple knapsack problem](include/orproblems/packing/quadratic_multiple_knapsack.hpp)
* [Bin packing problem with conflicts](include/orproblems/packing/bin_packing_with_conflicts.hpp)

Assignment:

* [Quadratic assignment problem](include/orproblems/assignment/quadratic_assignment.hpp)

Routing:

* Single vehicle
  * [Traveling salesman problem with release dates](include/orproblems/routing/traveling_salesman_with_release_dates.hpp)
    * Release dates for the arrival of goods to the depot, the solution may require multiple trips.
  * [Traveling repairman problem / minimum latency problem](include/orproblems/routing/traveling_repairman.hpp)
    * Three field classification: `1 | sᵢⱼ | ∑Cⱼ`
  * [Time-dependent orienteering problem](include/orproblems/routing/time_dependent_orienteering.hpp)
  * [Orienteering problem with hotel selection](include/orproblems/routing/orienteering_with_hotel_selection.hpp)
* Multiple vehicles
  * [Capacitated vehicle routing problem](include/orproblems/routing/capacitated_vehicle_routing.hpp)
  * [Vehicle routing problem with time windows](include/orproblems/routing/vehicle_routing_with_time_windows.hpp)
    * Time windows / Capacity constraint / Maximum number of vehicles
  * [Capacitated open vehicle routing problem](include/orproblems/routing/capacitated_open_vehicle_routing.hpp)
    * No need to return to the depot / Capacity constraint / Maximum route length / Maximum number of vehicles
  * [Team orienteering problem](include/orproblems/routing/team_orienteering.hpp)

Scheduling:

* Single machine scheduling
  * [Sequential ordering problem](include/orproblems/scheduling/sequential_ordering.hpp)
    * Three fields classification: `1 | sᵢⱼ, prec | Cₘₐₓ`
  * [Single machine scheduling problem with sequence-dependent setup times, total weighted tardiness](include/orproblems/scheduling/scheduling_with_sdst_twt.hpp)
    * Three field classification: `1 | sᵢⱼ | ∑wⱼTⱼ`
  * [Single machine order acceptance and scheduling problem with time windows and sequence-dependent setup times, total weighted tardiness](include/orproblems/scheduling/order_acceptance_and_scheduling.hpp)
    * Three field classification: `1 | rⱼ, sᵢⱼ, reject, đⱼ | ∑wⱼTⱼ - ∑vⱼ`
  * [Job sequencing and tool switching](include/orproblems/scheduling/job_sequencing_and_tool_switching.hpp)
  * [Single machine batch scheduling problem, total completion time](include/orproblems/scheduling/batch_scheduling_total_completion_time.hpp)
    * Three field classification: `1 | batch, sⱼ | ∑Cⱼ`
  * [Single machine batch scheduling problem, total weighted tardiness](include/orproblems/scheduling/batch_scheduling_total_weighted_tardiness.hpp)
    * Three field classification: `1 | batch, rⱼ, sⱼ, compt | ∑wⱼTⱼ`
* (Unrelated) parallel machine scheduling
  * [Identical parallel machine scheduling problem with family setup times, total weighted completion time](include/orproblems/scheduling/parallel_scheduling_with_family_setup_times_twct.hpp)
    * Three field classification: `P | sᵢ | ∑wⱼCⱼ`
* Flow shop scheduling
  * [Permutation flow shop scheduling problem, makespan](include/orproblems/scheduling/permutation_flowshop_scheduling_makespan.hpp)
    * Three field classification: `Fm | prmu | Cₘₐₓ`
  * [Permutation flow shop scheduling problem, total completion time](include/orproblems/scheduling/permutation_flowshop_scheduling_tct.hpp)
    * Three field classification: `Fm | prmu | ∑Cⱼ`
  * [Permutation flow shop scheduling problem, total tardiness](include/orproblems/scheduling/permutationflowshop_schedulingtt.hpp)
    * Three field classification: `Fm | prmu | ∑Tⱼ`
  * [Distributed permutation flow shop scheduling problem, Makespan](include/orproblems/scheduling/distributed_pfss_makespan.hpp)
    * Three field classification: `DFm | prmu | Cₘₐₓ`
  * [Distributed permutation flow shop scheduling problem, Total completion time](include/orproblems/scheduling/distributed_pfss_tct.hpp)
    * Three field classification: `DFm | prmu | ∑Cⱼ`
* Job shop scheduling
  * [No-wait job shop scheduling problem, makespan](include/orproblems/scheduling/no_wait_job_shop_scheduling_makespan.hpp)
    * Three field classification: `Jm | no-wait | Cₘₐₓ`
* Assembly Line Balancing
  * [Simple assembly line balancing problem of type 1 (SALBP-1)](include/orproblems/scheduling/simple_assembly_line_balancing_1.hpp)
    * Bin Packing Problem with precedence constraints of the form `bin(j1) <= bin(j2) `
  * [U-shaped assembly line balancing problem of type 1 (UALBP-1)](include/orproblems/scheduling/u_shaped_assembly_line_balancing_1.hpp)
