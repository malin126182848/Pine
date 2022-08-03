cmake_minimum_required(VERSION 3.15)

project(engine)

set(prj_header 
  ${CMAKE_CURRENT_SOURCE_DIR}/include/globel.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Application.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Log.h
  )

add_library(${PROJECT_NAME} SHARED
  ${prj_header}
  src/Application.cpp
  src/Log.cpp
  )

target_link_libraries(${PROJECT_NAME} 
  PUBLIC 
  spdlog::spdlog
  glad_gl_core_45
  glfw
  OpenGL::GL
  )

target_include_directories(${PROJECT_NAME} 
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
