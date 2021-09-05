load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

git_repository(
    name = "com_github_nelhage_rules_boost",
    commit = "9f9fb8b2f0213989247c9d5c0e814a8451d18d7f",
    remote = "https://github.com/nelhage/rules_boost",
    shallow_since = "1570056263 -0700",
)
load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()

git_repository(
    name = "optimizationtools",
    remote = "https://github.com/fontanf/optimizationtools.git",
    commit = "c2df60575bed9af3cfb8652bc3c859f98b52b58c",
    shallow_since = "1630764843 +0200",
)

http_archive(
    name = "pugixml",
    build_file_content = """
cc_library(
        name = "pugixml",
        srcs = ["pugixml-1.11/src/pugixml.cpp"],
        hdrs = ["pugixml-1.11/src/pugixml.hpp", "pugixml-1.11/src/pugiconfig.hpp"],
        visibility = ["//visibility:public"],
        strip_include_prefix = "pugixml-1.11/src/"
)
""",
    urls = ["https://github.com/zeux/pugixml/releases/download/v1.11/pugixml-1.11.tar.gz"],
    sha256 = "26913d3e63b9c07431401cf826df17ed832a20d19333d043991e611d23beaa2c",
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

