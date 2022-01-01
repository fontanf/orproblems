def Settings(**kwargs):
    return {
            'flags': [
                '-x', 'c++',
                '-Wall', '-Wextra', '-Werror',
                '-I', '.',
                '-I', './bazel-orproblems/',
                '-I', './bazel-orproblems/external/json/single_include/',
                '-I', './bazel-orproblems/external/simdjson/simdjson-0.9.2/singleheader',
                '-I', './bazel-orproblems/external/interval-tree/interval-tree-1.2/',
                '-I', './bazel-orproblems/external/googletest/googletest/include/',
                '-I', './bazel-orproblems/external/boost/',
                '-I', './bazel-orproblems/external/optimizationtools/',
                # '-I', '../optimizationtools/',
                ],
            }
