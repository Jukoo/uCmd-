cmake_minimum_required(VERSION 3.25) 
project(uCmd VERSION 1.0 DESCRIPTION "micro command") 
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON) 
set(CMAKE_BUILD_TYPE Debug) 

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin) 
include(Collections/config.cmake)

if(LS)
  message(STATUS "Build ls command")
  add_executable(${LS_CMD} ${LS_SOURCE})
endif() 

if(CLS)
  message(STATUS "Build cls command")
  add_executable(${CLS_CMD} ${CLS_SOURCE}) 
  target_link_libraries(
    ${CLS_CMD}
    ${CLS_USE_CURSES}
    )
endif() 
