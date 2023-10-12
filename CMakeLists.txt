cmake_minimum_required(VERSION 3.0)

project(conway)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)
find_package(SDL2 REQUIRED)

# Add global definitions
add_definitions("-Wall")
include_directories(${SDL2_INCLUDE_DIR})


add_executable(conway main.cpp)

set_property(TARGET conway PROPERTY CXX_STANDARD 17)
install(TARGETS conway RUNTIME DESTINATION bin)

target_link_libraries(conway ${SDL2_LIBRARIES})
