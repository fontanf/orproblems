# Enable FetchContent.
include(FetchContent)

# Fetch boost.
set(BOOST_INCLUDE_LIBRARIES thread filesystem system program_options)
set(BOOST_ENABLE_CMAKE ON)
include(FetchContent)
FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.84.0
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Boost)

# Fetch fontanf/optimizationtools.
FetchContent_Declare(
    optimizationtools
    GIT_REPOSITORY https://github.com/fontanf/optimizationtools.git
    GIT_TAG 33a3966ece149d390ec7ce08699669b5267e64aa)
    #SOURCE_DIR "${PROJECT_SOURCE_DIR}/../optimizationtools/")
FetchContent_MakeAvailable(optimizationtools)

# Fetch fontanf/optimizationtools.
FetchContent_Declare(
    travelingsalesmansolver
    GIT_REPOSITORY https://github.com/fontanf/travelingsalesmansolver.git
    GIT_TAG 034ec06a797451e05ee3b99a5885261b18ab229f)
    #SOURCE_DIR "${PROJECT_SOURCE_DIR}/../travelingsalesmansolver/")
FetchContent_MakeAvailable(travelingsalesmansolver)

# Fetch 5cript/interval-tree.
FetchContent_Declare(
    interval-tree
    GIT_REPOSITORY https://github.com/5cript/interval-tree.git
    GIT_TAG a1b6a498b7bb2e611f547de16ee0a666f4d5c20f)
FetchContent_MakeAvailable(interval-tree)
