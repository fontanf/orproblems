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
FetchContent_Declare(
    optimizationtools
    GIT_REPOSITORY https://github.com/fontanf/optimizationtools.git
    GIT_TAG 66f61a3e02c746c57584a5d5257e1b1455d4a9ae
    #SOURCE_DIR "${PROJECT_SOURCE_DIR}/../optimizationtools/"
    EXCLUDE_FROM_ALL)
FetchContent_MakeAvailable(optimizationtools)

# Fetch fontanf/travelingsalesmansolver.
FetchContent_Declare(
    travelingsalesmansolver
    GIT_REPOSITORY https://github.com/fontanf/travelingsalesmansolver.git
    GIT_TAG 034ec06a797451e05ee3b99a5885261b18ab229f
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
