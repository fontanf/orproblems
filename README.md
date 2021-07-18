# Operations Research Problems

Data, C++ parsers and solution checkers for various Operations Research problems.

These are the problems used as examples for [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver), [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver) and [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver).

The data also include CSV files listing the instances for each problem and their best known bounds which can be used with the benchmark scripts from [fontanf/optimizationtools](https://github.com/fontanf/optimizationtools).

## Packing

[Knapsack Problem with Conflicts](orproblems/knapsackwithconflicts.hpp)
* Literature:
  * "Local branching-based algorithms for the disjunctively constrained knapsack problem" (Akeb et al., 2011) [DOI](https://doi.org/10.1016/j.cie.2011.01.019)
  * "Bin Packing with Conflicts: A Generic Branch-and-Price Algorithm" (Sadykov et Vanderbeck, 2012) [DOI](https://doi.org/10.1287/ijoc.1120.0499)
  * "A Branch-and-Bound Algorithm for the Knapsack Problem with Conflict Graph" (Bettinelli et al., 2017) [DOI](https://doi.org/10.1287/ijoc.2016.0742)
  * "A new combinatorial branch-and-bound algorithm for the Knapsack Problem with Conflicts" (Coniglio et al., 2020) [DOI](https://doi.org/10.1016/j.ejor.2020.07.023)
* Data: [knapsackwithconflicts.7z](https://github.com/fontanf/orproblems/releases/download/data/knapsackwithconflicts.7z)
* Algorithms: [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver/blob/master/examples/knapsackwithconflicts.hpp), [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/knapsackwithconflicts.hpp)

[Multidimensional Multiple-choice Knapsack Problem](orproblems/multidimensionalmultiplechoiceknapsack.hpp)

<details><summary>Literature</summary>
<p>

* Literature:
  * "Heuristic algorithms for the multiple-choice multidimensional knapsack problem" (Hifi et al., 2004) [DOI](https://doi.org/10.1057/palgrave.jors.2601796)
  * "A Reactive Local Search-Based Algorithm for the Multiple-Choice Multi-Dimensional Knapsack Problem" (Hifi et al., 2005) [DOI](https://doi.org/10.1007/s10589-005-3057-0)
  * "Development of core to solve the multidimensional multiple-choice knapsack problem" (Ghasemia et Razzaz, 2011) [DOI](https://doi.org/10.1016/j.cie.2010.12.001)
  * "Iterative semi-continuous relaxation heuristics for the multiple-choice multidimensional knapsack problem" (Crévits et al., 2012) [DOI](https://doi.org/10.1016/j.cor.2010.12.016)
  * "A hybrid heuristic for the multiple choice multidimensional knapsack problem" (Mansi et al., 2012) [DOI](https://doi.org/10.1080/0305215X.2012.717072)
  * "A fast and scalable multidimensional multiple-choice knapsack heuristic" (Shojaei et al., 2013) [DOI](https://doi.org/10.1145/2541012.2541014)
  * "A “reduce and solve” approach for the multiple-choice multidimensional knapsack problem" (Chen et Hao, 2014) [DOI](https://doi.org/10.1016/j.ejor.2014.05.025)
  * "Lagrangian heuristic-based neighbourhood search for the multiple-choice multi-dimensional knapsack problem" (Hifi et al., 2015) [DOI](https://doi.org/10.1080/0305215X.2014.982631)
  * "A set partitioning reformulation for the multiple-choice multidimensional knapsack problem" (Voß et Lalla-Ruiz, 2015) [DOI](https://doi.org/10.1080/0305215X.2015.1062094)
  * "A Core-Based Exact Algorithm for the Multidimensional Multiple Choice Knapsack Problem" (Mansini et Zanotti, 2020) [DOI](https://doi.org/10.1287/ijoc.2019.0909) 
  * "A two-phase kernel search variant for the multidimensional multiple-choice knapsack problem" (Lamanna et al., 2021) [DOI](https://doi.org/10.1016/j.ejor.2021.05.007)

</p>
</details>

* Data: [multidimensionalmultiplechoiceknapsack.7z](https://github.com/fontanf/orproblems/releases/download/data/multidimensionalmultiplechoiceknapsack.7z)
* Algorithms: [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver/blob/master/examples/multidimensionalmultiplechoiceknapsack.hpp)

[Quadratic Assignment Problem](orproblems/quadraticassignment.hpp)

<details><summary>Literature</summary>
<p>

* Literature:
  * "Iterated local search for the quadratic assignment problem" (Stützle, 2006) [DOI](https://doi.org/10.1016/j.ejor.2005.01.066)
  * "A survey for the quadratic assignment problem" (Loiola et al., 2007) [DOI](https://doi.org/10.1016/j.ejor.2005.09.032)
  * "A branch-and-cut algorithm for quadratic assignment problems based on linearizations" (Erdoğan et Tansel, 2007) [DOI](https://doi.org/10.1016/j.cor.2005.05.027)
  * "Extensive experiments with hybrid genetic algorithms for the solution of the quadratic assignment problem" (Drezner, 2008) [DOI](https://doi.org/10.1016/j.cor.2006.05.004)
  * "A cooperative parallel tabu search algorithm for the quadratic assignment problem" (James et al., 2009) [DOI](https://doi.org/10.1016/j.ejor.2007.06.061)
  * "Multistart Tabu Search and Diversification Strategies for the Quadratic Assignment Problem" (James et al., 2009) [DOI](https://doi.org/10.1109/TSMCA.2009.2014556)
  * "An ejection chain algorithm for the quadratic assignment problem" (Rego et al., 2009) [DOI](https://doi.org/10.1002/net.20360)
  * "Breakout local search for the quadratic assignment problem" (Benlic et Hao, 2013) [DOI](https://doi.org/10.1016/j.amc.2012.10.106)
  * "Memetic search for the quadratic assignment problem" (Benlic et Hao, 2015) [DOI](https://doi.org/10.1016/j.eswa.2014.08.011)

</p>
</details>

* Data: [quadraticassignment.7z](https://github.com/fontanf/orproblems/releases/download/data/quadraticassignment.7z)
* Algorithms: [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver/blob/master/examples/quadraticassignment.hpp)

[Cutting Stock Problem](orproblems/cuttingstock.hpp)
* Literature: TODO
* Data: [cuttingstock.7z](https://github.com/fontanf/orproblems/releases/download/data/cuttingstock.7z)
* Algorithms: [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver/blob/master/examples/cuttingstock.hpp)

[Multiple Knapsack Problem](orproblems/multipleknapsack.hpp)
* Literature: TODO
* Data: [multipleknapsack.7z](https://github.com/fontanf/orproblems/releases/download/data/multipleknapsack.7z)
* Algorithms: [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver/blob/master/examples/multipleknapsack.hpp)

[Bin Packing Problem with Conflicts](orproblems/binpackingwithconflicts.hpp)
* Literature:
  * "Algorithms for the Bin Packing Problem with Conflicts" (Muritiba et al., 2010) [DOI](https://doi.org/10.1287/ijoc.1090.0355)
  * "A Branch-and-Price Algorithm for the Bin Packing Problem with Conflicts" (Elhedhli et al., 2010) [DOI](https://doi.org/10.1287/ijoc.1100.0406)
  * "Bin Packing with Conflicts: A Generic Branch-and-Price Algorithm" (Sadykov et Vanderbeck, 2012) [DOI](https://doi.org/10.1287/ijoc.1120.0499)
  * "Bin packing and related problems: General arc-flow formulation with graph compression" (Brandão et Pedroso, 2016) [DOI](https://doi.org/10.1016/j.cor.2015.11.009)
  * "A New Branch-and-Price-and-Cut Algorithm for One-Dimensional Bin-Packing Problems" (Wei et al., 2019) [DOI](https://doi.org/10.1287/ijoc.2018.0867)
* Data: [binpackingwithconflicts.7z](https://github.com/fontanf/orproblems/releases/download/data/binpackingwithconflicts.7z)
* Algorithms: [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver/blob/master/examples/binpackingwithconflicts.hpp)

## Routing

[Travelling Salesman Problem](orproblems/travellingsalesman.hpp)
* Three field classification: `1 | sᵢⱼ | Cₘₐₓ`
* Literature: TODO
* Data: [travellingsalesman.7z](https://github.com/fontanf/orproblems/releases/download/data/travellingsalesman.7z)
* Algorithms: [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver/blob/master/examples/travellingsalesman.hpp), [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/travellingsalesman.hpp)

[Sequential Ordering Problem](orproblems/sequentialordering.hpp)
* Three field classification: `1 | sᵢⱼ, prec | Cₘₐₓ`
* Literature:
  * "A hybrid particle swarm optimization approach for the sequential ordering problem" (Anghinolfi et al., 2011) [DOI](https://doi.org/10.1016/j.cor.2010.10.014)
  * "A bee colony optimization with automated parameter tuning for sequential ordering problem" (Wun et al., 2014) [DOI](https://doi.org/10.1109/WICT.2014.7077286)
  * "An improved Ant Colony System for the Sequential Ordering Problem" (Skinderowicz, 2017) [DOI](https://doi.org/10.1016/j.cor.2017.04.012)
  * "An extension of the Lin-Kernighan-Helsgaun TSP solver for constrained traveling salesman and vehicle routing problems" (Helsgaun, 2017)
  * "Tree search algorithms for the Sequential Ordering Problem" (Libralesso et al., 2019)
* Data: [sequentialordering.7z](https://github.com/fontanf/orproblems/releases/download/data/sequentialordering.7z)
* Algorithms: [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/sequentialordering.hpp)

[Travelling Repairman Problem / Minimum Latency Problem](orproblems/travellingrepairman.hpp)
* Three field classification: `1 | sᵢⱼ | ∑Cⱼ`
* Literature
  * "Efficient GRASP+VND and GRASP+VNS metaheuristics for the traveling repairman problem" (Salehipour et al., 2011) [DOI](https://doi.org/10.1007/s10288-011-0153-0)
  * "A simple and effective metaheuristic for the Minimum Latency Problem" (Silva et al., 2012) [DOI](https://doi.org/10.1016/j.ejor.2012.03.044)
* Data: [travellingrepairman.7z](https://github.com/fontanf/orproblems/releases/download/data/travellingrepairman.7z)

[Thief Orienteering Problem](orproblems/thieforienteering.hpp)
* Description:
  * Determine a subset of items to collect
  * Maximize the profit of collected items
  * Each item is in a location, a location may contain multiple items
  * Each collected item decreases the speed of the traveller
  * Time limit and capacity constraint
* Literature:
  * "The Thief Orienteering Problem: Formulation and Heuristic Approaches" (Santos et Chagas, 2018) [DOI](https://doi.org/10.1109/CEC.2018.8477853)
  * "Ants can orienteer a thief in their robbery" (Chagas et Wagner, 2020) [DOI](https://doi.org/10.1016/j.orl.2020.08.011)
* Data: [thieforienteering.7z](https://github.com/fontanf/orproblems/releases/download/data/thieforienteering.7z)
* Algorithms: [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/thieforienteering.hpp)

[Capacitated Vehicle Routing Problem](orproblems/capacitatedvehiclerouting.hpp)
* Literature: TODO
* Data: [capacitatedvehiclerouting.7z](https://github.com/fontanf/orproblems/releases/download/data/capacitatedvehiclerouting.7z)
* Algorithms: [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver/blob/master/examples/capacitatedvehiclerouting.hpp)

[Vehicle Routing Problem with Time Windows](orproblems/vehicleroutingwithtimewindows.hpp)
* Time windows / Capacity constraint / Maximum number of vehicles
* Literature: TODO
* Data: [vehicleroutingwithtimewindows.7z](https://github.com/fontanf/orproblems/releases/download/data/vehicleroutingwithtimewindows.7z)
* Algorithms: [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver/blob/master/examples/vehicleroutingwithtimewindows.hpp)

[Capacitated Open Vehicle Routing Problem](orproblems/capacitatedopenvehiclerouting.hpp)
* No need to return to the depot / Capacity constraint / Maximum route length / Maximum number of vehicles
* Literature:
  * "A hybrid evolution strategy for the open vehicle routing problem" (Repoussis et al., 2010) [DOI](https://doi.org/10.1016/j.cor.2008.11.003)
* Data: [capacitatedopenvehiclerouting.7z](https://github.com/fontanf/orproblems/releases/download/data/capacitatedopenvehiclerouting.7z)
* Algorithms: [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver/blob/master/examples/capacitatedopenvehiclerouting.hpp)

## Scheduling

### Single machine scheduling

[Single machine scheduling problem with sequence-dependent setup times, Total weighted tardiness](orproblems/schedulingwithsdsttwt.hpp)
* Three field classification: `1 | sᵢⱼ | ∑wⱼTⱼ`

<details><summary>Literature</summary>
<p>

* Literature:
  * "Real-time scheduling of an automated manufacturing center" (Raman, 1989) [DOI](https://doi.org/10.1016/0377-2217(89)90332-9)
  * "A heuristic to minimize the total weighted tardiness with sequence-dependent setups" (Lee et al., 1997) [DOI](https://doi.org/10.1080/07408179708966311)
  * "Enhancing Stochastic Search Performance by Value-Biased Randomization of Heuristics" (Cicirello et Smith, 2005) [DOI](https://doi.org/10.1007/s10732-005-6997-8)
  * "Non-wrapping order crossover: an order preserving crossover operator that respects absolute position" (Cicirello, 2006) [DOI](https://doi.org/10.1145/1143997.1144177)
  * "An ant colony optimization for single-machine tardiness scheduling with sequence-dependent setups" (Liao et Juan, 2007) [DOI](https://doi.org/10.1016/j.cor.2005.07.020)
  * "Solving single-machine total weighted tardiness problems with sequence-dependent setup times by meta-heuristics" (Lin et Ying, 2007) [DOI](https://doi.org/10.1007/s00170-006-0693-1)
  * "Beam search algorithms for the single machine total weighted tardiness scheduling problem with sequence-dependent setups" (Valente et Alves, 2008) [DOI](https://doi.org/10.1016/j.cor.2006.11.004)
  * "A new discrete particle swarm optimization approach for the single-machine total weighted tardiness scheduling problem with sequence-dependent setup times" (Anghinolfi et Paolucci, 2009) [DOI](https://doi.org/10.1016/j.ejor.2007.10.044)
  * "A discrete differential evolution algorithm for the single machine total weighted tardiness problem with sequence dependent setup times" (Tasgetiren et al., 2009) [DOI](https://doi.org/10.1016/j.cor.2008.06.007)
  * "Parallel path relinking method for the single machine total weighted tardiness problem with sequence-dependent setups" (Bożejko, 2010) [DOI](https://doi.org/10.1007/s10845-009-0253-2)
  * "A variable neighborhood search for minimizing total weighted tardiness with sequence dependent setup times on a single machine" (Kirlik et Oguz, 2012) [DOI](https://doi.org/10.1016/j.cor.2011.08.022)
  * "A discrete electromagnetism-like mechanism for single machine total weighted tardiness problem with sequence-dependent setup times" (Chao et Liao, 2012) [DOI](https://www.sciencedirect.com/science/article/abs/pii/S1568494612002530)
  * "Neighborhood search procedures for single machine tardiness scheduling with sequence-dependent setups" (Liao et al., 2012) [DOI](https://doi.org/10.1016/j.tcs.2012.01.043)
  * "A hybrid genetic algorithm for the single machine scheduling problem with sequence-dependent setup times" (Sioud et al., 2012) [DOI](https://doi.org/10.1016/j.cor.2011.12.017)
  * "An exact algorithm for the single-machine total weighted tardiness problem with sequence-dependent setup times" (Tanaka et Araki, 2013) [DOI](https://doi.org/10.1016/j.cor.2012.07.004)
  * "Iterated Local Search for single-machine scheduling with sequence-dependent setup times to minimize total weighted tardiness" (Xu et al., 2014) [DOI](https://doi.org/10.1007/s10951-013-0351-z)
  * "A study of hybrid evolutionary algorithms for single machine scheduling problem with sequence-dependent setup times" (Xu et al., 2014) [DOI](https://doi.org/10.1016/j.cor.2014.04.009)
  * "An Iterated Local Search heuristic for the single machine total weighted tardiness scheduling problem with sequence-dependent setup times" (Subramanian et al., 2014) [DOI](https://doi.org/10.1080/00207543.2014.883472)
  * "An iterated greedy algorithm for the single-machine total weighted tardiness problem with sequence-dependent setup times" (Deng et Gu, 2014) [DOI](https://doi.org/10.1080/00207721.2012.723054)
  * "An improved scatter search algorithm for the single machine total weighted tardiness scheduling problem with sequence-dependent setup times" (Guo et Tang, 2015) [DOI](https://doi.org/10.1016/j.asoc.2014.12.030)
  * "Efficient local search limitation strategy for single machine total weighted tardiness scheduling with sequence-dependent setup times" (Subramanian et Farias., 2017) [DOI](https://doi.org/10.1016/j.cor.2016.10.008)

</p>
</details>

* Data: [travellingsalesman.7z](https://github.com/fontanf/orproblems/releases/download/data/schedulingwithsdsttwt.7z)
* Algorithms: [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver/blob/master/examples/schedulingwithsdsttwt.hpp), [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/schedulingwithsdsttwt.hpp)

[Single machine order acceptance and scheduling problem with time windows and sequence-dependent setup times, Total weighted tardiness](orproblems/orderacceptanceandscheduling.hpp)
* Three field classification: `1 | rⱼ, sᵢⱼ, reject, đⱼ | ∑wⱼTⱼ - ∑vⱼ`
* Literature:
  * "A tabu search algorithm for order acceptance and scheduling" (Cesaret et al., 2012) [DOI](https://doi.org/10.1016/j.cor.2010.09.018)
  * "Hybrid evolutionary approaches for the single machine order acceptance and scheduling problem" (Chaurasia et Singh, 2017) [DOI](https://doi.org/10.1016/j.asoc.2016.09.051)
  * "Exact and heuristic algorithms for order acceptance and scheduling with sequence-dependent setup times" (Silva et al., 2018) [DOI](https://doi.org/10.1016/j.cor.2017.09.006)
  * "Tabu-Based Large Neighbourhood Search for Time/Sequence-Dependent Scheduling Problems with Time Windows" (He et al., 2019)
  * "Single-machine scheduling with release times, deadlines, setup times, and rejection" (de Weerdt et al., 2020) [DOI](https://doi.org/10.1016/j.ejor.2020.09.042)
* Data: [orderacceptanceandscheduling.7z](https://github.com/fontanf/orproblems/releases/download/data/orderacceptanceandscheduling.7z)
* Algorithms: [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/orderacceptanceandscheduling.hpp)

[Single machine batch scheduling problem, Total weighted tardiness](orproblems/batchschedulingtotalweightedtardiness.hpp)
* Three field classification: `1 | batch, rⱼ, sⱼ, compt | ∑wⱼTⱼ`
* Literature:
  * "Scheduling a batch processing machine to minimize total weighted tardiness" (Chou et Wang, 2008)
  * "Minimizing total weighted tardiness on a batch-processing machine with non-agreeable release times and due dates" (Mathirajan et al., 2010) [DOI](https://doi.org/10.1007/s00170-009-2342-y)
  * "Solving single batch-processing machine problems using an iterated heuristic" (Wang, 2011) [DOI](https://doi.org/10.1080/00207543.2010.518995)
  * "Iterated local search for single machine total weighted tardiness batch scheduling" (Queiroga et al., 2020) [DOI](https://doi.org/10.1007/s10732-020-09461-x)
* Data: [batchschedulingtotalweightedtardiness.7z](https://github.com/fontanf/orproblems/releases/download/data/batchschedulingtotalweightedtardiness.7z)
* Algorithms: [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/batchschedulingtotalweightedtardiness.hpp)

### (Unrelated) parallel machine scheduling

[Identical parallel machine scheduling problem with family setup times, Total weighted completion time](orproblems/parallelschedulingwithfamilysetuptimestwct.hpp)
* Three field classification: `P | sᵢ | ∑wⱼCⱼ`
* Literature:
  * "Heuristic methods for the identical parallel machine flowtime problem with set-up times" (Dunstall et Wirth, 2005) [DOI](https://doi.org/10.1016/j.cor.2004.03.013)
  * "An improved heuristic for parallel machine weighted flowtime scheduling with family set-up times" (Liao et al., 2012) [DOI](https://doi.org/10.1016/j.camwa.2011.10.077)
  * "Mathematical formulations for scheduling jobs on identical parallel machines with family setup times and total weighted completion time minimization" (Kramer et al., 2021) [DOI](https://doi.org/10.1016/j.ejor.2019.07.006)
* Data: [parallelschedulingwithfamilysetuptimestwct.7z](https://github.com/fontanf/orproblems/releases/download/data/parallelschedulingwithfamilysetuptimestwct.7z)
* Algorithms: [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver/blob/master/examples/parallelschedulingwithfamilysetuptimestwct.hpp)

[Star Observation Scheduling Problem](orproblems/starobservationscheduling.hpp)
* Three field classification: `R | rⱼᵢ, 2 pⱼᵢ ≥ dⱼᵢ - rⱼᵢ | ∑wⱼUⱼ`
* Literature:
  * "A Branch-And-Price Algorithm for Scheduling Observations on a Telescope" (Catusse et al., 2016)
* Data: [starobservationscheduling.7z](https://github.com/fontanf/orproblems/releases/download/data/starobservationscheduling.7z)
* Algorithms: [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver/blob/master/examples/starobservationscheduling.hpp)

### Flow shop scheduling

[Permutation flow shop scheduling problem, Makespan](orproblems/permutationflowshopschedulingmakespan.hpp)
* Three field classification: `Fm | prmu | Cₘₐₓ`
* Literature:
  * "An Effective Hybrid Heuristic for Flow Shop Scheduling" (Zheng et Wang, 2003) [DOI](https://doi.org/10.1007/s001700300005)
  * "A simple and effective iterated greedy algorithm for the permutation flowshop scheduling problem" (Ruiz et Stützle, 2007) [DOI](https://doi.org/10.1016/j.ejor.2005.12.009)
  * "Cooperative metaheuristics for the permutation flowshop scheduling problem" (Vallada et Ruiz, 2009) [DOI](https://doi.org/10.1016/j.ejor.2007.11.049)
  * "A Variable Block Insertion Heuristic for Solving Permutation Flow Shop Scheduling Problem with Makespan Criterion" (Kizilay et al., 2019) [DOI](https://doi.org/10.3390/a12050100)
  * "A best-of-breed iterated greedy for the permutation flowshop scheduling problem with makespan objective" (Fernandez-Viagas, Framinan, 2019) [DOI](https://doi.org/10.1016/j.cor.2019.104767)
  * "A memetic algorithm with novel semi-constructive evolution operators for permutation flowshop scheduling problem" (Kurdi, 2020) [DOI](https://doi.org/10.1016/j.asoc.2020.106458)
  * "Iterative beam search algorithms for the permutation flowshop" (Libralesso et al., 2020)
* Data: [permutationflowshopscheduling.7z](https://github.com/fontanf/orproblems/releases/download/data/permutationflowshopscheduling.7z)
* Algorithms: [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver/blob/master/examples/permutationflowshopschedulingmakespan.hpp), [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/permutationflowshopschedulingmakespan.hpp)

[Permutation flow shop scheduling problem, Total completion time](orproblems/permutationflowshopschedulingtct.hpp)
* Three field classification: `Fm | prmu | ∑Cⱼ`
* Literature:
  * "Constructive and composite heuristic solutions to the P//∑Ci scheduling problem" (Liu et Reeves, 2001) [DOI](https://doi.org/10.1016/S0377-2217(00)00137-5)
  * "Local search methods for the flowshop scheduling problem with flowtime minimization" (Pan et Ruiz, 2012) [DOI](https://doi.org/10.1016/j.ejor.2012.04.034)
  * "A new set of high-performing heuristics to minimise flowtime in permutation flowshops" (Fernandez-Viagas et Framinan, 2015) [DOI](https://doi.org/10.1016/j.cor.2014.08.004)
  * "A beam-search-based constructive heuristic for the PFSP to minimise total flowtime" (Fernandez-Viagas et Framinan, 2017) [DOI](https://doi.org/10.1016/j.cor.2016.12.020)
  * "Minimizing flowtime in a flowshop scheduling problem with a biased random-key genetic algorithm" (Andrade et al., 2019) [DOI](https://doi.org/10.1016/j.eswa.2019.03.007)
  * "Iterative beam search algorithms for the permutation flowshop" (Libralesso et al., 2020)
* Data: [permutationflowshopscheduling.7z](https://github.com/fontanf/orproblems/releases/download/data/permutationflowshopscheduling.7z)
* Algorithms: [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/permutationflowshopschedulingtct.hpp)

[Permutation flow shop scheduling problem, Total tardiness](orproblems/permutationflowshopschedulingtt.hpp)
* Three field classification: `Fm | prmu | ∑Tⱼ`
* Literature:
  * "Minimising total tardiness in the m-machine flowshop problem: A review and evaluation of heuristics and metaheuristics"  (Vallada et al., 2008) [DOI](https://doi.org/10.1016/j.cor.2006.08.016)
  * "Cooperative metaheuristics for the permutation flowshop scheduling problem" (Vallada et Ruiz, 2009) [DOI](https://doi.org/10.1016/j.ejor.2007.11.049)
  * "Genetic algorithms with path relinking for the minimum tardiness permutation flowshop problem" (Vallada et Ruiz, 2010) [DOI](https://doi.org/10.1016/j.omega.2009.04.002)
  * "NEH-based heuristics for the permutation flowshop scheduling problem to minimise total tardiness" (Fernandez-Viagas et Framinan, 2015) [DOI](https://doi.org/10.1016/j.cor.2015.02.002)
  * "Matheuristic algorithms for minimizing total tardiness in the m-machine flow-shop scheduling problem" (Ta et al., 2015) [DOI](https://doi.org/10.1007/s10845-015-1046-4)
  * "Iterated-greedy-based algorithms with beam search initialization for the permutation flowshop to minimise total tardiness" (Fernandez-Viagas et al., 2018) [DOI](https://doi.org/10.1016/j.eswa.2017.10.050)
* Data: [permutationflowshopscheduling.7z](https://github.com/fontanf/orproblems/releases/download/data/permutationflowshopscheduling.7z)
* Algorithms: [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver/blob/master/examples/permutationflowshopschedulingtt.hpp), [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/permutationflowshopschedulingtt.hpp)

### Assembly Line Balancing

[Simple Assembly Line Balancing Problem of Type 1 (SALBP-1)](orproblems/simpleassemblylinebalancing1.hpp)
* Bin Packing Problem with precedence constraints of the form `bin(j1) <= bin(j2) `
* Literature:
  * "Simple assembly line balancing—Heuristic approaches" (Scholl et Voß, 1997) [DOI](https://doi.org/10.1007/BF00127358)
  * "State-of-the-art exact and heuristic solution procedures for simple assembly line balancing" (Scholl et Becker, 2006) [DOI](https://doi.org/10.1016/j.ejor.2004.07.022)
  * "Beam-ACO for Simple Assembly Line Balancing" (Blum, 2008) [DOI](https://doi.org/10.1287/ijoc.1080.0271)
  * "A Branch, Bound, and Remember Algorithm for the Simple Assembly Line Balancing Problem" (Sewell et Jacobson, 2011) [DOI](https://doi.org/10.1287/ijoc.1110.0462)
  * "An application of the branch, bound, and remember algorithm to a new simple assembly line balancing dataset" (Morrison et al., 2014) [DOI](https://doi.org/10.1016/j.ejor.2013.11.033)
* Data: [simpleassemblylinebalancing1.7z](https://github.com/fontanf/orproblems/releases/download/data/simpleassemblylinebalancing1.7z)
* Algorithms: [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/simpleassemblylinebalancing1.hpp)

[U-shaped Assembly Line Balancing Problem of Type 1 (UALBP-1)](orproblems/ushapedassemblylinebalancing1.hpp)
* Literature
  * "Balancing of U-type assembly systems using simulated annealing" (Erel et al., 2001) [DOI](https://doi.org/10.1080/00207540110051905)
  * "Ant colony optimization for the single model U-type assembly line balancing problem" (Sabuncuoglu et al., 2013) [DOI](https://doi.org/10.1016/j.ijpe.2008.11.017)
  * "New MILP model and station-oriented ant colony optimization algorithm for balancing U-type assembly lines" (Li et al., 2017) [DOI](https://doi.org/10.1016/j.cie.2017.07.005)
  * "Branch, bound and remember algorithm for U-shaped assembly line balancing problem" (Li et al., 2018) [DOI](https://doi.org/10.1016/j.cie.2018.06.037)
  * "Enhanced beam search heuristic for U-shaped assembly line balancing problems" (Li et al., 2020) [DOI](https://doi.org/10.1080/0305215X.2020.1741569)
* Data: [simpleassemblylinebalancing1.7z](https://github.com/fontanf/orproblems/releases/download/data/simpleassemblylinebalancing1.7z)
* Algorithms: [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/ushapedassemblylinebalancing1.hpp)

### Resource constrained scheduling

[ROADEF/EURO Challenge 2020: Maintenance Planning Problem](orproblems/roadef2020.hpp)
* Website: https://www.roadef.org/challenge/2020/en/
* Data: [roadef2020.7z](https://github.com/fontanf/orproblems/releases/download/data/roadef2020.7z)
* Algorithms: [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver/blob/master/examples/roadef2020.hpp)

