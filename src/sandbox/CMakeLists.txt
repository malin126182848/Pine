cmake_minimum_required(VERSION 3.15)

project(sandbox)

add_executable(sandbox main.cpp)

target_link_libraries(sandbox 
  PUBLIC 
  engine
  )
