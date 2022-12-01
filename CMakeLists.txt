cmake_minimum_required (VERSION 3.24)

project(advent)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(subdir)
include(fileinput)

#add_subdirectory("2020")
#add_subdirectory("2021")
add_subdirectory("2022")

