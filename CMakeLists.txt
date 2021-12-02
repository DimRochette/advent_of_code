cmake_minimum_required (VERSION 3.8)

project(advent)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(subdir)
include(fileinput)

#add_subdirectory("2020")
add_subdirectory("2021")

