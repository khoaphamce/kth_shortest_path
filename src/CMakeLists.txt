set(APP_SOURCE_FILES 
main.cpp 
algo.h 
algo.cpp 
data_structure.h 
data_structure.cpp 
dijkstra.h 
dijkstra.cpp 
io_func.h 
io_func.cpp 
math_algo.h 
math_algo.cpp 
mandatory_edge.h 
mandatory_edge.cpp
)

#if(WIN32)
#   set(FORTY_SOURCE_FILES ${APP_SOURCE_FILES} sample.rc)
#endif(WIN32)

add_executable(runme ${APP_SOURCE_FILES})

# target_link_libraries(${CMAKE_PROJECT_NAME} ${wxWidgets_LIBRARIES})
