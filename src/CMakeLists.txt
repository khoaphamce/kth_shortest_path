set(APP_SOURCE_FILES main.cpp algo.h data_structure.h data_structure.cpp io_func.h math_algo.h)

#if(WIN32)
#   set(FORTY_SOURCE_FILES ${APP_SOURCE_FILES} sample.rc)
#endif(WIN32)

add_executable(runme ${APP_SOURCE_FILES})

# target_link_libraries(${CMAKE_PROJECT_NAME} ${wxWidgets_LIBRARIES})
