cmake_minimum_required(VERSION 3.15)

project(engine)

set(prj_header 
  ${CMAKE_CURRENT_SOURCE_DIR}/include/core/globel.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/core/Application.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/core/Log.h
  )

add_library(${PROJECT_NAME} SHARED
  ${prj_header}
  src/core/Application.cpp
  src/core/Log.cpp
  src/math/linmath.h
  )

target_link_libraries(${PROJECT_NAME} 
  PUBLIC 
  spdlog::spdlog
  glad_gl_core_45
  glfw
  OpenGL::GL
  )

target_include_directories(${PROJECT_NAME} 
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/math/
  ${CMAKE_CURRENT_SOURCE_DIR}/include/
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include/core
  ${CMAKE_CURRENT_SOURCE_DIR}/include/utils
  ${CMAKE_CURRENT_SOURCE_DIR}/include/events
  )

target_precompile_headers(${PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include/pch.h
  )
