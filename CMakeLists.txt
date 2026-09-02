cmake_minimum_required(VERSION 3.20.0)

set(CODECHECKER_ANALYZE_OPTS
    "--config;${CMAKE_SOURCE_DIR}/codechecker/codechecker.yml;"
    "--skip;${CMAKE_SOURCE_DIR}/codechecker/skip.codechecker"
    CACHE STRING "Code checker options")

# Find and load the Zephyr build system package
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# Define your project name
project(open_tempo)

# Target the application source code files
# Note: Zephyr handles compiler flags for C++ automatically when using .cpp extensions
target_sources(app PRIVATE src/main.cpp)
