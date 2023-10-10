cmake_minimum_required(VERSION 3.0)

project(conway)

add_executable(conway main.cpp)

install(TARGETS conway RUNTIME DESTINATION bin)
