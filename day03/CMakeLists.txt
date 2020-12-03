cmake_minimum_required (VERSION 3.8)

project ("day03")
include(fileinput)
add_executable(${PROJECT_NAME})
advent_input()
target_sources(${PROJECT_NAME} PRIVATE "${PROJECT_NAME}.cpp")