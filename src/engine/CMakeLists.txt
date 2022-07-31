cmake_minimum_required(VERSION 3.15)

project(engine)

set(prj_header 
  ${CMAKE_CURRENT_SOURCE_DIR}/include/globel.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Application.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Log.h
  )

add_library(engine SHARED
  ${prj_header}
  Application.cpp
  Log.cpp
  )

target_link_libraries(engine 
  PRIVATE
  spdlog::spdlog
  )

target_include_directories(engine 
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
