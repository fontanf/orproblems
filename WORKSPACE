load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

git_repository(
    name = "com_github_nelhage_rules_boost",
    remote = "https://github.com/nelhage/rules_boost",
    commit = "e83dfef18d91a3e35c8eac9b9aeb1444473c0efd",
    shallow_since = "1671181466 +0000",
)
load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()

http_archive(
    name = "json",
    build_file_content = """
cc_library(
        name = "json",
        hdrs = ["single_include/nlohmann/json.hpp"],
        visibility = ["//visibility:public"],
        strip_include_prefix = "single_include/"
)
""",
    urls = ["https://github.com/nlohmann/json/releases/download/v3.7.3/include.zip"],
    sha256 = "87b5884741427220d3a33df1363ae0e8b898099fbc59f1c451113f6732891014",
)

git_repository(
    name = "optimizationtools",
    remote = "https://github.com/fontanf/optimizationtools.git",
    commit = "0bd9be63666a4ddf66c2ca89ca984bda59824e01",
)

local_repository(
    name = "optimizationtools_",
    path = "../optimizationtools/",
)

git_repository(
    name = "travelingsalesmansolver",
    remote = "https://github.com/fontanf/travelingsalesmansolver.git",
    commit = "004086c1a544efea380ce5d757528eee23a73969",
)

local_repository(
    name = "travelingsalesmansolver_",
    path = "../travelingsalesmansolver/",
)

http_archive(
    name = "simdjson",
    build_file_content = """
cc_library(
        name = "simdjson",
        hdrs = ["simdjson-0.9.2/singleheader/simdjson.h"],
        srcs = ["simdjson-0.9.2/singleheader/simdjson.cpp"],
        visibility = ["//visibility:public"],
        strip_include_prefix = "simdjson-0.9.2/singleheader/"
)
""",
    urls = ["https://github.com/simdjson/simdjson/archive/refs/tags/v0.9.2.zip"],
    sha256 = "4d4e4a9d64b55839ec6c80f0ba54261139543b7ffcf84bceede681ccb95fe94b",
)

http_archive(
    name = "interval-tree",
    build_file_content = """
cc_library(
        name = "interval-tree",
        hdrs = glob(["interval-tree-1.2/*.hpp"]),
        visibility = ["//visibility:public"],
        strip_include_prefix = "interval-tree-1.2/"
)
""",
    urls = ["https://github.com/5cript/interval-tree/archive/refs/tags/1.2.zip"],
    sha256 = "d72f917ae7d8f2540c4603bc9bf5386904ca3e40f09da0efcdb3671835b7326f"
)

