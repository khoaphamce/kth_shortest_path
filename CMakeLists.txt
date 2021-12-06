cmake_minimum_required(VERSION 3.1...3.17)

project(kth_shortest_path VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")

set(APP_SOURCE_FILES 
    src/main.cpp 
    src/algo.h 
    src/algo.cpp 
    src/data_structure.h 
    src/data_structure.cpp 
    src/dijkstra.h 
    src/dijkstra.cpp 
    src/io_func.h 
    src/io_func.cpp 
    src/yen.h
    src/yen.cpp
    src/math_algo.h 
    src/math_algo.cpp 
    src/mandatory_edge.h 
    src/mandatory_edge.cpp
)

#if(WIN32)
#   set(FORTY_SOURCE_FILES ${APP_SOURCE_FILES} sample.rc)
#endif(WIN32)

add_executable(runme ${APP_SOURCE_FILES})
