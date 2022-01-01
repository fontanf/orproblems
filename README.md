# Operations Research Problems

Data, C++ parsers and solution checkers for various Operations Research problems.

These are the problems used as examples for [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver), [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver) and [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver).

The data also include CSV files listing the instances for each problem and their best known bounds which can be used with the benchmark scripts from [fontanf/optimizationtools](https://github.com/fontanf/optimizationtools).

## Packing

[Knapsack Problem with Conflicts / Disjunctively Constrained Knapsack Problem](orproblems/knapsackwithconflicts.hpp)

<details><summary>Literature</summary>
<p>

* Literature:
  * "Heuristic and exact algorithms for the disjunctively constrained knapsack problem" (Yamada et al., 2002)
  * "A reactive local search-based algorithm for the disjunctively constrained knapsack problem" ()Hifi et Michrafy, 2006) [DOI](https://doi.org/10.1057/palgrave.jors.2602046)
  * "Reduction strategies and exact algorithms for the disjunctively constrained knapsack problem" (Hifi et Michrafy, 2007) [DOI](https://doi.org/10.1016/j.cor.2005.10.004)
  * "Local branching-based algorithms for the disjunctively constrained knapsack problem" (Akeb et al., 2011) [DOI](https://doi.org/10.1016/j.cie.2011.01.019)
  * "An algorithm for the disjunctively constrained knapsack problem" (Hifi et Otmani, 2012) [DOI](https://doi.org/10.1504/IJOR.2012.044026)
  * "Bin Packing with Conflicts: A Generic Branch-and-Price Algorithm" (Sadykov et Vanderbeck, 2012) [DOI](https://doi.org/10.1287/ijoc.1120.0499)
  * "An iterative rounding search-based algorithm for the disjunctively constrained knapsack problem" (Hifi, 2014) [DOI](https://doi.org/10.1080/0305215X.2013.819096)
  * "Design and evaluation of a parallel neighbor algorithm for the disjunctively constrained knapsack problem" (Quan et Wu, 2016) [DOI](https://doi.org/10.1002/cpe.3848)
  * "Cooperative parallel adaptive neighbourhood search for the disjunctively constrained knapsack problem" (Quan et Wu, 2017) [DOI](https://doi.org/10.1080/0305215X.2016.1257854)
  * "Probabilistic Tabu search with multiple neighborhoods for the Disjunctively Constrained Knapsack Problem" (Salem et al., 2017) [DOI](https://doi.org/10.1051/ro/2016049)
  * "A Branch-and-Bound Algorithm for the Knapsack Problem with Conflict Graph" (Bettinelli et al., 2017) [DOI](https://doi.org/10.1287/ijoc.2016.0742)
  * "Optimization algorithms for the disjunctively constrained knapsack problem" (Salem et al., 2018) [DOI](https://doi.org/10.1007/s00500-016-2465-7)
  * "A new combinatorial branch-and-bound algorithm for the Knapsack Problem with Conflicts" (Coniglio et al., 2020) [DOI](https://doi.org/10.1016/j.ejor.2020.07.023)
  * "A threshold search based memetic algorithm for the disjunctively constrained knapsack problem" (Wei et Hao, 2021) [DOI](https://doi.org/10.1016/j.cor.2021.105447)

</p>
</details>

* Data: [knapsackwithconflicts.7z](https://github.com/fontanf/orproblems/releases/download/data/knapsackwithconflicts.7z)
* Algorithms: [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver/blob/master/examples/knapsackwithconflicts.hpp), [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/knapsackwithconflicts.hpp)

[Multidimensional Multiple-choice Knapsack Problem](orproblems/multidimensionalmultiplechoiceknapsack.hpp)

<details><summary>Literature</summary>
<p>

* Literature:
  * "Heuristic algorithms for the multiple-choice multidimensional knapsack problem" (Hifi et al., 2004) [DOI](https://doi.org/10.1057/palgrave.jors.2601796)
  * "A Reactive Local Search-Based Algorithm for the Multiple-Choice Multi-Dimensional Knapsack Problem" (Hifi et al., 2005) [DOI](https://doi.org/10.1007/s10589-005-3057-0)
  * "A column generation method for the multiple-choice multi-dimensional knapsack problem" (Cherfi et Hifi, 2010) [DOI](https://doi.org/10.1007/s10589-008-9184-7)
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

<details><summary>Literature</summary>
<p>

* Literature:
  * "A Linear Programming Approach to the Cutting-Stock Problem" (Gilmore et Gomory, 1961) [DOI](https://doi.org/10.1287/opre.9.6.849)
  * "A branch-and-cut-and-price algorithm for one-dimensional stock cutting and two-dimensional two-stage cutting" (Belov et Scheithauer, 2006) [DOI](https://doi.org/10.1016/j.ejor.2004.08.036)
  * "Bin packing and related problems: General arc-flow formulation with graph compression" (Brandão et Pedroso, 2016) [DOI](https://doi.org/10.1016/j.cor.2015.11.009)
  * "Bin packing and cutting stock problems: Mathematical models and exact algorithms" (Delorme et al., 2016) [DOI](https://doi.org/10.1016/j.ejor.2016.04.030)
  * "Enhanced Pseudo-polynomial Formulations for Bin Packing and Cutting Stock Problems" (Delorme et Iori, 2019) [DOI](https://doi.org/10.1287/ijoc.2018.0880)
  * "A New Branch-and-Price-and-Cut Algorithm for One-Dimensional Bin-Packing Problems" (Wei et al., 2019) [DOI](https://doi.org/10.1287/ijoc.2018.0867)

</p>
</details>

* Data: [cuttingstock.7z](https://github.com/fontanf/orproblems/releases/download/data/cuttingstock.7z)
* Algorithms: [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver/blob/master/examples/cuttingstock.hpp)

[Multiple Knapsack Problem](orproblems/multipleknapsack.hpp)

<details><summary>Literature</summary>
<p>

* Literature:
  * "An Algorithm for the Solution of 0-1 Loading Problems" (Ingargiola et Korsh, 1975) [DOI](https://doi.org/10.1287/opre.23.6.1110)
  * "An algorithm for 0-1 multiple-knapsack problems" (Hung et Fisk, 1978) [DOI](https://doi.org/10.1002/nav.3800250316)
  * "Solution of the zero-one multiple knapsack problem" (Martello et Toth, 1980) [DOI](https://doi.org/10.1016/0377-2217(80)90112-5)
  * "A Bound and Bound algorithm for the zero-one multiple knapsack problem" (Martello et Toth, 1981) [DOI](https://doi.org/10.1016/0166-218X(81)90005-6)
  * "Heuristic algorithms for the multiple knapsack problem" (Martello et Toth, 1981) [DOI](https://doi.org/10.1007/BF02243544)
  * "An exact algorithm for large multiple knapsack problems" (Pisinger, 1999) [DOI](https://doi.org/10.1016/S0377-2217(98)00120-9)
  * "Bin Completion Algorithms for Multicontainer Packing, Knapsack, and Covering Problems" (Fukunaga et Korf, 2007) [DOI](https://doi.org/10.1613/jair.2106)
  * "A new grouping genetic algorithm for the Multiple Knapsack Problem" (Fukunaga, 2008) [DOI](https://doi.org/10.1109/CEC.2008.4631094)
  * "Combining multiple representations in a genetic algorithm for the multiple knapsack problem" (Fukunaga et Tazoe, 2009) [DOI](https://doi.org/10.1109/CEC.2009.4983244)
  * "A branch-and-bound algorithm for hard multiple knapsack problems" (Fukunaga, 2011) [DOI](https://doi.org/10.1007/s10479-009-0660-y)
  * "A procedure-based heuristic for 0-1 Multiple Knapsack Problems" (Lalami et al., 2012) [DOI](https://doi.org/10.1504/IJMOR.2012.046684)
  * "Improved Swap Heuristic for the Multiple Knapsack Problem" (Laalaoui, 2013) [DOI](https://doi.org/10.1007/978-3-642-38679-4_55)
  * "A binary multiple knapsack model for single machine scheduling with machine unavailability" (Laalaouia et M’Hallah, 2016) [DOI](https://doi.org/10.1016/j.cor.2016.02.005)
  * "Mathematical models and decomposition methods for the multiple knapsack problem" (Dell’Amico et al., 2019) [DOI](https://doi.org/10.1016/j.ejor.2018.10.043)

</p>
</details>

* Data: [multipleknapsack.7z](https://github.com/fontanf/orproblems/releases/download/data/multipleknapsack.7z)
* Algorithms: [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver/blob/master/examples/multipleknapsack.hpp)

[Quadratic Multiple Knapsack Problem](orproblems/quadraticmultipleknapsack.hpp)

<details><summary>Literature</summary>
<p>

* Literature:
  * "The quadratic multiple knapsack problem and three heuristic approaches to it" (Hiley et Julstrom, 2006) [DOI](https://doi.org/10.1145/1143997.1144096)
  * "A Genetic Algorithm for the Quadratic Multiple Knapsack Problem" (Sara et Sipahioglu, 2007) [DOI](https://doi.org/10.1007/978-3-540-75555-5_47)
  * "A New Grouping Genetic Algorithm for the Quadratic Multiple Knapsack Problem" (Singh et Baghel, 2007) [DOI](https://doi.org/10.1007/978-3-540-71615-0_19)
  * "A Swarm Intelligence Approach to the Quadratic Multiple Knapsack Problem" (Sundar et Singh, 2010) [DOI](https://doi.org/10.1007/978-3-642-17537-4_76)
  * "Strategic oscillation for the quadratic multiple knapsack problem" (García-Martínez et al., 2013) [DOI](https://doi.org/10.1007/s10589-013-9623-y)
  * "Tabu-enhanced iterated greedy algorithm: A case study in the quadratic multiple knapsack problem" (García-Martínez et al., 2014) [DOI](https://doi.org/10.1016/j.ejor.2013.07.035)
  * "Iterated responsive threshold search for the quadratic multiple knapsack problem" (Chen et Hao, 2015) [DOI](https://doi.org/10.1007/s10479-014-1720-5)
  * "An evolutionary path relinking approach for the quadratic multiple knapsack problem" (Chen et al., 2016) [DOI](https://doi.org/10.1016/j.knosys.2015.10.004)
  * "Hybridization of tabu search with feasible and infeasible local searches for the quadratic multiple knapsack problem" (Qin et al., 2016) [DOI](https://doi.org/10.1016/j.cor.2015.08.002)
  * "An ejection chain approach for the quadratic multiple knapsack problem" (Peng et al., 2016) [DOI](https://doi.org/10.1016/j.ejor.2016.02.043)
  * "An Exact Algorithm for the Quadratic Multiknapsack Problem with an Application to Event Seating" (Bergman, 2019) [DOI](https://doi.org/10.1287/ijoc.2018.0840)
  * "Branch and solve strategies-based algorithm for the quadratic multiple knapsack problem" (Aïder et al., 2020) [DOI](https://doi.org/10.1080/01605682.2020.1843982)
  * "A branch-and-bound algorithm for the quadratic multiple knapsack problem" (Fleszar, 2021) [DOI](https://doi.org/10.1016/j.ejor.2021.06.018)
  * "Polynomial-size formulations and relaxations for the quadratic multiple knapsack problem" (Galli et al., 2021) [DOI](https://doi.org/10.1016/j.ejor.2020.10.047)

</p>
</details>

* Data: [quadraticmultipleknapsack.7z](https://github.com/fontanf/orproblems/releases/download/data/quadraticmultipleknapsack.7z)

<!--
[Generalized Quadratic Multiple Knapsack Problem](orproblems/generalizedquadraticmultipleknapsack.hpp)

<details><summary>Literature</summary>
<p>

* Literature:
  * "Generalized quadratic multiple knapsack problem and two solution approaches" (Saraç et Sipahioglu, 2014) [DOI](https://doi.org/10.1016/j.cor.2013.08.018)
  * "Memetic Search for the Generalized Quadratic Multiple Knapsack Problem" (Chen et Hao, 2016) [DOI](https://doi.org/10.1109/TEVC.2016.2546340)
  * "A multi-start iterated local search algorithm for the generalized quadratic multiple knapsack problem" (Avci et Topaloglu, 2017) [DOI](https://doi.org/10.1016/j.cor.2017.02.004)
  * "A matheuristic for the 0–1 generalized quadratic multiple knapsack problem" (Adouani et al., 2019) [DOI](https://doi.org/10.1007/s11590-019-01503-z)
  * "A hybrid evolutionary search for the generalized quadratic multiple knapsack problem" (Zhou et al., 2022) [DOI](https://doi.org/10.1016/j.ejor.2021.04.001)

</p>
</details>


* Data: [generalizedquadraticmultipleknapsack.7z](https://github.com/fontanf/generalizedorproblems/releases/download/data/quadraticmultipleknapsack.7z)
-->

[Bin Packing Problem with Conflicts](orproblems/binpackingwithconflicts.hpp)

<details><summary>Literature</summary>
<p>

* Literature:
  * "Algorithms for the Bin Packing Problem with Conflicts" (Muritiba et al., 2010) [DOI](https://doi.org/10.1287/ijoc.1090.0355)
  * "A Branch-and-Price Algorithm for the Bin Packing Problem with Conflicts" (Elhedhli et al., 2010) [DOI](https://doi.org/10.1287/ijoc.1100.0406)
  * "Bin Packing with Conflicts: A Generic Branch-and-Price Algorithm" (Sadykov et Vanderbeck, 2012) [DOI](https://doi.org/10.1287/ijoc.1120.0499)
  * "Bin packing and related problems: General arc-flow formulation with graph compression" (Brandão et Pedroso, 2016) [DOI](https://doi.org/10.1016/j.cor.2015.11.009)
  * "A New Branch-and-Price-and-Cut Algorithm for One-Dimensional Bin-Packing Problems" (Wei et al., 2019) [DOI](https://doi.org/10.1287/ijoc.2018.0867)

</p>
</details>

* Data: [binpackingwithconflicts.7z](https://github.com/fontanf/orproblems/releases/download/data/binpackingwithconflicts.7z)
* Algorithms: [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver/blob/master/examples/binpackingwithconflicts.hpp)

## Routing

### Single vehicle

[Travelling Salesman Problem](orproblems/travellingsalesman.hpp)
* Three field classification: `1 | sᵢⱼ | Cₘₐₓ`

<details><summary>Literature</summary>
<p>

* Taillard ÉD (2021) A linearithmic Heuristic for the Travelling Salesman Problem. European Journal of Operational Research. https://doi.org/10.1016/j.ejor.2021.05.034
* Taillard ÉD, Helsgaun K (2019) POPMUSIC for the travelling salesman problem. European Journal of Operational Research 272:420–429. https://doi.org/10.1016/j.ejor.2018.06.039
* Osterman C, Rego C (2016) A k-level data structure for large-scale traveling salesman problems. Ann Oper Res 244:583–601. https://doi.org/10.1007/s10479-016-2159-7
* Applegate DL, Bixby RE, Chvátal V, Cook WJ (2011) The Traveling Salesman Problem: A Computational Study. Princeton University Press
* Rego C, Gamboa D, Glover F, Osterman C (2011) Traveling salesman problem heuristics: Leading methods, implementations and latest advances. European Journal of Operational Research 211:427–441. https://doi.org/10.1016/j.ejor.2010.09.010
* Helsgaun K (2009) General k-opt submoves for the Lin–Kernighan TSP heuristic. Math Prog Comp 1:119–163. https://doi.org/10.1007/s12532-009-0004-6
* Merz P, Huhse J (2008) An Iterated Local Search Approach for Finding Provably Good Solutions for Very Large TSP Instances. In: Rudolph G, Jansen T, Beume N, et al. (eds) Parallel Problem Solving from Nature – PPSN X. Springer, Berlin, Heidelberg, pp 929–939, https://doi.org/10.1007/978-3-540-87700-4_92
* Gamboa D, Rego C, Glover F (2006) Implementation analysis of efficient heuristic algorithms for the traveling salesman problem. Computers & Operations Research 33:1154–1172. https://doi.org/10.1016/j.cor.2005.06.014
* Gamboa D, Rego C, Glover F (2005) Data structures and ejection chains for solving large-scale traveling salesman problems. European Journal of Operational Research 160:154–171. https://doi.org/10.1016/j.ejor.2004.04.023
* Applegate D, Cook W, Rohe A (2003) Chained Lin-Kernighan for Large Traveling Salesman Problems. INFORMS Journal on Computing 15:82–92. https://doi.org/10.1287/ijoc.15.1.82.15157
* Helsgaun K (2000) An effective implementation of the Lin–Kernighan traveling salesman heuristic. European Journal of Operational Research 126:106–130. https://doi.org/10.1016/S0377-2217(99)00284-2
* Voudouris C, Tsang E (1999) Guided local search and its application to the traveling salesman problem. European Journal of Operational Research 113:469–499. https://doi.org/10.1016/S0377-2217(98)00099-X
* Potvin J-Y (1996) Genetic algorithms for the traveling salesman problem. Ann Oper Res 63:337–370. https://doi.org/10.1007/BF02125403
* Gendreau M, Hertz A, Laporte G (1992) New Insertion and Postoptimization Procedures for the Traveling Salesman Problem. Operations Research 40:1086–1094. https://doi.org/10.1287/opre.40.6.1086
* Bentley JJ (1992) Fast Algorithms for Geometric Traveling Salesman Problems. ORSA Journal on Computing 4:387–411. https://doi.org/10.1287/ijoc.4.4.387
* Laporte G (1992) The traveling salesman problem: An overview of exact and approximate algorithms. European Journal of Operational Research 59:231–247. https://doi.org/10.1016/0377-2217(92)90138-Y
* Bentley JL (1990) Experiments on traveling salesman heuristics. In: Proceedings of the first annual ACM-SIAM symposium on Discrete algorithms. Society for Industrial and Applied Mathematics, USA, pp 91–99

</p>
</details>

* Data: [travellingsalesman.7z](https://github.com/fontanf/orproblems/releases/download/data/travellingsalesman.7z)
* Algorithms: [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver/blob/master/examples/travellingsalesman.hpp), [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/travellingsalesman.hpp)

[Sequential Ordering Problem](orproblems/sequentialordering.hpp)
* Three field classification: `1 | sᵢⱼ, prec | Cₘₐₓ`

<details><summary>Literature</summary>
<p>

* Jamal J, Shobaki G, Papapanagiotou V, et al (2017) Solving the sequential ordering problem using branch and bound. In: 2017 IEEE Symposium Series on Computational Intelligence (SSCI). pp 1–9, https://doi.org/10.1109/SSCI.2017.8280805
* Skinderowicz R (2017) An improved Ant Colony System for the Sequential Ordering Problem. Computers & Operations Research 86:1–17. https://doi.org/10.1016/j.cor.2017.04.012
* Papapanagiotou V, Jamal J, Montemanni R, et al (2015) A comparison of two exact algorithms for the sequential ordering problem. In: 2015 IEEE Conference on Systems, Process and Control (ICSPC). pp 73–78, https://doi.org/10.1109/SPC.2015.7473562
* Shobaki G, Jamal J (2015) An exact algorithm for the sequential ordering problem and its application to switching energy minimization in compilers. Comput Optim Appl 61:343–372. https://doi.org/10.1007/s10589-015-9725-9
* Skinderowicz R (2015) Population-Based Ant Colony Optimization for Sequential Ordering Problem. In: Núñez M, Nguyen NT, Camacho D, Trawiński B (eds) Computational Collective Intelligence. Springer International Publishing, Cham, pp 99–109, https://doi.org/10.1007/978-3-319-24306-1_10
* Wun MH, Wong L-P, Khader AT, Tan T-P (2014) A bee colony optimization with automated parameter tuning for sequential ordering problem. In: 2014 4th World Congress on Information and Communication Technologies (WICT 2014). pp 314–319, https://doi.org/10.1109/WICT.2014.7077286
* Ezzat A, Abdelbar AM, Wunsch DC (2014) A bare-bones ant colony optimization algorithm that performs competitively on the sequential ordering problem. Memetic Comp 6:19–29. https://doi.org/10.1007/s12293-013-0129-z
* Sung J, Jeong B (2014) An Adaptive Evolutionary Algorithm for Traveling Salesman Problem with Precedence Constraints. The Scientific World Journal 2014:e313767. https://doi.org/10.1155/2014/313767
* Gambardella LM, Montemanni R, Weyland D (2012a) Coupling ant colony systems with strong local searches. European Journal of Operational Research 220:831–843. https://doi.org/10.1016/j.ejor.2012.02.038
* Gambardella LM, Montemanni R, Weyland D (2012b) An Enhanced Ant Colony System for the Sequential Ordering Problem. In: Klatte D, Lüthi H-J, Schmedders K (eds) Operations Research Proceedings 2011. Springer, Berlin, Heidelberg, pp 355–360, https://doi.org/10.1007/978-3-642-29210-1_57
* Anghinolfi D, Montemanni R, Paolucci M, Maria Gambardella L (2011) A hybrid particle swarm optimization approach for the sequential ordering problem. Computers & Operations Research 38:1076–1085. https://doi.org/10.1016/j.cor.2010.10.014
* Montemanni R, Smith DH, Gambardella LM (2008) A heuristic manipulation technique for the sequential ordering problem. Computers & Operations Research 35:3931–3944. https://doi.org/10.1016/j.cor.2007.05.003
* Guerriero F, Mancini M (2003) A cooperative parallel rollout algorithm for the sequential ordering problem. Parallel Computing 29:663–677. https://doi.org/10.1016/S0167-8191(03)00048-6
* Seo D-I, Moon B-R (2003) A Hybrid Genetic Algorithm Based on Complete Graph Representation for the Sequential Ordering Problem. In: Cantú-Paz E, Foster JA, Deb K, et al. (eds) Genetic and Evolutionary Computation — GECCO 2003. Springer, Berlin, Heidelberg, pp 669–680, https://doi.org/10.1007/3-540-45105-6_82
* Moon C, Kim J, Choi G, Seo Y (2002) An efficient genetic algorithm for the traveling salesman problem with precedence constraints. Eur J Oper Res. https://doi.org/10.1016/S0377-2217(01)00227-2
* Ascheuer N, Jünger M, Reinelt G (2000) A Branch & Cut Algorithm for the Asymmetric Traveling Salesman Problem with Precedence Constraints. Computational Optimization and Applications 17:61–84. https://doi.org/10.1023/A:1008779125567
* Gambardella LM, Dorigo M (2000) An Ant Colony System Hybridized with a New Local Search for the Sequential Ordering Problem. INFORMS Journal on Computing 12:237–255. https://doi.org/10.1287/ijoc.12.3.237.12636
* Escudero LF, Guignard M, Malik K (1994) A Lagrangian relax-and-cut approach for the sequential ordering problem with precedence relationships. Ann Oper Res 50:219–237. https://doi.org/10.1007/BF02085641
* Ascheuer N, Escudero LF, Grötschel M, Stoer M (1993) A Cutting Plane Approach to the Sequential Ordering Problem (with Applications to Job Scheduling in Manufacturing). SIAM J Optim 3:25–42. https://doi.org/10.1137/0803002
* Escudero LF (1988) An inexact algorithm for the sequential ordering problem. European Journal of Operational Research 37:236–249. https://doi.org/10.1016/0377-2217(88)90333-5

</p>
</details>

* Data: [sequentialordering.7z](https://github.com/fontanf/orproblems/releases/download/data/sequentialordering.7z)
* Algorithms: [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/sequentialordering.hpp)

[Travelling Repairman Problem / Minimum Latency Problem](orproblems/travellingrepairman.hpp)
* Three field classification: `1 | sᵢⱼ | ∑Cⱼ`

<details><summary>Literature</summary>
<p>

* Santana Í, Plastino A, Rosseti I (2022) Improving a state-of-the-art heuristic for the minimum latency problem with data mining. International Transactions in Operational Research 29:959–986. https://doi.org/10.1111/itor.12774
* Ramadhan F, Imran A (2019) A Two-Phase Metaheuristic Method for Solving Travelling Repairman Problem. In: 2019 International Conference on Sustainable Engineering and Creative Computing (ICSECC). pp 155–159, https://doi.org/10.1109/ICSECC.2019.8907032
* Bulhões T, Sadykov R, Uchoa E (2018) A branch-and-price algorithm for the Minimum Latency Problem. Computers & Operations Research 93:66–78. https://doi.org/10.1016/j.cor.2018.01.016
* Manerba D, Mansini R, Riera-Ledesma J (2017) The Traveling Purchaser Problem and its variants. European Journal of Operational Research 259:1–18. https://doi.org/10.1016/j.ejor.2016.12.017
* Roberti R, Mingozzi A (2013) Dynamic ng-Path Relaxation for the Delivery Man Problem. Transportation Science 48:413–424. https://doi.org/10.1287/trsc.2013.0474
* Angel-Bello F, Alvarez A, García I (2013) Two improved formulations for the minimum latency problem. Applied Mathematical Modelling 37:2257–2266. https://doi.org/10.1016/j.apm.2012.05.026
* Silva MM, Subramanian A, Vidal T, Ochi LS (2012) A simple and effective metaheuristic for the Minimum Latency Problem. European Journal of Operational Research 221:513–520. https://doi.org/10.1016/j.ejor.2012.03.044
* Salehipour A, Sörensen K, Goos P, Bräysy O (2011) Efficient GRASP+VND and GRASP+VNS metaheuristics for the traveling repairman problem. 4OR-Q J Oper Res 9:189–209. https://doi.org/10.1007/s10288-011-0153-0
* Ngueveu SU, Prins C, Wolfler Calvo R (2010) An effective memetic algorithm for the cumulative capacitated vehicle routing problem. Computers & Operations Research 37:1877–1885. https://doi.org/10.1016/j.cor.2009.06.014
* Blum A, Chalasani P, Coppersmith D, et al (1994) The minimum latency problem. In: Proceedings of the twenty-sixth annual ACM symposium on Theory of Computing. Association for Computing Machinery, New York, NY, USA, pp 163–171, https://doi.org/10.1145/195058.195125
* Fischetti M, Laporte G, Martello S (1993) The Delivery Man Problem and Cumulative Matroids. Operations Research 41:1055–1064. https://doi.org/10.1287/opre.41.6.1055

</p>
</details>

* Data: [travellingrepairman.7z](https://github.com/fontanf/orproblems/releases/download/data/travellingrepairman.7z)

[Thief Orienteering Problem](orproblems/thieforienteering.hpp)
* Description:
  * Determine a subset of items to collect
  * Maximize the profit of collected items
  * Each item is in a location, a location may contain multiple items
  * Each collected item decreases the speed of the traveller
  * Time limit and capacity constraint

<details><summary>Literature</summary>
<p>

* Chagas JBC, Wagner M (2021) Efficiently solving the thief orienteering problem with a max–min ant colony optimization approach. Optim Lett. https://doi.org/10.1007/s11590-021-01824-y
* Chagas JBC, Wagner M (2020) Ants can orienteer a thief in their robbery. Operations Research Letters. https://doi.org/10.1016/j.orl.2020.08.011
* Santos AG, Chagas JBC (2018) The Thief Orienteering Problem: Formulation and Heuristic Approaches. In: 2018 IEEE Congress on Evolutionary Computation (CEC). pp 1–9, https://doi.org/10.1109/CEC.2018.8477853

</p>
</details>

* Data: [thieforienteering.7z](https://github.com/fontanf/orproblems/releases/download/data/thieforienteering.7z)
* Algorithms: [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/thieforienteering.hpp)

### Multiple vehicles

[Capacitated Vehicle Routing Problem](orproblems/capacitatedvehiclerouting.hpp)

<details><summary>Literature</summary>
<p>

* Vidal T (2021) Hybrid genetic search for the CVRP: Open-source implementation and SWAP\* neighborhood. Computers & Operations Research 105643. https://doi.org/10.1016/j.cor.2021.105643
* Queiroga E, Sadykov R, Uchoa E (2021) A POPMUSIC matheuristic for the capacitated vehicle routing problem. Computers & Operations Research 105475. https://doi.org/10.1016/j.cor.2021.105475
* Accorsi L, Vigo D (2021) A Fast and Scalable Heuristic for the Solution of Large-Scale Capacitated Vehicle Routing Problems. Transportation Science. https://doi.org/10.1287/trsc.2021.1059
* Máximo VR, Nascimento MCV (2021) A hybrid adaptive Iterated Local Search with diversification control to the Capacitated Vehicle Routing Problem. European Journal of Operational Research. https://doi.org/10.1016/j.ejor.2021.02.024
* Christiaens J, Vanden Berghe G (2020) Slack Induction by String Removals for Vehicle Routing Problems. Transportation Science 54:417–433. https://doi.org/10.1287/trsc.2019.0914
* Toffolo TAM, Vidal T, Wauters T (2019) Heuristics for vehicle routing problems: Sequence or set optimization? Computers & Operations Research 105:118–131. https://doi.org/10.1016/j.cor.2018.12.023
* Uchoa E, Pecin D, Pessoa A, et al (2017) New benchmark instances for the Capacitated Vehicle Routing Problem. European Journal of Operational Research 257:845–858. https://doi.org/10.1016/j.ejor.2016.08.012
* Vidal T, Crainic TG, Gendreau M, Prins C (2014) A unified solution framework for multi-attribute vehicle routing problems. European Journal of Operational Research 234:658–673. https://doi.org/10.1016/j.ejor.2013.09.045
* Subramanian A, Uchoa E, Ochi LS (2013) A hybrid algorithm for a class of vehicle routing problems. Computers & Operations Research 40:2519–2531. https://doi.org/10.1016/j.cor.2013.01.013
* Prins C (2009) A GRASP × Evolutionary Local Search Hybrid for the Vehicle Routing Problem. In: Pereira FB, Tavares J (eds) Bio-inspired Algorithms for the Vehicle Routing Problem. Springer, Berlin, Heidelberg, pp 35–53, https://doi.org/10.1007/978-3-540-85152-3_2
* Prins C (2004) A simple and effective evolutionary algorithm for the vehicle routing problem. Computers & Operations Research 31:1985–2002. https://doi.org/10.1016/S0305-0548(03)00158-8
* Beasley J (1983) Route first—Cluster second methods for vehicle routing. Omega 11:403–408. https://doi.org/10.1016/0305-0483(83)90033-6
* Clarke G, Wright JW (1964) Scheduling of Vehicles from a Central Depot to a Number of Delivery Points. Operations Research 12:568–581. https://doi.org/10.1287/opre.12.4.568
* Dantzig GB, Ramser JH (1959) The Truck Dispatching Problem. Management Science 6:80–91. https://doi.org/10.1287/mnsc.6.1.80

</p>
</details>

* Data: [capacitatedvehiclerouting.7z](https://github.com/fontanf/orproblems/releases/download/data/capacitatedvehiclerouting.7z)
* Algorithms: [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver/blob/master/examples/capacitatedvehiclerouting.hpp)

[Vehicle Routing Problem with Time Windows](orproblems/vehicleroutingwithtimewindows.hpp)
* Time windows / Capacity constraint / Maximum number of vehicles

<details><summary>Literature</summary>
<p>

* Christiaens J, Vanden Berghe G (2020) Slack Induction by String Removals for Vehicle Routing Problems. Transportation Science 54:417–433. https://doi.org/10.1287/trsc.2019.0914
* Vidal T, Crainic TG, Gendreau M, Prins C (2015) Time-window relaxations in vehicle routing heuristics. J Heuristics 21:329–358. https://doi.org/10.1007/s10732-014-9273-y
* Vidal T, Crainic TG, Gendreau M, Prins C (2013) A hybrid genetic algorithm with adaptive diversity management for a large class of vehicle routing problems with time-windows. Computers & Operations Research 40:475–489. https://doi.org/10.1016/j.cor.2012.07.018
* Qi M, Lin W-H, Li N, Miao L (2012) A spatiotemporal partitioning approach for large-scale vehicle routing problems with time windows. Transportation Research Part E: Logistics and Transportation Review 48:248–257. https://doi.org/10.1016/j.tre.2011.07.001
* Nagata Y, Bräysy O, Dullaert W (2010) A penalty-based edge assembly memetic algorithm for the vehicle routing problem with time windows. Computers & Operations Research 37:724–737. https://doi.org/10.1016/j.cor.2009.06.022
* Repoussis PP, Tarantilis CD, Ioannou G (2009) Arc-Guided Evolutionary Algorithm for the Vehicle Routing Problem With Time Windows. IEEE Transactions on Evolutionary Computation 13:624–647. https://doi.org/10.1109/TEVC.2008.2011740
* Pisinger D, Ropke S (2007) A general heuristic for vehicle routing problems. Computers & Operations Research 34:2403–2435. https://doi.org/10.1016/j.cor.2005.09.012
* Gehring H, Homberger J (1999) A parallel hybrid evolutionary metaheuristic for the vehicle routing problem with time windows. In: Proceedings of EUROGEN99. Citeseer, pp 57–64

</p>
</details>

* Data: [vehicleroutingwithtimewindows.7z](https://github.com/fontanf/orproblems/releases/download/data/vehicleroutingwithtimewindows.7z)
* Algorithms: [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver/blob/master/examples/vehicleroutingwithtimewindows.hpp)

[Capacitated Open Vehicle Routing Problem](orproblems/capacitatedopenvehiclerouting.hpp)
* No need to return to the depot / Capacity constraint / Maximum route length / Maximum number of vehicles

<details><summary>Literature</summary>
<p>

* Vidal T, Crainic TG, Gendreau M, Prins C (2014) A unified solution framework for multi-attribute vehicle routing problems. European Journal of Operational Research 234:658–673. https://doi.org/10.1016/j.ejor.2013.09.045
* Marinakis Y, Marinaki M (2014) A Bumble Bees Mating Optimization algorithm for the Open Vehicle Routing Problem. Swarm and Evolutionary Computation 15:80–94. https://doi.org/10.1016/j.swevo.2013.12.003
* Subramanian A, Uchoa E, Ochi LS (2013) A hybrid algorithm for a class of vehicle routing problems. Computers & Operations Research 40:2519–2531. https://doi.org/10.1016/j.cor.2013.01.013
* Norouzi N, Tavakkoli-Moghaddam R, Ghazanfari M, et al (2012) A New Multi-objective Competitive Open Vehicle Routing Problem Solved by Particle Swarm Optimization. Netw Spat Econ 12:609–633. https://doi.org/10.1007/s11067-011-9169-4
* Zachariadis EE, Kiranoudis CT (2010) An open vehicle routing problem metaheuristic for examining wide solution neighborhoods. Computers & Operations Research 37:712–723. https://doi.org/10.1016/j.cor.2009.06.021
* Repoussis PP, Tarantilis CD, Bräysy O, Ioannou G (2010) A hybrid evolution strategy for the open vehicle routing problem. Computers & Operations Research 37:443–455. https://doi.org/10.1016/j.cor.2008.11.003
* Fleszar K, Osman IH, Hindi KS (2009) A variable neighbourhood search algorithm for the open vehicle routing problem. European Journal of Operational Research 195:803–809. https://doi.org/10.1016/j.ejor.2007.06.064
* Pisinger D, Ropke S (2007) A general heuristic for vehicle routing problems. Computers & Operations Research 34:2403–2435. https://doi.org/10.1016/j.cor.2005.09.012
* Sariklis D, Powell S (2000) A heuristic method for the open vehicle routing problem. Journal of the Operational Research Society 51:564–573. https://doi.org/10.1057/palgrave.jors.2600924

</p>
</details>

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

<details><summary>Literature</summary>
<p>

* Literature:
  * "A tabu search algorithm for order acceptance and scheduling" (Cesaret et al., 2012) [DOI](https://doi.org/10.1016/j.cor.2010.09.018)
  * "Hybrid evolutionary approaches for the single machine order acceptance and scheduling problem" (Chaurasia et Singh, 2017) [DOI](https://doi.org/10.1016/j.asoc.2016.09.051)
  * "Exact and heuristic algorithms for order acceptance and scheduling with sequence-dependent setup times" (Silva et al., 2018) [DOI](https://doi.org/10.1016/j.cor.2017.09.006)
  * "Tabu-Based Large Neighbourhood Search for Time/Sequence-Dependent Scheduling Problems with Time Windows" (He et al., 2019)
  * "Single-machine scheduling with release times, deadlines, setup times, and rejection" (de Weerdt et al., 2020) [DOI](https://doi.org/10.1016/j.ejor.2020.09.042)

</p>
</details>

* Data: [orderacceptanceandscheduling.7z](https://github.com/fontanf/orproblems/releases/download/data/orderacceptanceandscheduling.7z)
* Algorithms: [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver/blob/master/examples/orderacceptanceandscheduling.hpp), [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/orderacceptanceandscheduling.hpp)

[Single machine batch scheduling problem, Total completion time](orproblems/batchschedulingtotalcompletiontime.hpp)
* Three field classification: `1 | batch, sⱼ | ∑Cⱼ`

<details><summary>Literature</summary>
<p>

* Literature:
  * "Minimizing total flow time on a batch processing machine using a hybrid max–min ant system" (Rafiee Parsa et al., 2016) [DOI](https://doi.org/10.1016/j.cie.2016.06.008)
  * "A hybrid neural network approach to minimize total completion time on a single batch processing machine" (Rafiee Parsa et al., 2021) [DOI](https://doi.org/10.1111/itor.12665)
  * "Column generation for minimizing total completion time in a parallel-batching environment" (Alfieri et al., 2021) [DOI](https://doi.org/10.1007/s10951-021-00703-9)

</p>
</details>

* Data: [batchschedulingtotalcompletiontime.7z](https://github.com/fontanf/orproblems/releases/download/data/batchschedulingtotalcompletiontime.7z)

[Single machine batch scheduling problem, Total weighted tardiness](orproblems/batchschedulingtotalweightedtardiness.hpp)
* Three field classification: `1 | batch, rⱼ, sⱼ, compt | ∑wⱼTⱼ`

<details><summary>Literature</summary>
<p>

* Literature:
  * "Scheduling a batch processing machine to minimize total weighted tardiness" (Chou et Wang, 2008)
  * "Minimizing total weighted tardiness on a batch-processing machine with non-agreeable release times and due dates" (Mathirajan et al., 2010) [DOI](https://doi.org/10.1007/s00170-009-2342-y)
  * "Solving single batch-processing machine problems using an iterated heuristic" (Wang, 2011) [DOI](https://doi.org/10.1080/00207543.2010.518995)
  * "Iterated local search for single machine total weighted tardiness batch scheduling" (Queiroga et al., 2020) [DOI](https://doi.org/10.1007/s10732-020-09461-x)

</p>
</details>

* Data: [batchschedulingtotalweightedtardiness.7z](https://github.com/fontanf/orproblems/releases/download/data/batchschedulingtotalweightedtardiness.7z)
* Algorithms: [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/batchschedulingtotalweightedtardiness.hpp)

### (Unrelated) parallel machine scheduling

[Identical parallel machine scheduling problem with family setup times, Total weighted completion time](orproblems/parallelschedulingwithfamilysetuptimestwct.hpp)
* Three field classification: `P | sᵢ | ∑wⱼCⱼ`

<details><summary>Literature</summary>
<p>

* Literature:
  * "Heuristic methods for the identical parallel machine flowtime problem with set-up times" (Dunstall et Wirth, 2005) [DOI](https://doi.org/10.1016/j.cor.2004.03.013)
  * "An improved heuristic for parallel machine weighted flowtime scheduling with family set-up times" (Liao et al., 2012) [DOI](https://doi.org/10.1016/j.camwa.2011.10.077)
  * "Mathematical formulations for scheduling jobs on identical parallel machines with family setup times and total weighted completion time minimization" (Kramer et al., 2021) [DOI](https://doi.org/10.1016/j.ejor.2019.07.006)

</p>
</details>

* Data: [parallelschedulingwithfamilysetuptimestwct.7z](https://github.com/fontanf/orproblems/releases/download/data/parallelschedulingwithfamilysetuptimestwct.7z)
* Algorithms: [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver/blob/master/examples/parallelschedulingwithfamilysetuptimestwct.hpp)

[Star Observation Scheduling Problem](orproblems/starobservationscheduling.hpp)
* Three field classification: `R | rⱼᵢ, 2 pⱼᵢ ≥ dⱼᵢ - rⱼᵢ | ∑wⱼUⱼ`

<details><summary>Literature</summary>
<p>

* Literature:
  * "A Branch-And-Price Algorithm for Scheduling Observations on a Telescope" (Catusse et al., 2016)

</p>
</details>

* Data: [starobservationscheduling.7z](https://github.com/fontanf/orproblems/releases/download/data/starobservationscheduling.7z)
* Algorithms: [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver/blob/master/examples/starobservationscheduling.hpp)

### Flow shop scheduling

[Permutation flow shop scheduling problem, Makespan](orproblems/permutationflowshopschedulingmakespan.hpp)
* Three field classification: `Fm | prmu | Cₘₐₓ`

<details><summary>Literature</summary>
<p>

* Literature:
  * "An Effective Hybrid Heuristic for Flow Shop Scheduling" (Zheng et Wang, 2003) [DOI](https://doi.org/10.1007/s001700300005)
  * "Two new robust genetic algorithms for the flowshop scheduling problem" (Ruiz et al., 2006) [DOI](https://doi.org/10.1016/j.omega.2004.12.006)
  * "A simple and effective iterated greedy algorithm for the permutation flowshop scheduling problem" (Ruiz et Stützle, 2007) [DOI](https://doi.org/10.1016/j.ejor.2005.12.009)
  * "Cooperative metaheuristics for the permutation flowshop scheduling problem" (Vallada et Ruiz, 2009) [DOI](https://doi.org/10.1016/j.ejor.2007.11.049)
  * "A Variable Block Insertion Heuristic for Solving Permutation Flow Shop Scheduling Problem with Makespan Criterion" (Kizilay et al., 2019) [DOI](https://doi.org/10.3390/a12050100)
  * "A best-of-breed iterated greedy for the permutation flowshop scheduling problem with makespan objective" (Fernandez-Viagas, Framinan, 2019) [DOI](https://doi.org/10.1016/j.cor.2019.104767)
  * "A memetic algorithm with novel semi-constructive evolution operators for permutation flowshop scheduling problem" (Kurdi, 2020) [DOI](https://doi.org/10.1016/j.asoc.2020.106458)
  * "Iterative beam search algorithms for the permutation flowshop" (Libralesso et al., 2021) [DOI](https://doi.org/10.1016/j.ejor.2021.10.015)

</p>
</details>

* Data: [permutationflowshopscheduling.7z](https://github.com/fontanf/orproblems/releases/download/data/permutationflowshopscheduling.7z)
* Algorithms: [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver/blob/master/examples/permutationflowshopschedulingmakespan.hpp), [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/permutationflowshopschedulingmakespan.hpp)

[Permutation flow shop scheduling problem, Total completion time](orproblems/permutationflowshopschedulingtct.hpp)
* Three field classification: `Fm | prmu | ∑Cⱼ`

<details><summary>Literature</summary>
<p>

* Literature:
  * "Constructive and composite heuristic solutions to the P//∑Ci scheduling problem" (Liu et Reeves, 2001) [DOI](https://doi.org/10.1016/S0377-2217(00)00137-5)
  * "Local search methods for the flowshop scheduling problem with flowtime minimization" (Pan et Ruiz, 2012) [DOI](https://doi.org/10.1016/j.ejor.2012.04.034)
  * "A new set of high-performing heuristics to minimise flowtime in permutation flowshops" (Fernandez-Viagas et Framinan, 2015) [DOI](https://doi.org/10.1016/j.cor.2014.08.004)
  * "A beam-search-based constructive heuristic for the PFSP to minimise total flowtime" (Fernandez-Viagas et Framinan, 2017) [DOI](https://doi.org/10.1016/j.cor.2016.12.020)
  * "Minimizing flowtime in a flowshop scheduling problem with a biased random-key genetic algorithm" (Andrade et al., 2019) [DOI](https://doi.org/10.1016/j.eswa.2019.03.007)
  * "Iterative beam search algorithms for the permutation flowshop" (Libralesso et al., 2021) [DOI](https://doi.org/10.1016/j.ejor.2021.10.015)

</p>
</details>

* Data: [permutationflowshopscheduling.7z](https://github.com/fontanf/orproblems/releases/download/data/permutationflowshopscheduling.7z)
* Algorithms: [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver/blob/master/examples/permutationflowshopschedulingtct.hpp), [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/permutationflowshopschedulingtct.hpp)

[Permutation flow shop scheduling problem, Total tardiness](orproblems/permutationflowshopschedulingtt.hpp)
* Three field classification: `Fm | prmu | ∑Tⱼ`

<details><summary>Literature</summary>
<p>

* Literature:
  * "Heuristics for Flowshop Scheduling Problems Minimizing Mean Tardiness" (Kim, 1993) [DOI](https://doi.org/10.1057/jors.1993.3)
  * "Minimising total tardiness in the m-machine flowshop problem: A review and evaluation of heuristics and metaheuristics"  (Vallada et al., 2008) [DOI](https://doi.org/10.1016/j.cor.2006.08.016)
  * "Total tardiness minimization in permutation flow shops: a simple approach based on a variable greedy algorithm" (Framinan et Leisten, 2008) [DOI](https://doi.org/10.1080/00207540701418960)
  * "Cooperative metaheuristics for the permutation flowshop scheduling problem" (Vallada et Ruiz, 2009) [DOI](https://doi.org/10.1016/j.ejor.2007.11.049)
  * "Genetic algorithms with path relinking for the minimum tardiness permutation flowshop problem" (Vallada et Ruiz, 2010) [DOI](https://doi.org/10.1016/j.omega.2009.04.002)
  * "An evolutionary algorithm for the permutation flowshop scheduling problem with total tardiness criterion" (Cura, 2015) [DOI](https://doi.org/10.1504/IJOR.2015.068287)
  * "NEH-based heuristics for the permutation flowshop scheduling problem to minimise total tardiness" (Fernandez-Viagas et Framinan, 2015) [DOI](https://doi.org/10.1016/j.cor.2015.02.002)
  * "Trajectory Scheduling Methods for minimizing total tardiness in a flowshop" (Li et al., 2015) [DOI](https://doi.org/10.1016/j.orp.2014.12.001)
  * "A hybrid iterated greedy algorithm for total tardiness minimization in permutation flowshops" (Karabulut, 2016) [DOI](https://doi.org/10.1016/j.cie.2016.06.012)
  * "Matheuristic algorithms for minimizing total tardiness in the m-machine flow-shop scheduling problem" (Ta et al., 2015) [DOI](https://doi.org/10.1007/s10845-015-1046-4)
  * "Iterated-greedy-based algorithms with beam search initialization for the permutation flowshop to minimise total tardiness" (Fernandez-Viagas et al., 2018) [DOI](https://doi.org/10.1016/j.eswa.2017.10.050)

</p>
</details>

* Data: [permutationflowshopscheduling.7z](https://github.com/fontanf/orproblems/releases/download/data/permutationflowshopscheduling.7z)
* Algorithms: [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver/blob/master/examples/permutationflowshopschedulingtt.hpp), [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/permutationflowshopschedulingtt.hpp)

### Job shop scheduling

[No-wait job shop scheduling problem, Makespan](orproblems/nowaitjobshopschedulingmakespan.hpp)
* Three field classification: `Jm | no-wait | Cₘₐₓ`

<details><summary>Literature</summary>
<p>

* Literature:
  * "Job-shop scheduling with blocking and no-wait constraints" (Mascis et Pacciarelli, 2002) [DOI](https://doi.org/10.1016/S0377-2217(01)00338-1)
  * "Approximative procedures for no-wait job shop scheduling" (Schuster et Framinan, 2003) [DOI](https://doi.org/10.1016/S0167-6377(03)00005-1)
  * "Minimizing Makespan in No-Wait Job Shops" (Bansal et al., 2005) [DOI](https://doi.org/10.1287/moor.1050.0155)
  * "No-Wait Job Shop Scheduling, a Constraint Propagation Approach" (Lennartz, 2006)
  * "An enhanced timetabling procedure for the no-wait job shop problem: a complete local search approach" (Framinan et Schuster) [DOI](https://doi.org/10.1016/j.cor.2004.09.009)
  * "No-wait Job Shop Scheduling: Tabu Search and Complexity of Subproblems" (Schuster, 2006) [DOI](https://doi.org/10.1007/s00186-005-0056-y)
  * "MIP-based approaches for complex planning problems" (van den Broek, 2009)
  * "A hybrid genetic algorithm for no-wait job shop scheduling problems" (Pan et Huang, 2009) [DOI](https://doi.org/10.1016/j.eswa.2008.07.005)
  * "A fast hybrid tabu search algorithm for the no-wait job shop problem" (Bożejko et Makuchowski, 2009) [DOI](https://doi.org/10.1016/j.cie.2008.09.023)
  * "Complete local search with limited memory algorithm for no-wait job shops to minimize makespan" (Zhu et al., 2009) [DOI](https://doi.org/10.1016/j.ejor.2008.09.015)
  * "Solving the no-wait job shop problem: an ILP and CP approach" (Vermeulen et al., 2011)
  * "A Cross Entropy-Genetic Algorithm for m-Machines No-Wait Job-ShopScheduling Problem" (Santosa et al., 2011) [DOI](http://dx.doi.org/10.4236/jilsa.2011.33018)
  * "Solving the no-wait job-shop problem by using genetic algorithm with automatic adjustment" (Bożejko et Makuchowski, 2011) [DOI](https://doi.org/10.1007/s00170-011-3297-3)
  * "An Effective Meta-Heuristic for No-Wait Job Shops to Minimize Makespan" (Zhu et Li, 2011) [DOI](https://doi.org/10.1109/TASE.2011.2163305)
  * "Optimal job insertion in the no-wait job shop" (Bürgy et Gröflin, 2013) [DOI](https://doi.org/10.1007/s10878-012-9466-y)
  * "Algorithm based on K-neighborhood search for no-wait job shop scheduling problems" (Wang et Yin, 2015) [DOI](https://doi.org/10.1109/CCDC.2015.7162672)
  * "Branch-and-bound and PSO algorithms for no-wait job shop scheduling" (AitZai et al., 2016) [DOI](https://doi.org/10.1007/s10845-014-0906-7)
  * "A memory-based complete local search method with variable neighborhood structures for no-wait job shops" (Li et al., 2016) [DOI](https://doi.org/10.1007/s00170-013-4866-4)
  * "A hybrid artificial bee colony algorithm for the job-shop scheduling problem with no-wait constraint" (Sundar et al., 2017) [DOI](https://doi.org/10.1007/s00500-015-1852-9)
  * "An Evolutionary Algorithm Based Hyper-heuristic for the Job-Shop Scheduling Problem with No-Wait Constraint" (Chaurasia et al., 2018) [DOI](https://doi.org/10.1007/978-981-13-0761-4_25)
  * "A combination of two simple decoding strategies for the no-wait job shop scheduling problem" (Valenzuela et al., 2019) [DOI](https://doi.org/10.1145/3321707.3321870)
  * "Solving no-wait job-shop scheduling problems using a multi-start simulated annealing with bi-directional shift timetabling algorithm" (Ying et Lin, 2020) [DOI](https://doi.org/10.1016/j.cie.2020.106615)
  * "A new exact algorithm for no-wait job shop problem to minimize makespan" (Ozolins, 2020) [DOI](https://doi.org/10.1007/s12351-018-0414-1)

</p>
</details>

* Data: [jobshopscheduling.7z](https://github.com/fontanf/orproblems/releases/download/data/jobshopscheduling.7z)
* Algorithms: [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/nowaitjobshopschedulingmakespan.hpp)

### Assembly Line Balancing

[Simple Assembly Line Balancing Problem of Type 1 (SALBP-1)](orproblems/simpleassemblylinebalancing1.hpp)
* Bin Packing Problem with precedence constraints of the form `bin(j1) <= bin(j2) `

<details><summary>Literature</summary>
<p>

* Literature:
  * "Simple assembly line balancing—Heuristic approaches" (Scholl et Voß, 1997) [DOI](https://doi.org/10.1007/BF00127358)
  * "State-of-the-art exact and heuristic solution procedures for simple assembly line balancing" (Scholl et Becker, 2006) [DOI](https://doi.org/10.1016/j.ejor.2004.07.022)
  * "Beam-ACO for Simple Assembly Line Balancing" (Blum, 2008) [DOI](https://doi.org/10.1287/ijoc.1080.0271)
  * "A Branch, Bound, and Remember Algorithm for the Simple Assembly Line Balancing Problem" (Sewell et Jacobson, 2011) [DOI](https://doi.org/10.1287/ijoc.1110.0462)
  * "An application of the branch, bound, and remember algorithm to a new simple assembly line balancing dataset" (Morrison et al., 2014) [DOI](https://doi.org/10.1016/j.ejor.2013.11.033)

</p>
</details>

* Data: [simpleassemblylinebalancing1.7z](https://github.com/fontanf/orproblems/releases/download/data/simpleassemblylinebalancing1.7z)
* Algorithms: [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/simpleassemblylinebalancing1.hpp)

[U-shaped Assembly Line Balancing Problem of Type 1 (UALBP-1)](orproblems/ushapedassemblylinebalancing1.hpp)

<details><summary>Literature</summary>
<p>

* Literature
  * "Balancing of U-type assembly systems using simulated annealing" (Erel et al., 2001) [DOI](https://doi.org/10.1080/00207540110051905)
  * "Ant colony optimization for the single model U-type assembly line balancing problem" (Sabuncuoglu et al., 2013) [DOI](https://doi.org/10.1016/j.ijpe.2008.11.017)
  * "New MILP model and station-oriented ant colony optimization algorithm for balancing U-type assembly lines" (Li et al., 2017) [DOI](https://doi.org/10.1016/j.cie.2017.07.005)
  * "Branch, bound and remember algorithm for U-shaped assembly line balancing problem" (Li et al., 2018) [DOI](https://doi.org/10.1016/j.cie.2018.06.037)
  * "Enhanced beam search heuristic for U-shaped assembly line balancing problems" (Li et al., 2020) [DOI](https://doi.org/10.1080/0305215X.2020.1741569)

</p>
</details>

* Data: [simpleassemblylinebalancing1.7z](https://github.com/fontanf/orproblems/releases/download/data/simpleassemblylinebalancing1.7z)
* Algorithms: [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver/blob/master/examples/ushapedassemblylinebalancing1.hpp)

### Resource constrained scheduling

[ROADEF/EURO Challenge 2020: Maintenance Planning Problem](orproblems/roadef2020.hpp)
* Website: https://www.roadef.org/challenge/2020/en/
* Data: [roadef2020.7z](https://github.com/fontanf/orproblems/releases/download/data/roadef2020.7z)
* Algorithms: [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver/blob/master/examples/roadef2020.hpp)

