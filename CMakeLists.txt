cmake_minimum_required(VERSION 3.15.0)

project(ORProblems LANGUAGES CXX)

# Build options.
option(ORPROBLEMS_BUILD_TEST "Build the unit tests" ON)

# Avoid FetchContent warning.
cmake_policy(SET CMP0135 NEW)

# Require C++14.
set(CMAKE_CXX_STANDARD 14)

# Enable output of compile commands during generation.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add sub-directories.
add_subdirectory(extern)
add_subdirectory(src)
if(ORPROBLEMS_BUILD_TEST)
  add_subdirectory(test)
endif()