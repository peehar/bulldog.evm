cmake_minimum_required(VERSION 2.8)
project(bulldog.evm)
add_definitions(-std=c++11 -Wall)
add_subdirectory(data)
add_subdirectory(exec)
add_subdirectory(utils)
aux_source_directory(. SRC_LIST)
add_executable(evm main.cpp)
target_link_libraries(evm data exec utils)

install(TARGETS evm RUNTIME DESTINATION bin)
