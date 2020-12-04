cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(subdir)
include(fileinput)

subdirlist(ALLDIRS "day")
foreach(subdir ${ALLDIRS})
  project (${subdir})
  add_executable(${PROJECT_NAME})
  advent_input()
  target_sources(${PROJECT_NAME} PRIVATE "${subdir}/main.cpp")
endforeach()

