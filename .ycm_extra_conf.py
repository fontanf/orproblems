def Settings(**kwargs):
    return {
            'flags': [
                '-x', 'c++',
                '-Wall', '-Wextra', '-Werror',
                '-DGUROBI_FOUND',
                '-DCPLEX_FOUND',
                '-DIL_STD', # Cplex
                '-I', '.',
                '-I', './bazel-orproblems/',
                '-I', './bazel-orproblems/external/json/single_include/',
                '-I', './bazel-orproblems/external/googletest/googletest/include/',
                '-I', './bazel-orproblems/external/boost/',
                '-I', './bazel-orproblems/external/simdjson/simdjson-0.9.2/singleheader',
                # '-I', './bazel-orproblems/external/optimizationtools/',
                '-I', './../optimizationtools/',
                '-I', '/opt/ibm/ILOG/CPLEX_Studio129/concert/include/',
                '-I', '/opt/ibm/ILOG/CPLEX_Studio129/cplex/include/',
                '-I', '/opt/ibm/ILOG/CPLEX_Studio129/cpoptimizer/include/',
                '-I', '/home/florian/Programmes/gurobi811/linux64/include/',
                ],
            }
