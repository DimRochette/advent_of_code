# return a dirlist of subdirectories starting with argument
# subdirlist(VARIABLENAME "day")
# return in VARIABLENAME all subdirectory starting with day
macro(subdirlist result startwith)
  file(GLOB children RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/${startwith}*")
  set(dirlist "")
  foreach(child ${children})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child})
      LIST(APPEND dirlist ${child})
    endif()
  endforeach()
  SET(${result} ${dirlist})
endmacro()