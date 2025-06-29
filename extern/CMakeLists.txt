# Enable FetchContent.
include(FetchContent)

# Fetch boost.
if(ORPROBLEMS_BUILD_TEST)
  set(BOOST_INCLUDE_LIBRARIES thread filesystem system program_options)
  set(BOOST_ENABLE_CMAKE ON)
  FetchContent_Declare(
      Boost
      URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
      EXCLUDE_FROM_ALL)
  FetchContent_MakeAvailable(Boost)
endif()

# Fetch fontanf/optimizationtools.
set(OPTIMIZATIONTOOLS_BUILD_TEST OFF)
FetchContent_Declare(
    optimizationtools
    GIT_REPOSITORY https://github.com/fontanf/optimizationtools.git
    GIT_TAG 5e0c59cb06c779d1950b31caa636998b37f5db1b
    #SOURCE_DIR "${PROJECT_SOURCE_DIR}/../optimizationtools/"
    EXCLUDE_FROM_ALL)
FetchContent_MakeAvailable(optimizationtools)

# Fetch fontanf/travelingsalesmansolver.
set(TRAVELINGSALESMANSOLVER_BUILD_MAIN OFF)
set(TRAVELINGSALESMANSOLVER_BUILD_TEST OFF)
FetchContent_Declare(
    travelingsalesmansolver
    GIT_REPOSITORY https://github.com/fontanf/travelingsalesmansolver.git
    GIT_TAG 1be22ddae585e9e85d1682f528c5a5813b3ede4c
    #SOURCE_DIR "${PROJECT_SOURCE_DIR}/../travelingsalesmansolver/"
    EXCLUDE_FROM_ALL)
FetchContent_MakeAvailable(travelingsalesmansolver)

# Fetch 5cript/interval-tree.
FetchContent_Declare(
    interval-tree
    GIT_REPOSITORY https://github.com/5cript/interval-tree.git
    GIT_TAG a1b6a498b7bb2e611f547de16ee0a666f4d5c20f
    EXCLUDE_FROM_ALL)
FetchContent_MakeAvailable(interval-tree)
