# Minimum CMake version
cmake_minimum_required(VERSION 3.15)

# Project name
project(DMA)

# C++ standard (17 - modern, stable)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Fetch external libraries from GitHub


# Build executable
add_executable(dma_agent
    src/main.cpp
    src/agent.cpp
    src/collectors/system_metrics_collector.cpp
    src/aggregator.cpp
)

# Include directories for headers
target_include_directories(dma_agent PRIVATE include)


