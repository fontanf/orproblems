# Operations Research Problems

Data, C++ parsers and solution checkers for various Operations Research problems.

These are the problems used as examples for [fontanf/localsearchsolver](https://github.com/fontanf/localsearchsolver), [fontanf/treesearchsolver](https://github.com/fontanf/treesearchsolver) and [fontanf/columngenerationsolver](https://github.com/fontanf/columngenerationsolver).

The data also include CSV files listing the instances for each problem and their best known bounds which can be used with the benchmark scripts from [fontanf/optimizationtools](https://github.com/fontanf/optimizationtools).


## Packing


[Knapsack Problem with Conflicts / Disjunctively Constrained Knapsack Problem](orproblems/knapsackwithconflicts.hpp)

<details><summary>Literature</summary>
<p>

* Luiz TA, Santos HG, Uchoa E (2021) Cover by Disjoint Cliques Cuts for the Knapsack Problem with Conflicting Items. Operations Research Letters. https://doi.org/10.1016/j.orl.2021.10.001
* Wei Z, Hao J-K (2021) A threshold search based memetic algorithm for the disjunctively constrained knapsack problem. Computers & Operations Research 105447. https://doi.org/10.1016/j.cor.2021.105447
* Coniglio S, Furini F, Segundo PS (2020) A new combinatorial branch-and-bound algorithm for the Knapsack Problem with Conflicts. European Journal of Operational Research. https://doi.org/10.1016/j.ejor.2020.07.023
* Ben Salem M, Taktak R, Mahjoub AR, Ben-Abdallah H (2018) Optimization algorithms for the disjunctively constrained knapsack problem. Soft Comput 22:2025–2043. https://doi.org/10.1007/s00500-016-2465-7
* Quan Z, Wu L (2017a) Cooperative parallel adaptive neighbourhood search for the disjunctively constrained knapsack problem. Engineering Optimization 49:1541–1557. https://doi.org/10.1080/0305215X.2016.1257854
* Salem MB, Hanafi S, Taktak R, Abdallah HB (2017) Probabilistic Tabu search with multiple neighborhoods for the Disjunctively Constrained Knapsack Problem. RAIRO-Oper Res 51:627–637. https://doi.org/10.1051/ro/2016049
* Bettinelli A, Cacchiani V, Malaguti E (2017) A Branch-and-Bound Algorithm for the Knapsack Problem with Conflict Graph. INFORMS Journal on Computing 29:457–473. https://doi.org/10.1287/ijoc.2016.0742
* Quan Z, Wu L (2017b) Design and evaluation of a parallel neighbor algorithm for the disjunctively constrained knapsack problem. Concurrency and Computation: Practice and Experience 29:e3848. https://doi.org/10.1002/cpe.3848
* Hifi M (2014) An iterative rounding search-based algorithm for the disjunctively constrained knapsack problem. Engineering Optimization 46:1109–1122. https://doi.org/10.1080/0305215X.2013.819096
* Sadykov R, Vanderbeck F (2012) Bin Packing with Conflicts: A Generic Branch-and-Price Algorithm. INFORMS Journal on Computing 25:244–255. https://doi.org/10.1287/ijoc.1120.0499
* Hifi M, Otmani N (2012) An algorithm for the disjunctively constrained knapsack problem. International Journal of Operational Research 13:22–43. https://doi.org/10.1504/IJOR.2012.044026
* Akeb H, Hifi M, Ould Ahmed Mounir ME (2011) Local branching-based algorithms for the disjunctively constrained knapsack problem. Computers & Industrial Engineering 60:811–820. https://doi.org/10.1016/j.cie.2011.01.019
* Hifi M, Michrafy M (2007) Reduction strategies and exact algorithms for the disjunctively constrained knapsack problem. Computers & Operations Research 34:2657–2673. https://doi.org/10.1016/j.cor.2005.10.004
* Hifi M, Michrafy M (2006) A reactive local search-based algorithm for the disjunctively constrained knapsack problem. Journal of the Operational Research Society 57:718–726. https://doi.org/10.1057/palgrave.jors.2602046
* Yamada T, Kataoka S, Watanabe K (2002) Heuristic and exact algorithms for the disjunctively constrained knapsack problem. Information Processing Society of Japan Journal 43:

</p>
</details>

* Data: [knapsackwithconflicts.7z](https://github.com/fontanf/orproblems/releases/download/data/knapsackwithconflicts.7z)


[Multidimensional Multiple-choice Knapsack Problem](orproblems/multidimensionalmultiplechoiceknapsack.hpp)

<details><summary>Literature</summary>
<p>

* Lamanna L, Mansini R, Zanotti R (2021) A Two-phase Kernel Search variant for the Multidimensional Multiple-choice Knapsack Problem. European Journal of Operational Research. https://doi.org/10.1016/j.ejor.2021.05.007
* Mansini R, Zanotti R (2020) A Core-Based Exact Algorithm for the Multidimensional Multiple Choice Knapsack Problem. INFORMS Journal on Computing. https://doi.org/10.1287/ijoc.2019.0909
* Gao C, Lu G, Yao X, Li J (2017) An iterative pseudo-gap enumeration approach for the Multidimensional Multiple-choice Knapsack Problem. European Journal of Operational Research 260:1–11. https://doi.org/10.1016/j.ejor.2016.11.042
* Voß S, Lalla-Ruiz E (2016) A set partitioning reformulation for the multiple-choice multidimensional knapsack problem. Engineering Optimization 48:831–850. https://doi.org/10.1080/0305215X.2015.1062094
* Hifi M, Wu L (2015) Lagrangian heuristic-based neighbourhood search for the multiple-choice multi-dimensional knapsack problem. Engineering Optimization 47:1619–1636. https://doi.org/10.1080/0305215X.2014.982631
* Chen Y, Hao J-K (2014) A “reduce and solve” approach for the multiple-choice multidimensional knapsack problem. European Journal of Operational Research 239:313–322. https://doi.org/10.1016/j.ejor.2014.05.025
* Shojaei H, Basten T, Geilen M, Davoodi A (2013) A fast and scalable multidimensional multiple-choice knapsack heuristic. ACM Trans Des Autom Electron Syst 18:51:1-51:32. https://doi.org/10.1145/2541012.2541014
* Mansi R, Alves C, Carvalho JMV de, Hanafi S (2013) A hybrid heuristic for the multiple choice multidimensional knapsack problem. Engineering Optimization 45:983–1004. https://doi.org/10.1080/0305215X.2012.717072
* Crévits I, Hanafi S, Mansi R, Wilbaut C (2012) Iterative semi-continuous relaxation heuristics for the multiple-choice multidimensional knapsack problem. Computers & Operations Research 39:32–41. https://doi.org/10.1016/j.cor.2010.12.016
* Ghasemi T, Razzazi M (2011) Development of core to solve the multidimensional multiple-choice knapsack problem. Computers & Industrial Engineering 60:349–360. https://doi.org/10.1016/j.cie.2010.12.001
* Cherfi N, Hifi M (2010) A column generation method for the multiple-choice multi-dimensional knapsack problem. Comput Optim Appl 46:51–73. https://doi.org/10.1007/s10589-008-9184-7
* Hifi M, Michrafy M, Sbihi A (2006) A Reactive Local Search-Based Algorithm for the Multiple-Choice Multi-Dimensional Knapsack Problem. Comput Optim Applic 33:271–285. https://doi.org/10.1007/s10589-005-3057-0
* Hifi M, Michrafy M, Sbihi A (2004) Heuristic algorithms for the multiple-choice multidimensional knapsack problem. Journal of the Operational Research Society 55:1323–1332. https://doi.org/10.1057/palgrave.jors.2601796

</p>
</details>

* Data: [multidimensionalmultiplechoiceknapsack.7z](https://github.com/fontanf/orproblems/releases/download/data/multidimensionalmultiplechoiceknapsack.7z)


[Quadratic Assignment Problem](orproblems/quadraticassignment.hpp)

<details><summary>Literature</summary>
<p>

* Mallach S (2020) Inductive linearization for binary quadratic programs with linear constraints. 4OR-Q J Oper Res. https://doi.org/10.1007/s10288-020-00460-z
* Dokeroglu T, Sevinc E, Cosar A (2019) Artificial bee colony optimization for the quadratic assignment problem. Applied Soft Computing 76:595–606. https://doi.org/10.1016/j.asoc.2019.01.001
* Abdel-Basset M, Manogaran G, El-Shahat D, Mirjalili S (2018a) Integrating the whale algorithm with Tabu search for quadratic assignment problem: A new approach for locating hospital departments. Applied Soft Computing 73:530–546. https://doi.org/10.1016/j.asoc.2018.08.047
* Abdel-Basset M, Manogaran G, Rashad H, Zaied ANH (2018b) A comprehensive review of quadratic assignment problem: variants, hybrids and applications. J Ambient Intell Human Comput. https://doi.org/10.1007/s12652-018-0917-x
* Bravo Ferreira JFS, Khoo Y, Singer A (2018) Semidefinite programming approach for the quadratic assignment problem with a sparse graph. Comput Optim Appl 69:677–712. https://doi.org/10.1007/s10589-017-9968-8
* Ahmed ZH (2018) A hybrid algorithm combining lexisearch and genetic algorithms for the quadratic assignment problem. Cogent Engineering 5:1423743. https://doi.org/10.1080/23311916.2018.1423743
* Gonçalves AD, Pessoa AA, Bentes C, et al (2017) A Graphics Processing Unit Algorithm to Solve the Quadratic Assignment Problem Using Level-2 Reformulation-Linearization Technique. INFORMS Journal on Computing 29:676–687. https://doi.org/10.1287/ijoc.2017.0754
* Ahyaningsih F (2017) A combined strategy for solving quadratic assignment problem. AIP Conference Proceedings 1867:020006. https://doi.org/10.1063/1.4994409
* Mzili I, Riffi ME, Benzekri F (2017) Penguins Search Optimization Algorithm to Solve Quadratic Assignment Problem. In: Proceedings of the 2nd international Conference on Big Data, Cloud and Applications. Association for Computing Machinery, New York, NY, USA, pp 1–6, https://doi.org/10.1145/3090354.3090375
* Shylo PV (2017) Solving the Quadratic Assignment Problem by the Repeated Iterated Tabu Search Method. Cybern Syst Anal 53:308–311. https://doi.org/10.1007/s10559-017-9930-x
* Ismail MM, Hezam IM, El-Sharkawy E (2017) Enhanced Cuckoo Search Algorithm with SPV Rule for Quadratic Assignment Problem. International Journal of Computer Applications 158:39–42
* Aksan Y, Dokeroglu T, Cosar A (2017) A stagnation-aware cooperative parallel breakout local search algorithm for the quadratic assignment problem. Computers & Industrial Engineering 103:105–115. https://doi.org/10.1016/j.cie.2016.11.023
* Chmiel W, Kadłuczka P, Kwiecień J, Filipowicz B (2017) A comparison of nature inspired algorithms for the quadratic assignment problem. Bulletin of the Polish Academy of Sciences Technical Sciences Vol. 65: https://doi.org/10.1515/bpasts-2017-0056
* Ahmed ZH (2016) Experimental analysis of crossover and mutation operators on the quadratic assignment problem. Ann Oper Res 247:833–851. https://doi.org/10.1007/s10479-015-1848-y
* Dokeroglu T, Cosar A (2016) A novel multistart hyper-heuristic algorithm on the grid for the quadratic assignment problem. Engineering Applications of Artificial Intelligence 52:10–25. https://doi.org/10.1016/j.engappai.2016.02.004
* Hafiz F, Abdennour A (2016) Particle Swarm Algorithm variants for the Quadratic Assignment Problems - A probabilistic learning approach. Expert Systems with Applications 44:413–431. https://doi.org/10.1016/j.eswa.2015.09.032
* Chmiel W, Szwed P (2016) Bees Algorithm for the Quadratic Assignment Problem on CUDA Platform. In: Gruca A, Brachman A, Kozielski S, Czachórski T (eds) Man–Machine Interactions 4. Springer International Publishing, Cham, pp 615–625, https://doi.org/10.1007/978-3-319-23437-3_53
* Munera D, Diaz D, Abreu S (2016a) Solving the Quadratic Assignment Problem with Cooperative Parallel Extremal Optimization. In: Chicano F, Hu B, García-Sánchez P (eds) Evolutionary Computation in Combinatorial Optimization. Springer International Publishing, Cham, pp 251–266, https://doi.org/10.1007/978-3-319-30698-8_17
* Munera D, Diaz D, Abreu S (2016b) Hybridization as Cooperative Parallelism for the Quadratic Assignment Problem. In: Blesa MJ, Blum C, Cangelosi A, et al. (eds) Hybrid Metaheuristics. Springer International Publishing, Cham, pp 47–61, https://doi.org/10.1007/978-3-319-39636-1_4
* Sghir I, Hao J-K, Jaafar IB, Ghédira K (2015) A multi-agent based optimization method applied to the quadratic assignment problem. Expert Systems with Applications 42:9252–9262. https://doi.org/10.1016/j.eswa.2015.07.070
* Acan A, Ünveren A (2015) A great deluge and tabu search hybrid with two-stage memory support for quadratic assignment problem. Applied Soft Computing 36:185–203. https://doi.org/10.1016/j.asoc.2015.06.061
* Xia Y, Gharibi W (2015) On improving convex quadratic programming relaxation for the quadratic assignment problem. J Comb Optim 30:647–667. https://doi.org/10.1007/s10878-013-9655-3
* de Klerk E, Sotirov R, Truetsch U (2015) A New Semidefinite Programming Relaxation for the Quadratic Assignment Problem and Its Computational Perspectives. INFORMS Journal on Computing 27:378–391. https://doi.org/10.1287/ijoc.2014.0634
* Benlic U, Hao J-K (2015) Memetic search for the quadratic assignment problem. Expert Systems with Applications 42:584–595. https://doi.org/10.1016/j.eswa.2014.08.011
* Zhang H, Beltran-Royo C, Ma L (2013) Solving the quadratic assignment problem by means of general purpose mixed integer linear programming solvers. Ann Oper Res 207:261–278. https://doi.org/10.1007/s10479-012-1079-4
* Benlic U, Hao J-K (2013) Breakout local search for the quadratic assignment problem. Applied Mathematics and Computation 219:4800–4815. https://doi.org/10.1016/j.amc.2012.10.106
* Fischetti M, Monaci M, Salvagnin D (2012) Three Ideas for the Quadratic Assignment Problem. Operations Research 60:954–964. https://doi.org/10.1287/opre.1120.1073
* Nyberg A, Westerlund T (2012) A new exact discrete linear reformulation of the quadratic assignment problem. European Journal of Operational Research 220:314–319. https://doi.org/10.1016/j.ejor.2012.02.010
* Hahn PM, Zhu Y-R, Guignard M, et al (2012) A Level-3 Reformulation-Linearization Technique-Based Bound for the Quadratic Assignment Problem. INFORMS Journal on Computing 24:202–209. https://doi.org/10.1287/ijoc.1110.0450
* Zhang H, Beltran-Royo C, Constantino M (2010) Effective formulation reductions for the quadratic assignment problem. Computers & Operations Research 37:2007–2016. https://doi.org/10.1016/j.cor.2010.02.001
* Rego C, James T, Glover F (2010) An ejection chain algorithm for the quadratic assignment problem. Networks 56:188–206. https://doi.org/10.1002/net.20360
* James T, Rego C, Glover F (2009a) A cooperative parallel tabu search algorithm for the quadratic assignment problem. European Journal of Operational Research 195:810–826. https://doi.org/10.1016/j.ejor.2007.06.061
* James T, Rego Cé, Glover F (2009b) Multistart Tabu Search and Diversification Strategies for the Quadratic Assignment Problem. IEEE Transactions on Systems, Man, and Cybernetics - Part A: Systems and Humans 39:579–596. https://doi.org/10.1109/TSMCA.2009.2014556
* Loukil L, Mehdi M, Melab N, et al (2009) A parallel hybrid genetic algorithm-simulated annealing for solving Q3AP on computational grid. In: 2009 IEEE International Symposium on Parallel Distributed Processing. pp 1–8, https://doi.org/10.1109/IPDPS.2009.5161126
* Drezner Z (2008) Extensive experiments with hybrid genetic algorithms for the solution of the quadratic assignment problem. Computers & Operations Research 35:717–736. https://doi.org/10.1016/j.cor.2006.05.004
* Xia Y (2008) Gilmore-Lawler bound of quadratic assignment problem. Front Math China 3:109–118. https://doi.org/10.1007/s11464-008-0010-4
* Tsutsui S (2008) Parallel Ant Colony Optimization for the Quadratic Assignment Problems with Symmetric Multi Processing. In: Dorigo M, Birattari M, Blum C, et al. (eds) Ant Colony Optimization and Swarm Intelligence. Springer, Berlin, Heidelberg, pp 363–370, https://doi.org/10.1007/978-3-540-87527-7_38
* Adams WP, Guignard M, Hahn PM, Hightower WL (2007) A level-2 reformulation–linearization technique bound for the quadratic assignment problem. European Journal of Operational Research 180:983–996. https://doi.org/10.1016/j.ejor.2006.03.051
* Erdoğan G, Tansel B (2007) A branch-and-cut algorithm for quadratic assignment problems based on linearizations. Computers & Operations Research 34:1085–1106. https://doi.org/10.1016/j.cor.2005.05.027
* Rendl F, Sotirov R (2007) Bounds for the quadratic assignment problem using the bundle method. Math Program 109:505–524. https://doi.org/10.1007/s10107-006-0038-8
* Loiola EM, de Abreu NMM, Boaventura-Netto PO, et al (2007) A survey for the quadratic assignment problem. European Journal of Operational Research 176:657–690. https://doi.org/10.1016/j.ejor.2005.09.032
* Liu H, Abraham A, Zhang J (2007) A Particle Swarm Approach to Quadratic Assignment Problems. In: Saad A, Dahal K, Sarfraz M, Roy R (eds) Soft Computing in Industrial Applications. Springer, Berlin, Heidelberg, pp 213–222, https://doi.org/10.1007/978-3-540-70706-6_20
* Stützle T (2006) Iterated local search for the quadratic assignment problem. European Journal of Operational Research 174:1519–1539. https://doi.org/10.1016/j.ejor.2005.01.066
* Tseng L-Y, Liang S-C (2006) A Hybrid Metaheuristic for the Quadratic Assignment Problem. Comput Optim Applic 34:85–113. https://doi.org/10.1007/s10589-005-3069-9
* Ji P, Wu Y, Liu H (2006) A solution method for the quadratic assignment problem (QAP). In: The Sixth International Symposium on Operations Research and Its Applications (ISORA’06), Xinjiang, China, August. pp 8–12
* Drezner Z, Hahn PM, Taillard ÉD (2005) Recent Advances for the Quadratic Assignment Problem with Special Emphasis on Instances that are Difficult for Meta-Heuristic Methods. Ann Oper Res 139:65–94. https://doi.org/10.1007/s10479-005-3444-z
* Drezner Z (2005a) Compounded genetic algorithms for the quadratic assignment problem. Operations Research Letters 33:475–480. https://doi.org/10.1016/j.orl.2004.11.001
* Drezner Z (2005b) The extended concentric tabu for the quadratic assignment problem. European Journal of Operational Research 160:416–422. https://doi.org/10.1016/S0377-2217(03)00438-7
* Misevicius A (2005) A Tabu Search Algorithm for the Quadratic Assignment Problem. Comput Optim Applic 30:95–111. https://doi.org/10.1007/s10589-005-4562-x
* Fedjki CA, Duffuaa SO (2004) An extreme point algorithm for a local minimum solution to the quadratic assignment problem. European Journal of Operational Research 156:566–578. https://doi.org/10.1016/S0377-2217(03)00132-2
* Misevicius A (2004) An improved hybrid genetic algorithm: new results for the quadratic assignment problem. Knowledge-Based Systems 17:65–73. https://doi.org/10.1016/j.knosys.2004.03.001
* Misevičius A (2004) An improved hybrid optimization algorithm for the quadratic assignment problem. Mathematical Modelling and Analysis 9:149–168. https://doi.org/10.1080/13926292.2004.9637249
* Oliveira CAS, Pardalos PM, Resende MGC (2004) GRASP with Path-Relinking for the Quadratic Assignment Problem. In: Ribeiro CC, Martins SL (eds) Experimental and Efficient Algorithms. Springer, Berlin, Heidelberg, pp 356–368, https://doi.org/10.1007/978-3-540-24838-5_27
* Drezner Z (2003) A New Genetic Algorithm for the Quadratic Assignment Problem. INFORMS Journal on Computing
* Anstreicher KM (2003) Recent advances in the solution of quadratic assignment problems. Math Program, Ser B 97:27–42. https://doi.org/10.1007/s10107-003-0437-z
* Mills P, Tsang E, Ford J (2003) Applying an Extended Guided Local Search to the Quadratic Assignment Problem. Annals of Operations Research 118:121–135. https://doi.org/10.1023/A:1021857607524
* Misevičius A (2003) A Modified Simulated Annealing Algorithm for the Quadratic Assignment Problem. Informatica 14:497–514
* Angel E, Zissimopoulos V (2002) On the Hardness of the Quadratic Assignment Problem with Metaheuristics. Journal of Heuristics 8:399–414. https://doi.org/10.1023/A:1015454612213
* Hasegawa M, Ikeguchi T, Aihara K, Itoh K (2002) A novel chaotic search for quadratic assignment problems. European Journal of Operational Research 139:543–556. https://doi.org/10.1016/S0377-2217(01)00189-8
* Gutin G, Yeo A (2002) Polynomial approximation algorithms for the TSP and the QAP with a factorial domination number. Discrete Applied Mathematics 119:107–116. https://doi.org/10.1016/S0166-218X(01)00267-0
* Ramakrishnan KG, Resende MGC, Ramachandran B, Pekny JF (2002) Tight QAP bounds via linear programming. In: Combinatorial and Global Optimization. WORLD SCIENTIFIC, pp 297–303, https://doi.org/10.1142/9789812778215_0019
* Smith JM, Li W-J (2001) Quadratic Assignment Problems and M/G/C/C/ State Dependent Network Flows. Journal of Combinatorial Optimization 5:421–443. https://doi.org/10.1023/A:1011624708694
* Jünger M, Kaibel V (2001) Box-inequalities for quadratic assignment polytopes. Math Program 91:175–197. https://doi.org/10.1007/s101070100251
* Angel E, Zissimopoulos V (2001) On the landscape ruggedness of the quadratic assignment problem. Theoretical Computer Science 263:159–172. https://doi.org/10.1016/S0304-3975(00)00239-5
* Anstreicher KM, Brixius NW (2001) A new bound for the quadratic assignment problem based on convex quadratic programming. Math Program 89:341–357. https://doi.org/10.1007/PL00011402
* Talbi E-G, Roux O, Fonlupt C, Robillard D (2001) Parallel Ant Colonies for the quadratic assignment problem. Future Generation Computer Systems 17:441–449. https://doi.org/10.1016/S0167-739X(99)00124-7
* Nishiyama T, Tsuchiya K, Tsujita K (2001) A Markov Chain Monte Carlo Algorithm for the Quadratic Assignment Problem Based on Replicator Equations. In: Dorffner G, Bischof H, Hornik K (eds) Artificial Neural Networks — ICANN 2001. Springer, Berlin, Heidelberg, pp 148–155, https://doi.org/10.1007/3-540-44668-0_21
* Merz P, Freisleben B (2000) Fitness landscape analysis and memetic algorithms for the quadratic assignment problem. IEEE Transactions on Evolutionary Computation 4:337–352. https://doi.org/10.1109/4235.887234
* Ahuja RK, Orlin JB, Tiwari A (2000) A greedy genetic algorithm for the quadratic assignment problem. Computers & Operations Research 27:917–934. https://doi.org/10.1016/S0305-0548(99)00067-2
* De&ıbreve;neko VG, Woeginger GJ (2000) A study of exponential neighborhoods for the Travelling Salesman Problem and for the Quadratic Assignment Problem. Math Program 87:519–542. https://doi.org/10.1007/s101070050010
* Misevičius A (2000) An Intensive Search Algorithm for the Quadratic Assignment Problem. Informatica 11:145–162. https://doi.org/10.3233/INF-2000-11204
* Wolkowicz H (2000) Semidefinite Programming Approaches to the Quadratic Assignment Problem. In: Pardalos PM, Pitsoulis LS (eds) Nonlinear Assignment Problems: Algorithms and Applications. Springer US, Boston, MA, pp 143–174, https://doi.org/10.1007/978-1-4757-3155-2_7
* Karisch SE, Çela E, Clausen J, Espersen T (1999) A Dual Framework for Lower Bounds of the Quadratic Assignment Problem Based on Linearization. Computing 63:351–403. https://doi.org/10.1007/s006070050040
* Maniezzo V (1999) Exact and Approximate Nondeterministic Tree-Search Procedures for the Quadratic Assignment Problem. INFORMS Journal on Computing 11:358–369. https://doi.org/10.1287/ijoc.11.4.358
* Maniezzo V, Colorni A (1999) The ant system applied to the quadratic assignment problem. IEEE Transactions on Knowledge and Data Engineering 11:769–778. https://doi.org/10.1109/69.806935
* Gambardella LM, Taillard ÉD, Dorigo M (1999) Ant colonies for the quadratic assignment problem. Journal of the Operational Research Society 50:167–176. https://doi.org/10.1057/palgrave.jors.2600676
* Hahn P, Grant T (1998) Lower Bounds for the Quadratic Assignment Problem Based upon a Dual Formulation. Operations Research 46:912–922. https://doi.org/10.1287/opre.46.6.912
* Hahn P, Grant T, Hall N (1998) A branch-and-bound algorithm for the quadratic assignment problem based on the Hungarian method. European Journal of Operational Research 108:629–640. https://doi.org/10.1016/S0377-2217(97)00063-5
* Brüngger A, Marzetta A, Clausen J, Perregaard M (1998) Solving Large-Scale QAP Problems in Parallel with the Search Library ZRAM. Journal of Parallel and Distributed Computing 50:157–169. https://doi.org/10.1006/jpdc.1998.1434
* Zhao Q, Karisch SE, Rendl F, Wolkowicz H (1998) Semidefinite Programming Relaxations for the Quadratic Assignment Problem. Journal of Combinatorial Optimization 2:71–109. https://doi.org/10.1023/A:1009795911987
* Burkard RE, Karisch SE, Rendl F (1997) QAPLIB – A Quadratic Assignment Problem Library. Journal of Global Optimization 10:391–403. https://doi.org/10.1023/A:1008293323270
* Cung V-D, Mautor T, Michelon P, Tavares A (1997) A scatter search based approach for the quadratic assignment problem. In: Proceedings of 1997 IEEE International Conference on Evolutionary Computation (ICEC ’97). pp 165–169, https://doi.org/10.1109/ICEC.1997.592289
* Pardalos PM, Ramakrishnan KG, Resende MGC, Li Y (1997) Implementation of a Variance Reduction-Based Lower Bound in a Branch-and-Bound Algorithm for the Quadratic Assignment Problem. SIAM J Optim 7:280–294. https://doi.org/10.1137/S1052623494273393
* Ramakrishnan KG, Resende MGC, Pardalos PM (1996) A Branch and Bound Algorithm for the Quadratic Assignment Problem using a Lower Bound Based on Linear Programming. In: Floudas CA, Pardalos PM (eds) State of the Art in Global Optimization: Computational Methods and Applications. Springer US, Boston, MA, pp 57–73, https://doi.org/10.1007/978-1-4613-3437-8_5
* Bousoño-Calzón C, Manning MRW (1995) The Hopfield neural network applied to the Quadratic Assignment Problem. Neural Comput & Applic 3:64–72. https://doi.org/10.1007/BF01421958
* Nissen V, Paul H (1995) A modification of threshold accepting and its application to the quadratic assignment problem. OR Spektrum 17:205–210. https://doi.org/10.1007/BF01719267
* Drezner Z (1995) Lower bounds based on linear programming for the quadratic assignment problem. Comput Optim Applic 4:159–165. https://doi.org/10.1007/BF01302894
* Mans B, Mautor T, Roucairol C (1995) A parallel depth first search branch and bound algorithm for the quadratic assignment problem. European Journal of Operational Research 81:617–628. https://doi.org/10.1016/0377-2217(93)E0334-T
* Milis IZ, Magirou VF (1995) A Lagrangian relaxation algorithm for sparse quadratic assignment problems. Operations Research Letters 17:69–76. https://doi.org/10.1016/0167-6377(94)00061-A
* Maniezzo V, Dorigo M, Colorni A (1995) Algodesk: An experimental comparison of eight evolutionary heuristics applied to the Quadratic Assignment Problem. European Journal of Operational Research 81:188–204. https://doi.org/10.1016/0377-2217(93)E0128-K
* White DJ (1995) Some concave-convex representations of the quadratic assignment problem. European Journal of Operational Research 80:418–424. https://doi.org/10.1016/0377-2217(93)E0215-J
* Li Y, Pardalos PM, Ramakrishnan KG, Resende MGC (1994) Lower bounds for the quadratic assignment problem. Ann Oper Res 50:387–410. https://doi.org/10.1007/BF02085649
* Bos J (1993) Zoning in Forest Management: a Quadratic Assignment Problem Solved by Simulated Annealing. Journal of Environmental Management 37:127–145. https://doi.org/10.1006/jema.1993.1010
* Hadley SW, Rendl F, Wolkowicz H (1992) A New Lower Bound Via Projection for the Quadratic Assignment Problem. Mathematics of OR 17:727–739. https://doi.org/10.1287/moor.17.3.727
* Rendl F, Wolkowicz H (1992) Applications of parametric programming and eigenvalue maximization to the quadratic assignment problem. Mathematical Programming 53:63–78. https://doi.org/10.1007/BF01585694
* Taillard E (1991) Robust taboo search for the quadratic assignment problem. Parallel Computing 17:443–455. https://doi.org/10.1016/S0167-8191(05)80147-4
* Skorin-Kapov J (1990) Tabu Search Applied to the Quadratic Assignment Problem. ORSA Journal on Computing 2:33–45. https://doi.org/10.1287/ijoc.2.1.33
* Hadley SW, Rendl F, Wolkowicz H (1990) Bounds for the Quadratic Assignment Problems Using Continuous Optimization Techniques. In: IPCO. pp 237–248
* Wilhelm MR, Ward TL (1987) Solving Quadratic Assignment Problems by ‘Simulated Annealing.’ IIE Transactions 19:107–119. https://doi.org/10.1080/07408178708975376
* Finke G, Burkard RE, Rendl F (1987) Quadratic Assignment Problems. In: Martello S, Laporte G, Minoux M, Ribeiro C (eds) North-Holland Mathematics Studies. North-Holland, pp 61–82, https://doi.org/10.1016/S0304-0208(08)73232-8
* Kaku BK, Thompson GL (1986) An exact algorithm for the general quadratic assignment problem. European Journal of Operational Research 23:382–390. https://doi.org/10.1016/0377-2217(86)90303-6
* Burkard RE, Bönniger T (1983) A heuristic for quadratic Boolean programs with applications to quadratic assignment problems. European Journal of Operational Research 13:374–386. https://doi.org/10.1016/0377-2217(83)90097-8
* Bazaraa MS, Kirca O (1983) A branch-and-bound-based heuristic for solving the quadratic assignment problem. Naval Research Logistics Quarterly 30:287–304. https://doi.org/10.1002/nav.3800300210
* Frieze AM, Yadegar J (1983) On the quadratic assignment problem. Discrete applied mathematics 5:89–98
* Bazaraa MS, Sherali HD (1982) On the Use of Exact and Heuristic Cutting Plane Methods for the Quadratic Assignment Problem. J Oper Res Soc 33:991–1003. https://doi.org/10.1057/jors.1982.210
* Bazaraa MS, Elshafei AN (1979) An exact branch-and-bound procedure for the quadratic-assignment problem. Naval Research Logistics Quarterly 26:109–121. https://doi.org/10.1002/nav.3800260111
* Kaufman L, Broeckx F (1978) An algorithm for the quadratic assignment problem using Bender’s decomposition. European Journal of Operational Research 2:207–211. https://doi.org/10.1016/0377-2217(78)90095-4
* Elshafei AN (1977) Hospital Layout as a Quadratic Assignment Problem. J Oper Res Soc 28:167–179. https://doi.org/10.1057/jors.1977.29
* Lawler EL (1963) The Quadratic Assignment Problem. Management Science 9:586–599. https://doi.org/10.1287/mnsc.9.4.586
* Gilmore PC (1962) Optimal and Suboptimal Algorithms for the Quadratic Assignment Problem. Journal of the Society for Industrial and Applied Mathematics 10:305–313. https://doi.org/10.1137/0110022

</p>
</details>

* Data: [quadraticassignment.7z](https://github.com/fontanf/orproblems/releases/download/data/quadraticassignment.7z)


[Cutting Stock Problem](orproblems/cuttingstock.hpp)

<details><summary>Literature</summary>
<p>

* Coniglio S, D’Andreagiovanni F, Furini F (2019) A lexicographic pricer for the fractional bin packing problem. Operations Research Letters 47:622–628. https://doi.org/10.1016/j.orl.2019.10.011
* Wei L, Luo Z, Baldacci R, Lim A (2019) A New Branch-and-Price-and-Cut Algorithm for One-Dimensional Bin-Packing Problems. INFORMS Journal on Computing. https://doi.org/10.1287/ijoc.2018.0867
* Delorme M, Iori M (2019) Enhanced Pseudo-polynomial Formulations for Bin Packing and Cutting Stock Problems. INFORMS Journal on Computing. https://doi.org/10.1287/ijoc.2018.0880
* Delorme M, Iori M, Martello S (2016) Bin packing and cutting stock problems: Mathematical models and exact algorithms. European Journal of Operational Research 255:1–20. https://doi.org/10.1016/j.ejor.2016.04.030
* Brandão F, Pedroso JP (2016) Bin packing and related problems: General arc-flow formulation with graph compression. Computers & Operations Research 69:56–67. https://doi.org/10.1016/j.cor.2015.11.009
* Baldi MM, Crainic TG, Perboli G, Tadei R (2014) Branch-and-price and beam search algorithms for the Variable Cost and Size Bin Packing Problem with optional items. Ann Oper Res 222:125–141. https://doi.org/10.1007/s10479-012-1283-2
* Belov G, Scheithauer G (2006) A branch-and-cut-and-price algorithm for one-dimensional stock cutting and two-dimensional two-stage cutting. European Journal of Operational Research 171:85–106. https://doi.org/10.1016/j.ejor.2004.08.036
* Gilmore PC, Gomory RE (1961) A Linear Programming Approach to the Cutting-Stock Problem. Operations Research 9:849–859. https://doi.org/10.1287/opre.9.6.849

</p>
</details>

* Data: [cuttingstock.7z](https://github.com/fontanf/orproblems/releases/download/data/cuttingstock.7z)


[Multiple Knapsack Problem](orproblems/multipleknapsack.hpp)

<details><summary>Literature</summary>
<p>

* Dell’Amico M, Delorme M, Iori M, Martello S (2019) Mathematical models and decomposition methods for the multiple knapsack problem. European Journal of Operational Research 274:886–899. https://doi.org/10.1016/j.ejor.2018.10.043
* Laalaoui Y, M’Hallah R (2016) A binary multiple knapsack model for single machine scheduling with machine unavailability. Computers & Operations Research 72:71–82. https://doi.org/10.1016/j.cor.2016.02.005
* Laalaoui Y (2013) Improved Swap Heuristic for the Multiple Knapsack Problem. In: Rojas I, Joya G, Gabestany J (eds) Advances in Computational Intelligence. Springer, Berlin, Heidelberg, pp 547–555, https://doi.org/10.1007/978-3-642-38679-4_55
* Lalami ME, Elkihel M, El Baz D, Boyer V (2012) A procedure-based heuristic for 0-1 Multiple Knapsack Problems. International Journal of Mathematics in Operational Research 4:214–224. https://doi.org/10.1504/IJMOR.2012.046684
* Fukunaga AS (2011) A branch-and-bound algorithm for hard multiple knapsack problems. Ann Oper Res 184:97–119. https://doi.org/10.1007/s10479-009-0660-y
* Fukunaga AS, Tazoe S (2009) Combining multiple representations in a genetic algorithm for the multiple knapsack problem. In: 2009 IEEE Congress on Evolutionary Computation. pp 2423–2430, https://doi.org/10.1109/CEC.2009.4983244
* Fukunaga AS (2008) A new grouping genetic algorithm for the Multiple Knapsack Problem. In: 2008 IEEE Congress on Evolutionary Computation (IEEE World Congress on Computational Intelligence). pp 2225–2232, https://doi.org/10.1109/CEC.2008.4631094
* Fukunaga AS, Korf RE (2007) Bin Completion Algorithms for Multicontainer Packing, Knapsack, and Covering Problems. Journal of Artificial Intelligence Research 28:393–429. https://doi.org/10.1613/jair.2106
* Kellerer H, Pferschy U, Pisinger D (2004) Knapsack Problems. Springer Berlin Heidelberg, Berlin, Heidelberg
* Pisinger D (1999) An exact algorithm for large multiple knapsack problems. European Journal of Operational Research 114:528–541. https://doi.org/10.1016/S0377-2217(98)00120-9
* Martello S, Toth P (1990) Knapsack problems: algorithms and computer implementations. John Wiley & Sons, Inc.
* Martello S, Toth P (1981a) A Bound and Bound algorithm for the zero-one multiple knapsack problem. Discrete Applied Mathematics 3:275–288. https://doi.org/10.1016/0166-218X(81)90005-6
* Martello S, Toth P (1981b) Heuristische Algorithmen zur Packung von mehreren Rucksäcken. Computing 27:93–112. https://doi.org/10.1007/BF02243544
* Martello S, Toth P (1980) Solution of the zero-one multiple knapsack problem. European Journal of Operational Research 4:276–283. https://doi.org/10.1016/0377-2217(80)90112-5
* Hung MS, Fisk JC (1978) An algorithm for 0-1 multiple-knapsack problems. Naval Research Logistics Quarterly 25:571–579. https://doi.org/10.1002/nav.3800250316
* Ingargiola G, Korsh JF (1975) An Algorithm for the Solution of 0-1 Loading Problems. Operations Research 23:1110–1119. https://doi.org/10.1287/opre.23.6.1110

</p>
</details>

* Data: [multipleknapsack.7z](https://github.com/fontanf/orproblems/releases/download/data/multipleknapsack.7z)


[Quadratic Multiple Knapsack Problem](orproblems/quadraticmultipleknapsack.hpp)

<details><summary>Literature</summary>
<p>

* Fleszar K (2021) A Branch-and-Bound Algorithm for the Quadratic Multiple Knapsack Problem. European Journal of Operational Research. https://doi.org/10.1016/j.ejor.2021.06.018
* Galli L, Martello S, Rey C, Toth P (2021) Polynomial-size formulations and relaxations for the quadratic multiple knapsack problem. European Journal of Operational Research 291:871–882. https://doi.org/10.1016/j.ejor.2020.10.047
* Aïder M, Gacem O, Hifi M (2020) Branch and solve strategies-based algorithm for the quadratic multiple knapsack problem. Journal of the Operational Research Society 0:1–18. https://doi.org/10.1080/01605682.2020.1843982
* Bergman D (2019) An Exact Algorithm for the Quadratic Multiknapsack Problem with an Application to Event Seating. INFORMS Journal on Computing 31:477–492. https://doi.org/10.1287/ijoc.2018.0840
* Peng B, Liu M, Lü Z, et al (2016) An ejection chain approach for the quadratic multiple knapsack problem. European Journal of Operational Research 253:328–336. https://doi.org/10.1016/j.ejor.2016.02.043
* Qin J, Xu X, Wu Q, Cheng TCE (2016) Hybridization of tabu search with feasible and infeasible local searches for the quadratic multiple knapsack problem. Computers & Operations Research 66:199–214. https://doi.org/10.1016/j.cor.2015.08.002
* Chen Y, Hao J-K, Glover F (2016) An evolutionary path relinking approach for the quadratic multiple knapsack problem. Knowledge-Based Systems 92:23–34. https://doi.org/10.1016/j.knosys.2015.10.004
* Chen Y, Hao J-K (2015) Iterated responsive threshold search for the quadratic multiple knapsack problem. Ann Oper Res 226:101–131. https://doi.org/10.1007/s10479-014-1720-5
* García-Martínez C, Glover F, Rodriguez FJ, et al (2014a) Strategic oscillation for the quadratic multiple knapsack problem. Comput Optim Appl 58:161–185. https://doi.org/10.1007/s10589-013-9623-y
* García-Martínez C, Rodriguez FJ, Lozano M (2014b) Tabu-enhanced iterated greedy algorithm: A case study in the quadratic multiple knapsack problem. European Journal of Operational Research 232:454–463. https://doi.org/10.1016/j.ejor.2013.07.035
* Sundar S, Singh A (2010) A Swarm Intelligence Approach to the Quadratic Multiple Knapsack Problem. In: Wong KW, Mendis BSU, Bouzerdoum A (eds) Neural Information Processing. Theory and Algorithms. Springer, Berlin, Heidelberg, pp 626–633, https://doi.org/10.1007/978-3-642-17537-4_76
* Saraç T, Sipahioglu A (2007) A Genetic Algorithm for the Quadratic Multiple Knapsack Problem. In: Mele F, Ramella G, Santillo S, Ventriglia F (eds) Advances in Brain, Vision, and Artificial Intelligence. Springer, Berlin, Heidelberg, pp 490–498, https://doi.org/10.1007/978-3-540-75555-5_47
* Singh A, Baghel AS (2007) A New Grouping Genetic Algorithm for the Quadratic Multiple Knapsack Problem. In: Cotta C, van Hemert J (eds) Evolutionary Computation in Combinatorial Optimization. Springer, Berlin, Heidelberg, pp 210–218, https://doi.org/10.1007/978-3-540-71615-0_19
* Hiley A, Julstrom BA (2006) The quadratic multiple knapsack problem and three heuristic approaches to it. In: Proceedings of the 8th annual conference on Genetic and evolutionary computation. Association for Computing Machinery, New York, NY, USA, pp 547–552, https://doi.org/10.1145/1143997.1144096

</p>
</details>

* Data: [quadraticmultipleknapsack.7z](https://github.com/fontanf/orproblems/releases/download/data/quadraticmultipleknapsack.7z)


<!--
[Generalized Quadratic Multiple Knapsack Problem](orproblems/generalizedquadraticmultipleknapsack.hpp)

<details><summary>Literature</summary>
<p>

* Zhou Q, Hao J-K, Wu Q (2021) A hybrid evolutionary search for the generalized quadratic multiple knapsack problem. European Journal of Operational Research. https://doi.org/10.1016/j.ejor.2021.04.001
* Adouani Y, Jarboui B, Masmoudi M (2019) A matheuristic for the 0–1 generalized quadratic multiple knapsack problem. Optim Lett. https://doi.org/10.1007/s11590-019-01503-z
* Avci M, Topaloglu S (2017) A multi-start iterated local search algorithm for the generalized quadratic multiple knapsack problem. Computers & Operations Research 83:54–65. https://doi.org/10.1016/j.cor.2017.02.004
* Chen Y, Hao J-K (2016) Memetic Search for the Generalized Quadratic Multiple Knapsack Problem. IEEE Transactions on Evolutionary Computation 20:908–923. https://doi.org/10.1109/TEVC.2016.2546340
* Saraç T, Sipahioglu A (2014) Generalized quadratic multiple knapsack problem and two solution approaches. Computers & Operations Research 43:78–89. https://doi.org/10.1016/j.cor.2013.08.018

</p>
</details>


* Data: [generalizedquadraticmultipleknapsack.7z](https://github.com/fontanf/generalizedorproblems/releases/download/data/quadraticmultipleknapsack.7z)
-->


[Bin Packing Problem with Conflicts](orproblems/binpackingwithconflicts.hpp)

<details><summary>Literature</summary>
<p>

* Wei L, Luo Z, Baldacci R, Lim A (2019) A New Branch-and-Price-and-Cut Algorithm for One-Dimensional Bin-Packing Problems. INFORMS Journal on Computing. https://doi.org/10.1287/ijoc.2018.0867
* Brandão F, Pedroso JP (2016) Bin packing and related problems: General arc-flow formulation with graph compression. Computers & Operations Research 69:56–67. https://doi.org/10.1016/j.cor.2015.11.009
* Sadykov R, Vanderbeck F (2012) Bin Packing with Conflicts: A Generic Branch-and-Price Algorithm. INFORMS Journal on Computing 25:244–255. https://doi.org/10.1287/ijoc.1120.0499
* Elhedhli S, Li L, Gzara M, Naoum-Sawaya J (2010) A Branch-and-Price Algorithm for the Bin Packing Problem with Conflicts. INFORMS Journal on Computing 23:404–415. https://doi.org/10.1287/ijoc.1100.0406
* Muritiba AEF, Iori M, Malaguti E, Toth P (2010) Algorithms for the Bin Packing Problem with Conflicts. INFORMS J on Computing 22:401–415. https://doi.org/10.1287/ijoc.1090.0355

</p>
</details>

* Data: [binpackingwithconflicts.7z](https://github.com/fontanf/orproblems/releases/download/data/binpackingwithconflicts.7z)


## Routing


### Single vehicle


[Sequential Ordering Problem](orproblems/sequentialordering.hpp)
* Three field classification: `1 | sᵢⱼ, prec | Cₘₐₓ`

<details><summary>Literature</summary>
<p>

* Libralesso L, Bouhassoun A-M, Cambazard H, Jost V (2020) Tree Search for the Sequential Ordering Problem. In: ECAI 2020 - 24th European Conference on Artificial Intelligence, 29 August-8 September 2020, Santiago de Compostela, Spain, August 29 - September 8, 2020 - Including 10th Conference on Prestigious Applications of Artificial Intelligence (PAIS 2020). pp 459–465, https://doi.org/10.3233/FAIA200126
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


[Traveling salesman problem with release dates](orproblems/travelingsalesmanwithreleasedates.hpp)
* Release dates for the arrival of goods to the depot, the solution may require multiple trips.

<details><summary>Literature</summary>
<p>

* Archetti C, Feillet D, Mor A, Speranza MG (2018) An iterated local search for the Traveling Salesman Problem with release dates and completion time minimization. Computers & Operations Research 98:24–37. https://doi.org/10.1016/j.cor.2018.05.001

</p>
</details>

* Data: [travelingsalesmanwithreleasedates.7z](https://github.com/fontanf/orproblems/releases/download/data/travelingsalesmanwithreleasedates.7z)


[Traveling Repairman Problem / Minimum Latency Problem](orproblems/travelingrepairman.hpp)
* Three field classification: `1 | sᵢⱼ | ∑Cⱼ`

<details><summary>Literature</summary>
<p>

* Santana Í, Plastino A, Rosseti I (2022) Improving a state-of-the-art heuristic for the minimum latency problem with data mining. International Transactions in Operational Research 29:959–986. https://doi.org/10.1111/itor.12774
* Ramadhan F, Imran A (2019) A Two-Phase Metaheuristic Method for Solving Travelling Repairman Problem. In: 2019 International Conference on Sustainable Engineering and Creative Computing (ICSECC). pp 155–159, https://doi.org/10.1109/ICSECC.2019.8907032
* Bulhões T, Sadykov R, Uchoa E (2018) A branch-and-price algorithm for the Minimum Latency Problem. Computers & Operations Research 93:66–78. https://doi.org/10.1016/j.cor.2018.01.016
* Manerba D, Mansini R, Riera-Ledesma J (2017) The Traveling Purchaser Problem and its variants. European Journal of Operational Research 259:1–18. https://doi.org/10.1016/j.ejor.2016.12.017
* Ha BB, Duc NN (2013) A meta-heuristic algorithm combining between Tabu and Variable Neighborhood Search for the Minimum Latency Problem. In: The 2013 RIVF International Conference on Computing Communication Technologies - Research, Innovation, and Vision for Future (RIVF). pp 192–197, https://doi.org/10.1109/RIVF.2013.6719892
* Roberti R, Mingozzi A (2013) Dynamic ng-Path Relaxation for the Delivery Man Problem. Transportation Science 48:413–424. https://doi.org/10.1287/trsc.2013.0474
* Mladenović N, Urošević D, Hanafi S (2013) Variable neighborhood search for the travelling deliveryman problem. 4OR-Q J Oper Res 11:57–73. https://doi.org/10.1007/s10288-012-0212-1
* Angel-Bello F, Alvarez A, García I (2013) Two improved formulations for the minimum latency problem. Applied Mathematical Modelling 37:2257–2266. https://doi.org/10.1016/j.apm.2012.05.026
* Ban HB, Nguyen K, Ngo MC, Nguyen DN (2013) An efficient exact algorithm for Minimum Latency Problem. J PI 10:1–8
* Silva MM, Subramanian A, Vidal T, Ochi LS (2012) A simple and effective metaheuristic for the Minimum Latency Problem. European Journal of Operational Research 221:513–520. https://doi.org/10.1016/j.ejor.2012.03.044
* Salehipour A, Sörensen K, Goos P, Bräysy O (2011) Efficient GRASP+VND and GRASP+VNS metaheuristics for the traveling repairman problem. 4OR-Q J Oper Res 9:189–209. https://doi.org/10.1007/s10288-011-0153-0
* Ngueveu SU, Prins C, Wolfler Calvo R (2010) An effective memetic algorithm for the cumulative capacitated vehicle routing problem. Computers & Operations Research 37:1877–1885. https://doi.org/10.1016/j.cor.2009.06.014
* Bang BH, Nghia ND (2010) Improved genetic algorithm for minimum latency problem. In: Proceedings of the 2010 Symposium on Information and Communication Technology. Association for Computing Machinery, New York, NY, USA, pp 9–15, https://doi.org/10.1145/1852611.1852614
* Chaudhuri K, Godfrey B, Rao S, Talwar K (2003) Paths, trees, and minimum latency tours. In: 44th Annual IEEE Symposium on Foundations of Computer Science, 2003. Proceedings. pp 36–45, https://doi.org/10.1109/SFCS.2003.1238179
* Goemans M, Kleinberg J (1998) An improved approximation ratio for the minimum latency problem. Mathematical Programming 82:111–124. https://doi.org/10.1007/BF01585867
* Blum A, Chalasani P, Coppersmith D, et al (1994) The minimum latency problem. In: Proceedings of the twenty-sixth annual ACM symposium on Theory of Computing. Association for Computing Machinery, New York, NY, USA, pp 163–171, https://doi.org/10.1145/195058.195125
* Fischetti M, Laporte G, Martello S (1993) The Delivery Man Problem and Cumulative Matroids. Operations Research 41:1055–1064. https://doi.org/10.1287/opre.41.6.1055

</p>
</details>

* Data: [travelingrepairman.7z](https://github.com/fontanf/orproblems/releases/download/data/travelingrepairman.7z)


[Time-dependent orienteering problem](orproblems/timedependentorienteering.hpp)

<details><summary>Literature</summary>
<p>

* Ostrowski K (2017) Evolutionary Algorithm for the Time-Dependent Orienteering Problem. In: Saeed K, Homenda W, Chaki R (eds) Computer Information Systems and Industrial Management. Springer International Publishing, Cham, pp 50–62, https://doi.org/10.1007/978-3-319-59105-6_5
* Verbeeck C, Sörensen K, Aghezzaf E-H, Vansteenwegen P (2014) A fast solution method for the time-dependent orienteering problem. European Journal of Operational Research 236:419–432. https://doi.org/10.1016/j.ejor.2013.11.038
* Gunawan A, Yuan Z, Lau HC (2014) A mathematical model and metaheuristics for time dependent orienteering problem. In: PATAT 2014: Proceedings of the 10th International Conference of the Practice and Theory of Automated Timetabling, 26-29 August 2014. PATAT
* Abbaspour RA, Samadzadegan F (2011) Time-dependent personal tour planning and scheduling in metropolises. Expert Systems with Applications 38:12439–12452. https://doi.org/10.1016/j.eswa.2011.04.025
* Li J, Wu Q, Li X, Zhu D (2010) Study on the Time-Dependent Orienteering Problem. In: 2010 International Conference on E-Product E-Service and E-Entertainment. pp 1–4, https://doi.org/10.1109/ICEEE.2010.5660232
* Fomin FV, Lingas A (2002) Approximation algorithms for time-dependent orienteering. Information Processing Letters 83:57–62. https://doi.org/10.1016/S0020-0190(01)00313-1

</p>
</details>

* Data: [timedependentorienteering.7z](https://github.com/fontanf/orproblems/releases/download/data/timedependentorienteering.7z)


[Orienteering problem with hotel selection](orproblems/orienteeringwithhotelselection.hpp)

<details><summary>Literature</summary>
<p>

* Sohrabi S, Ziarati K, Keshtkaran M (2021) ACS-OPHS: Ant Colony System for the Orienteering Problem with Hotel Selection. EURO Journal on Transportation and Logistics 100036. https://doi.org/10.1016/j.ejtl.2021.100036
* Sohrabi S, Ziarati K, Keshtkaran M (2020) A Greedy Randomized Adaptive Search Procedure for the Orienteering Problem with Hotel Selection. European Journal of Operational Research 283:426–440. https://doi.org/10.1016/j.ejor.2019.11.010
* Toledo A, Riff MC (2015) HOPHS: A hyperheuristic that solves orienteering problem with hotel selection. In: 2015 Fifth International Conference on Digital Information Processing and Communications (ICDIPC). pp 148–152, https://doi.org/10.1109/ICDIPC.2015.7323021
* Divsalar A, Vansteenwegen P, Sörensen K, Cattrysse D (2014) A memetic algorithm for the orienteering problem with hotel selection. European Journal of Operational Research 237:29–49. https://doi.org/10.1016/j.ejor.2014.01.001
* Divsalar A, Vansteenwegen P, Cattrysse D (2013) A variable neighborhood search method for the orienteering problem with hotel selection. International Journal of Production Economics 145:150–160. https://doi.org/10.1016/j.ijpe.2013.01.010

</p>
</details>

* Data: [orienteeringwithhotelselection.7z](https://github.com/fontanf/orproblems/releases/download/data/orienteeringwithhotelselection.7z)


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


## Scheduling


### Single machine scheduling


[Single machine scheduling problem with sequence-dependent setup times, Total weighted tardiness](orproblems/schedulingwithsdsttwt.hpp)
* Three field classification: `1 | sᵢⱼ | ∑wⱼTⱼ`

<details><summary>Literature</summary>
<p>

* Subramanian A, Farias K (2017) Efficient local search limitation strategy for single machine total weighted tardiness scheduling with sequence-dependent setup times. Computers & Operations Research 79:190–206. https://doi.org/10.1016/j.cor.2016.10.008
* Xu H, Lü Z, Yin A, et al (2014a) A study of hybrid evolutionary algorithms for single machine scheduling problem with sequence-dependent setup times. Computers & Operations Research 50:47–60. https://doi.org/10.1016/j.cor.2014.04.009
* Xu H, Lü Z, Cheng TCE (2014b) Iterated Local Search for single-machine scheduling with sequence-dependent setup times to minimize total weighted tardiness. J Sched 17:271–287. https://doi.org/10.1007/s10951-013-0351-z
* Subramanian A, Battarra M, Potts CN (2014) An Iterated Local Search heuristic for the single machine total weighted tardiness scheduling problem with sequence-dependent setup times. International Journal of Production Research 52:2729–2742. https://doi.org/10.1080/00207543.2014.883472
* Deng G, Gu X (2014) An iterated greedy algorithm for the single-machine total weighted tardiness problem with sequence-dependent setup times. International Journal of Systems Science 45:351–362. https://doi.org/10.1080/00207721.2012.723054
* Tanaka S, Araki M (2013) An exact algorithm for the single-machine total weighted tardiness problem with sequence-dependent setup times. Computers & Operations Research 40:344–352. https://doi.org/10.1016/j.cor.2012.07.004
* Sioud A, Gravel M, Gagné C (2012) A hybrid genetic algorithm for the single machine scheduling problem with sequence-dependent setup times. Computers & Operations Research 39:2415–2424. https://doi.org/10.1016/j.cor.2011.12.017
* Chao C-W, Liao C-J (2012) A discrete electromagnetism-like mechanism for single machine total weighted tardiness problem with sequence-dependent setup times. Applied Soft Computing 12:3079–3087. https://doi.org/10.1016/j.asoc.2012.05.017
* Kirlik G, Oguz C (2012) A variable neighborhood search for minimizing total weighted tardiness with sequence dependent setup times on a single machine. Computers & Operations Research 39:1506–1520. https://doi.org/10.1016/j.cor.2011.08.022
* Liao C-J, Tsou H-H, Huang K-L (2012) Neighborhood search procedures for single machine tardiness scheduling with sequence-dependent setups. Theoretical Computer Science 434:45–52. https://doi.org/10.1016/j.tcs.2012.01.043
* Bożejko W (2010) Parallel path relinking method for the single machine total weighted tardiness problem with sequence-dependent setups. J Intell Manuf 21:777–785. https://doi.org/10.1007/s10845-009-0253-2
* Tasgetiren MF, Pan Q-K, Liang Y-C (2009) A discrete differential evolution algorithm for the single machine total weighted tardiness problem with sequence dependent setup times. Computers & Operations Research 36:1900–1915. https://doi.org/10.1016/j.cor.2008.06.007
* Anghinolfi D, Paolucci M (2009) A new discrete particle swarm optimization approach for the single-machine total weighted tardiness scheduling problem with sequence-dependent setup times. European Journal of Operational Research 193:73–85. https://doi.org/10.1016/j.ejor.2007.10.044
* Valente JMS, Alves RAFS (2008) Beam search algorithms for the single machine total weighted tardiness scheduling problem with sequence-dependent setups. Computers & Operations Research 35:2388–2405. https://doi.org/10.1016/j.cor.2006.11.004
* Lin S-W, Ying K-C (2007) Solving single-machine total weighted tardiness problems with sequence-dependent setup times by meta-heuristics. Int J Adv Manuf Technol 34:1183–1190. https://doi.org/10.1007/s00170-006-0693-1
* Liao C-J, Juan H-C (2007) An ant colony optimization for single-machine tardiness scheduling with sequence-dependent setups. Computers & Operations Research 34:1899–1909. https://doi.org/10.1016/j.cor.2005.07.020
* Cicirello VA (2006) Non-wrapping order crossover: an order preserving crossover operator that respects absolute position. In: Proceedings of the 8th annual conference on Genetic and evolutionary computation. Association for Computing Machinery, New York, NY, USA, pp 1125–1132, https://doi.org/10.1145/1143997.1144177
* Cicirello VA, Smith SF (2005) Enhancing Stochastic Search Performance by Value-Biased Randomization of Heuristics. J Heuristics 11:5–34. https://doi.org/10.1007/s10732-005-6997-8
* LEE YH, BHASKARAN K, PINEDO M (1997) A heuristic to minimize the total weighted tardiness with sequence-dependent setups. IIE Transactions 29:45–52. https://doi.org/10.1080/07408179708966311
* Raman N, Rachamadugu RV, Talbot FB (1989) Real-time scheduling of an automated manufacturing center. European Journal of Operational Research 40:222–242. https://doi.org/10.1016/0377-2217(89)90332-9

</p>
</details>

* Data: [schedulingwithsdsttwt.7z](https://github.com/fontanf/orproblems/releases/download/data/schedulingwithsdsttwt.7z)


[Single machine order acceptance and scheduling problem with time windows and sequence-dependent setup times, Total weighted tardiness](orproblems/orderacceptanceandscheduling.hpp)
* Three field classification: `1 | rⱼ, sᵢⱼ, reject, đⱼ | ∑wⱼTⱼ - ∑vⱼ`

<details><summary>Literature</summary>
<p>

* Tarhan İ, Oğuz C (2021) A Matheuristic for the Generalized Order Acceptance and Scheduling Problem. European Journal of Operational Research. https://doi.org/10.1016/j.ejor.2021.08.024
* Weerdt M de, Baart R, He L (2020) Single-Machine Scheduling with Release Times, Deadlines, Setup Times, and Rejection. European Journal of Operational Research. https://doi.org/10.1016/j.ejor.2020.09.042
* He L, Guijt A, de Weerdt M, et al (2019a) Order acceptance and scheduling with sequence-dependent setup times: A new memetic algorithm and benchmark of the state of the art. Computers & Industrial Engineering 138:106102. https://doi.org/10.1016/j.cie.2019.106102
* He L, de Weerdt M, Yorke-Smith N (2019b) Tabu-based large neighbourhood search for time/sequence-dependent scheduling problems with time windows. In: Proceedings of the International Conference on Automated Planning and Scheduling. pp 186–194
* Silva YLTV, Subramanian A, Pessoa AA (2018) Exact and heuristic algorithms for order acceptance and scheduling with sequence-dependent setup times. Computers & Operations Research 90:142–160. https://doi.org/10.1016/j.cor.2017.09.006
* Chaurasia SN, Singh A (2017) Hybrid evolutionary approaches for the single machine order acceptance and scheduling problem. Applied Soft Computing 52:725–747. https://doi.org/10.1016/j.asoc.2016.09.051
* Cesaret B, Oğuz C, Sibel Salman F (2012) A tabu search algorithm for order acceptance and scheduling. Computers & Operations Research 39:1197–1205. https://doi.org/10.1016/j.cor.2010.09.018

</p>
</details>

* Data: [orderacceptanceandscheduling.7z](https://github.com/fontanf/orproblems/releases/download/data/orderacceptanceandscheduling.7z)


[Single machine batch scheduling problem, Total completion time](orproblems/batchschedulingtotalcompletiontime.hpp)
* Three field classification: `1 | batch, sⱼ | ∑Cⱼ`

<details><summary>Literature</summary>
<p>

* Alfieri A, Druetto A, Grosso A, Salassa F (2021) Column generation for minimizing total completion time in a parallel-batching environment. J Sched. https://doi.org/10.1007/s10951-021-00703-9
* Parsa NR, Keshavarz T, Karimi B, Husseini SMM (2021) A hybrid neural network approach to minimize total completion time on a single batch processing machine. International Transactions in Operational Research 28:2867–2899. https://doi.org/10.1111/itor.12665
* Rafiee Parsa N, Karimi B, Moattar Husseini SM (2016) Minimizing total flow time on a batch processing machine using a hybrid max–min ant system. Computers & Industrial Engineering 99:372–381. https://doi.org/10.1016/j.cie.2016.06.008

</p>
</details>

* Data: [batchschedulingtotalcompletiontime.7z](https://github.com/fontanf/orproblems/releases/download/data/batchschedulingtotalcompletiontime.7z)


[Single machine batch scheduling problem, Total weighted tardiness](orproblems/batchschedulingtotalweightedtardiness.hpp)
* Three field classification: `1 | batch, rⱼ, sⱼ, compt | ∑wⱼTⱼ`

<details><summary>Literature</summary>
<p>

* Queiroga E, Pinheiro RGS, Christ Q, et al (2020) Iterated local search for single machine total weighted tardiness batch scheduling. J Heuristics. https://doi.org/10.1007/s10732-020-09461-x
* Wang H-M (2011) Solving single batch-processing machine problems using an iterated heuristic. International Journal of Production Research 49:4245–4261. https://doi.org/10.1080/00207543.2010.518995
* Mathirajan M, Bhargav V, Ramachandran V (2010) Minimizing total weighted tardiness on a batch-processing machine with non-agreeable release times and due dates. Int J Adv Manuf Technol 48:1133–1148. https://doi.org/10.1007/s00170-009-2342-y
* Chou F-D, Wang H-M (2008) Scheduling for a Single Semiconductor Batch-Processing Machine to Minimize Total Weighted Tardiness. Journal of the Chinese Institute of Industrial Engineers 25:136–147. https://doi.org/10.1080/10170660809509079

</p>
</details>

* Data: [batchschedulingtotalweightedtardiness.7z](https://github.com/fontanf/orproblems/releases/download/data/batchschedulingtotalweightedtardiness.7z)


### (Unrelated) parallel machine scheduling


[Identical parallel machine scheduling problem with family setup times, Total weighted completion time](orproblems/parallelschedulingwithfamilysetuptimestwct.hpp)
* Three field classification: `P | sᵢ | ∑wⱼCⱼ`

<details><summary>Literature</summary>
<p>

* Kramer A, Iori M, Lacomme P (2021) Mathematical formulations for scheduling jobs on identical parallel machines with family setup times and total weighted completion time minimization. European Journal of Operational Research 289:825–840. https://doi.org/10.1016/j.ejor.2019.07.006
* Liao C-J, Chao C-W, Chen L-C (2012) An improved heuristic for parallel machine weighted flowtime scheduling with family set-up times. Computers & Mathematics with Applications 63:110–117. https://doi.org/10.1016/j.camwa.2011.10.077
* Dunstall S, Wirth A (2005) Heuristic methods for the identical parallel machine flowtime problem with set-up times. Computers & Operations Research 32:2479–2491. https://doi.org/10.1016/j.cor.2004.03.013

</p>
</details>

* Data: [parallelschedulingwithfamilysetuptimestwct.7z](https://github.com/fontanf/orproblems/releases/download/data/parallelschedulingwithfamilysetuptimestwct.7z)


### Flow shop scheduling


[Permutation flow shop scheduling problem, Makespan](orproblems/permutationflowshopschedulingmakespan.hpp)
* Three field classification: `Fm | prmu | Cₘₐₓ`

<details><summary>Literature</summary>
<p>

* Libralesso L, Focke PA, Secardin A, Jost V (2021) Iterative beam search algorithms for the permutation flowshop. European Journal of Operational Research. https://doi.org/10.1016/j.ejor.2021.10.015
* Baskar A, Xavior MA (2021) New idle time-based tie-breaking rules in heuristics for the permutation flowshop scheduling problems. Computers & Operations Research 105348. https://doi.org/10.1016/j.cor.2021.105348
* Puka R, Duda J, Stawowy A, Skalna I (2021) N-NEH+ algorithm for solving permutation flow shop problems. Computers & Operations Research 105296. https://doi.org/10.1016/j.cor.2021.105296
* Kurdi M (2020) A memetic algorithm with novel semi-constructive evolution operators for permutation flowshop scheduling problem. Applied Soft Computing 94:106458. https://doi.org/10.1016/j.asoc.2020.106458
* Gmys J, Mezmaz M, Melab N, Tuyttens D (2020) A computationally efficient Branch-and-Bound algorithm for the permutation flow-shop scheduling problem. European Journal of Operational Research 284:814–833. https://doi.org/10.1016/j.ejor.2020.01.039
* Fernandez-Viagas V, Framinan JM (2019) A best-of-breed iterated greedy for the permutation flowshop scheduling problem with makespan objective. Computers & Operations Research 104767. https://doi.org/10.1016/j.cor.2019.104767
* Kizilay D, Tasgetiren MF, Pan Q-K, Gao L (2019) A Variable Block Insertion Heuristic for Solving Permutation Flow Shop Scheduling Problem with Makespan Criterion. Algorithms 12:100. https://doi.org/10.3390/a12050100
* Fernandez-Viagas V, Ruiz R, Framinan JM (2017) A new vision of approximate methods for the permutation flowshop to minimise makespan: State-of-the-art and computational evaluation. European Journal of Operational Research 257:707–721. https://doi.org/10.1016/j.ejor.2016.09.055
* Juan AA, Lourenço HR, Mateo M, et al (2014) Using iterated local search for solving the flow-shop problem: Parallelization, parametrization, and randomization issues. International Transactions in Operational Research 21:103–126. https://doi.org/10.1111/itor.12028
* Vallada E, Ruiz R (2009) Cooperative metaheuristics for the permutation flowshop scheduling problem. European Journal of Operational Research 193:365–376. https://doi.org/10.1016/j.ejor.2007.11.049
* Ruiz R, Stützle T (2007) A simple and effective iterated greedy algorithm for the permutation flowshop scheduling problem. European Journal of Operational Research 177:2033–2049. https://doi.org/10.1016/j.ejor.2005.12.009
* Ruiz R, Maroto C, Alcaraz J (2006) Two new robust genetic algorithms for the flowshop scheduling problem. Omega 34:461–476. https://doi.org/10.1016/j.omega.2004.12.006
* Zheng D-Z, Wang L (2003) An Effective Hybrid Heuristic for Flow Shop Scheduling. Int J Adv Manuf Technol 21:38–44. https://doi.org/10.1007/s001700300005
* Taillard E (1990) Some efficient heuristic methods for the flow shop sequencing problem. European Journal of Operational Research 47:65–74. https://doi.org/10.1016/0377-2217(90)90090-X
* Nawaz M, Enscore EE, Ham I (1983) A heuristic algorithm for the m-machine, n-job flow-shop sequencing problem. Omega 11:91–95. https://doi.org/10.1016/0305-0483(83)90088-9

</p>
</details>

* Data: [flowshopscheduling.7z](https://github.com/fontanf/orproblems/releases/download/data/flowshopscheduling.7z)


[Permutation flow shop scheduling problem, Total completion time](orproblems/permutationflowshopschedulingtct.hpp)
* Three field classification: `Fm | prmu | ∑Cⱼ`

<details><summary>Literature</summary>
<p>

* Libralesso L, Focke PA, Secardin A, Jost V (2021) Iterative beam search algorithms for the permutation flowshop. European Journal of Operational Research. https://doi.org/10.1016/j.ejor.2021.10.015
* Andrade CE, Silva T, Pessoa LS (2019) Minimizing flowtime in a flowshop scheduling problem with a biased random-key genetic algorithm. Expert Systems with Applications 128:67–80. https://doi.org/10.1016/j.eswa.2019.03.007
* Fernandez-Viagas V, Framinan JM (2017) A beam-search-based constructive heuristic for the PFSP to minimise total flowtime. Computers & Operations Research 81:167–177. https://doi.org/10.1016/j.cor.2016.12.020
* Fernandez-Viagas V, Framinan JM (2015) A new set of high-performing heuristics to minimise flowtime in permutation flowshops. Computers & Operations Research 53:68–80. https://doi.org/10.1016/j.cor.2014.08.004
* Dong X, Chen P, Huang H, Nowak M (2013) A multi-restart iterated local search algorithm for the permutation flow shop problem minimizing total flow time. Computers & Operations Research 40:627–632. https://doi.org/10.1016/j.cor.2012.08.021
* Pan Q-K, Ruiz R (2013) A comprehensive review and evaluation of permutation flowshop heuristics to minimize flowtime. Computers & Operations Research 40:117–128. https://doi.org/10.1016/j.cor.2012.05.018
* Pan Q-K, Ruiz R (2012) Local search methods for the flowshop scheduling problem with flowtime minimization. European Journal of Operational Research 222:31–43. https://doi.org/10.1016/j.ejor.2012.04.034
* Dong X, Huang H, Chen P (2009) An iterated local search algorithm for the permutation flowshop problem with total flowtime criterion. Computers & Operations Research 36:1664–1669. https://doi.org/10.1016/j.cor.2008.04.001
* Liu J, Reeves CR (2001) Constructive and composite heuristic solutions to the P//∑Ci scheduling problem. European Journal of Operational Research 132:439–452. https://doi.org/10.1016/S0377-2217(00)00137-5

</p>
</details>

* Data: [flowshopscheduling.7z](https://github.com/fontanf/orproblems/releases/download/data/flowshopscheduling.7z)


[Permutation flow shop scheduling problem, Total tardiness](orproblems/permutationflowshopschedulingtt.hpp)
* Three field classification: `Fm | prmu | ∑Tⱼ`

<details><summary>Literature</summary>
<p>

* Fernandez-Viagas V, Valente JMS, Framinan JM (2018) Iterated-greedy-based algorithms with beam search initialization for the permutation flowshop to minimise total tardiness. Expert Systems with Applications 94:58–69. https://doi.org/10.1016/j.eswa.2017.10.050
* Ta QC, Billaut J-C, Bouquard J-L (2018) Matheuristic algorithms for minimizing total tardiness in the m-machine flow-shop scheduling problem. J Intell Manuf 29:617–628. https://doi.org/10.1007/s10845-015-1046-4
* Karabulut K (2016) A hybrid iterated greedy algorithm for total tardiness minimization in permutation flowshops. Computers & Industrial Engineering 98:300–307. https://doi.org/10.1016/j.cie.2016.06.012
* Li X, Chen L, Xu H, Gupta JND (2015) Trajectory Scheduling Methods for minimizing total tardiness in a flowshop. Operations Research Perspectives 2:13–23. https://doi.org/10.1016/j.orp.2014.12.001
* Fernandez-Viagas V, Framinan JM (2015) NEH-based heuristics for the permutation flowshop scheduling problem to minimise total tardiness. Computers & Operations Research 60:27–36. https://doi.org/10.1016/j.cor.2015.02.002
* Cura T (2015) An evolutionary algorithm for the permutation flowshop scheduling problem with total tardiness criterion. International Journal of Operational Research 22:366–384. https://doi.org/10.1504/IJOR.2015.068287
* Vallada E, Ruiz R (2010) Genetic algorithms with path relinking for the minimum tardiness permutation flowshop problem. Omega 38:57–67. https://doi.org/10.1016/j.omega.2009.04.002
* Vallada E, Ruiz R (2009) Cooperative metaheuristics for the permutation flowshop scheduling problem. European Journal of Operational Research 193:365–376. https://doi.org/10.1016/j.ejor.2007.11.049
* Framinan JM, Leisten R (2008) Total tardiness minimization in permutation flow shops: a simple approach based on a variable greedy algorithm. International Journal of Production Research 46:6479–6498. https://doi.org/10.1080/00207540701418960
* Vallada E, Ruiz R, Minella G (2008) Minimising total tardiness in the m-machine flowshop problem: A review and evaluation of heuristics and metaheuristics. Computers & Operations Research 35:1350–1373. https://doi.org/10.1016/j.cor.2006.08.016
* Armentano VA, Ronconi DP (1999) Tabu search for total tardiness minimization in flowshop scheduling problems. Computers & Operations Research 26:219–235. https://doi.org/10.1016/S0305-0548(98)00060-4
* Kim Y-D (1993) Heuristics for Flowshop Scheduling Problems Minimizing Mean Tardiness. J Oper Res Soc 44:19–28. https://doi.org/10.1057/jors.1993.3

</p>
</details>

* Data: [flowshopscheduling.7z](https://github.com/fontanf/orproblems/releases/download/data/flowshopscheduling.7z)


[Distributed permutation flow shop scheduling problem, Makespan](orproblems/distributedpfssmakespan.hpp)
* Three field classification: `DFm | prmu | Cₘₐₓ`

<details><summary>Literature</summary>
<p>

* Ruiz R, Pan Q-K, Naderi B (2019) Iterated Greedy methods for the distributed permutation flowshop scheduling problem. Omega 83:213–222. https://doi.org/10.1016/j.omega.2018.03.004
* Fernandez-Viagas V, Framinan JM (2015) A bounded-search iterated greedy algorithm for the distributed permutation flowshop scheduling problem. International Journal of Production Research 53:1111–1123. https://doi.org/10.1080/00207543.2014.948578
* Naderi B, Ruiz R (2014) A scatter search algorithm for the distributed permutation flowshop scheduling problem. European Journal of Operational Research 239:323–334. https://doi.org/10.1016/j.ejor.2014.05.024
* Xu Y, Wang L, Wang S, Liu M (2014) An effective hybrid immune algorithm for solving the distributed permutation flow-shop scheduling problem. Engineering Optimization 46:1269–1283. https://doi.org/10.1080/0305215X.2013.827673
* Wang S, Wang L, Liu M, Xu Y (2013) An effective estimation of distribution algorithm for solving the distributed permutation flow-shop scheduling problem. International Journal of Production Economics 145:387–396. https://doi.org/10.1016/j.ijpe.2013.05.004
* Lin S-W, Ying K-C, Huang C-Y (2013) Minimising makespan in distributed permutation flowshops using a modified iterated greedy algorithm. International Journal of Production Research 51:5029–5038. https://doi.org/10.1080/00207543.2013.790571
* Gao J, Chen R, Deng W (2013) An efficient tabu search algorithm for the distributed permutation flowshop scheduling problem. International Journal of Production Research 51:641–651. https://doi.org/10.1080/00207543.2011.644819
* Gao J, Chen R (2011) A hybrid genetic algorithm for the distributed permutation flowshop scheduling problem. International Journal of Computational Intelligence Systems 4:497–508. https://doi.org/10.1080/18756891.2011.9727808
* Naderi B, Ruiz R (2010) The distributed permutation flowshop scheduling problem. Computers & Operations Research 37:754–768. https://doi.org/10.1016/j.cor.2009.06.019

</p>
</details>

* Data: [flowshopscheduling.7z](https://github.com/fontanf/orproblems/releases/download/data/flowshopscheduling.7z)


[Distributed permutation flow shop scheduling problem, Total completion time](orproblems/distributedpfsstct.hpp)
* Three field classification: `DFm | prmu | ∑Cⱼ`

<details><summary>Literature</summary>
<p>

* Pan Q-K, Gao L, Wang L, et al (2019) Effective heuristics and metaheuristics to minimize total flowtime for the distributed permutation flowshop problem. Expert Systems with Applications 124:309–324. https://doi.org/10.1016/j.eswa.2019.01.062
* Fernandez-Viagas V, Perez-Gonzalez P, Framinan JM (2018) The distributed permutation flow shop to minimise the total flowtime. Computers & Industrial Engineering 118:464–477. https://doi.org/10.1016/j.cie.2018.03.014

</p>
</details>

* Data: [flowshopscheduling.7z](https://github.com/fontanf/orproblems/releases/download/data/flowshopscheduling.7z)


### Job shop scheduling


[No-wait job shop scheduling problem, Makespan](orproblems/nowaitjobshopschedulingmakespan.hpp)
* Three field classification: `Jm | no-wait | Cₘₐₓ`

<details><summary>Literature</summary>
<p>

* Ozolins A (2020) A new exact algorithm for no-wait job shop problem to minimize makespan. Oper Res Int J 20:2333–2363. https://doi.org/10.1007/s12351-018-0414-1
* Ying K-C, Lin S-W (2020) Solving no-wait job-shop scheduling problems using a multi-start simulated annealing with bi-directional shift timetabling algorithm. Computers & Industrial Engineering 146:106615. https://doi.org/10.1016/j.cie.2020.106615
* Valenzuela VM, Brizuela CA, Cosío-León M, Romero-Ocaño AD (2019) A combination of two simple decoding strategies for the no-wait job shop scheduling problem. In: Proceedings of the Genetic and Evolutionary Computation Conference. Association for Computing Machinery, New York, NY, USA, pp 864–871, https://doi.org/10.1145/3321707.3321870
* Chaurasia SN, Sundar S, Jung D, et al (2019) An Evolutionary Algorithm Based Hyper-heuristic for the Job-Shop Scheduling Problem with No-Wait Constraint. In: Yadav N, Yadav A, Bansal JC, et al. (eds) Harmony Search and Nature Inspired Optimization Algorithms. Springer, Singapore, pp 249–257, https://doi.org/10.1007/978-981-13-0761-4_25
* Sundar S, Suganthan PN, Jin CT, et al (2017) A hybrid artificial bee colony algorithm for the job-shop scheduling problem with no-wait constraint. Soft Comput 21:1193–1202. https://doi.org/10.1007/s00500-015-1852-9
* Li X, Xu H, Li M (2016) A memory-based complete local search method with variable neighborhood structures for no-wait job shops. Int J Adv Manuf Technol 87:1401–1408. https://doi.org/10.1007/s00170-013-4866-4
* AitZai A, Benmedjdoub B, Boudhar M (2016) Branch-and-bound and PSO algorithms for no-wait job shop scheduling. J Intell Manuf 27:679–688. https://doi.org/10.1007/s10845-014-0906-7
* Wang YM, Yin HL (2015) Algorithm based on K-neighborhood search for no-wait job shop scheduling problems. In: The 27th Chinese Control and Decision Conference (2015 CCDC). pp 4221–4225, https://doi.org/10.1109/CCDC.2015.7162672
* Bürgy R, Gröflin H (2013) Optimal job insertion in the no-wait job shop. J Comb Optim 26:345–371. https://doi.org/10.1007/s10878-012-9466-y
* Zhu J, Li X (2012) An Effective Meta-Heuristic for No-Wait Job Shops to Minimize Makespan. IEEE Transactions on Automation Science and Engineering 9:189–198. https://doi.org/10.1109/TASE.2011.2163305
* Bożejko W, Makuchowski M (2011) Solving the no-wait job-shop problem by using genetic algorithm with automatic adjustment. Int J Adv Manuf Technol 57:735–752. https://doi.org/10.1007/s00170-011-3297-3
* Santosa B, Budiman MA, Wiratno SE (2011) A Cross Entropy-Genetic Algorithm for m-Machines No-Wait Job-ShopScheduling Problem. Journal of Intelligent Learning Systems and Applications 3:171–180. https://doi.org/10.4236/jilsa.2011.33018
* Vermeulen HM, Hoogeveen JA, van den Akker JM (2011) Solving the no-wait job shop problem: an ILP and CP approach. CPAIOR 2011 Late Breaking Abstracts 44:
* Zhu J, Li X, Wang Q (2009) Complete local search with limited memory algorithm for no-wait job shops to minimize makespan. European Journal of Operational Research 198:378–386. https://doi.org/10.1016/j.ejor.2008.09.015
* Bożejko W, Makuchowski M (2009) A fast hybrid tabu search algorithm for the no-wait job shop problem. Computers & Industrial Engineering 56:1502–1509. https://doi.org/10.1016/j.cie.2008.09.023
* Pan JC-H, Huang H-C (2009) A hybrid genetic algorithm for no-wait job shop scheduling problems. Expert Systems with Applications 36:5800–5806. https://doi.org/10.1016/j.eswa.2008.07.005
* van den Broek JJJ (2009) MIP-based approaches for complex planning problems. Citeseer
* Schuster CJ (2006) No-wait Job Shop Scheduling: Tabu Search and Complexity of Subproblems. Math Meth Oper Res 63:473–491. https://doi.org/10.1007/s00186-005-0056-y
* Framinan JM, Schuster C (2006) An enhanced timetabling procedure for the no-wait job shop problem: a complete local search approach. Computers & Operations Research 33:1200–1213. https://doi.org/10.1016/j.cor.2004.09.009
* Lennartz PM (2006) No-wait job shop scheduling, a constraint propagation approach. PhD Thesis, Utrecht University
* Bansal N, Mahdian M, Sviridenko M (2005) Minimizing Makespan in No-Wait Job Shops. Mathematics of OR 30:817–831. https://doi.org/10.1287/moor.1050.0155
* Schuster CJ, Framinan JM (2003) Approximative procedures for no-wait job shop scheduling. Operations Research Letters 31:308–318. https://doi.org/10.1016/S0167-6377(03)00005-1
* Mascis A, Pacciarelli D (2002) Job-shop scheduling with blocking and no-wait constraints. European Journal of Operational Research 143:498–517. https://doi.org/10.1016/S0377-2217(01)00338-1

</p>
</details>

* Data: [jobshopscheduling.7z](https://github.com/fontanf/orproblems/releases/download/data/jobshopscheduling.7z)


### Assembly Line Balancing


[Simple Assembly Line Balancing Problem of Type 1 (SALBP-1)](orproblems/simpleassemblylinebalancing1.hpp)
* Bin Packing Problem with precedence constraints of the form `bin(j1) <= bin(j2) `

<details><summary>Literature</summary>
<p>

* Li Z, Kucukkoc I, Tang Q (2020) A comparative study of exact methods for the simple assembly line balancing problem. Soft Comput 24:11459–11475. https://doi.org/10.1007/s00500-019-04609-9
* Morrison DR, Sewell EC, Jacobson SH (2014) An application of the branch, bound, and remember algorithm to a new simple assembly line balancing dataset. European Journal of Operational Research 236:403–409. https://doi.org/10.1016/j.ejor.2013.11.033
* Sewell EC, Jacobson SH (2011) A Branch, Bound, and Remember Algorithm for the Simple Assembly Line Balancing Problem. INFORMS Journal on Computing 24:433–442. https://doi.org/10.1287/ijoc.1110.0462
* Blum C (2008) Beam-ACO for Simple Assembly Line Balancing. INFORMS Journal on Computing 20:618–627. https://doi.org/10.1287/ijoc.1080.0271
* Scholl A, Becker C (2006) State-of-the-art exact and heuristic solution procedures for simple assembly line balancing. European Journal of Operational Research 168:666–693. https://doi.org/10.1016/j.ejor.2004.07.022
* Scholl A, Voß S (1997) Simple assembly line balancing—Heuristic approaches. J Heuristics 2:217–244. https://doi.org/10.1007/BF00127358

</p>
</details>

* Data: [simpleassemblylinebalancing1.7z](https://github.com/fontanf/orproblems/releases/download/data/simpleassemblylinebalancing1.7z)


[U-shaped Assembly Line Balancing Problem of Type 1 (UALBP-1)](orproblems/ushapedassemblylinebalancing1.hpp)

<details><summary>Literature</summary>
<p>

* Li Z, Janardhanan MN, Rahman HF (2021) Enhanced beam search heuristic for U-shaped assembly line balancing problems. Engineering Optimization 53:594–608. https://doi.org/10.1080/0305215X.2020.1741569
* Li Z, Kucukkoc I, Zhang Z (2018) Branch, bound and remember algorithm for U-shaped assembly line balancing problem. Computers & Industrial Engineering 124:24–35. https://doi.org/10.1016/j.cie.2018.06.037
* Li Z, Kucukkoc I, Tang Q (2017) New MILP model and station-oriented ant colony optimization algorithm for balancing U-type assembly lines. Computers & Industrial Engineering 112:107–121. https://doi.org/10.1016/j.cie.2017.07.005
* Avikal S, Jain R, Mishra PK, Yadav HC (2013) A heuristic approach for U-shaped assembly line balancing to improve labor productivity. Computers & Industrial Engineering 64:895–901. https://doi.org/10.1016/j.cie.2013.01.001
* Sabuncuoglu I, Erel E, Alp A (2009) Ant colony optimization for the single model U-type assembly line balancing problem. International Journal of Production Economics 120:287–300. https://doi.org/10.1016/j.ijpe.2008.11.017
* Erel E, Sabuncuoglu I, Aksu BA (2001) Balancing of U-type assembly systems using simulated annealing. International Journal of Production Research 39:3003–3015. https://doi.org/10.1080/00207540110051905
* Miltenburg GJ, Wijngaard J (1994) The U-line Line Balancing Problem. Management Science 40:1378–1388. https://doi.org/10.1287/mnsc.40.10.1378

</p>
</details>

* Data: [simpleassemblylinebalancing1.7z](https://github.com/fontanf/orproblems/releases/download/data/simpleassemblylinebalancing1.7z)
