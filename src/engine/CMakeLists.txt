cmake_minimum_required(VERSION 3.15)

project(engine)

set(prj_header 
  ${CMAKE_CURRENT_SOURCE_DIR}/include/core/globel.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/core/Application.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/core/Log.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/core/Window.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/events/Event.h
  )

add_library(${PROJECT_NAME} SHARED
  ${prj_header}
  src/core/Application.cpp
  src/core/Log.cpp
  src/math/linmath.h
  src/platform/windows/WindowsForm.h
  src/platform/windows/WindowsForm.cpp
  )

find_package(spdlog REQUIRED)
find_package(glfw REQUIRED)
find_package(glad REQUIRED)

target_link_libraries(${PROJECT_NAME} 
  PUBLIC
  spdlog::spdlog
  PRIVATE 
  glad
  glfw
  )

target_include_directories(${PROJECT_NAME} 
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/math/
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/include/core
  ${CMAKE_CURRENT_SOURCE_DIR}/include/utils
  ${CMAKE_CURRENT_SOURCE_DIR}/include/events
  )

target_compile_definitions(${PROJECT_NAME} 
  PRIVATE 
  GLFW_INCLUDE_NONE
  )

target_precompile_headers(${PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include/pch.h
  )
