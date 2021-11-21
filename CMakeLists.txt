cmake_minimum_required(VERSION 3.1...3.17)

project(kth_shortest_path VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")

add_subdirectory(src)