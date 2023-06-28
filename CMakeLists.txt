cmake_minimum_required(VERSION 3.15)

project(Pine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_PDB_OUTPUT_DIRECTORY     ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY AUTOGEN_SOURCE_GROUP "Generated files")
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# 3rdParty 
include(FetchContent)
FetchContent_Declare(
  spdlog
  URL file://${CMAKE_SOURCE_DIR}/3rd/spdlog-1.11.0.zip
  URL_HASH MD5=cd620e0f103737a122a3b6539bd0a57a
  DOWNLOAD_EXTRACT_TIMESTAMP true
  )
FetchContent_Declare(
  glfw
  URL file://${CMAKE_SOURCE_DIR}/3rd/glfw-3.3.8.zip
  URL_HASH MD5=b06789a44e82a8a3ebd2e0301fb0484a
  DOWNLOAD_EXTRACT_TIMESTAMP true
  )
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
FetchContent_Declare(
  glad2
  URL file://${CMAKE_SOURCE_DIR}/3rd/glad-2.0.4.zip
  URL_HASH MD5=4929d9825531a70fb56a8a7e5440a940
  DOWNLOAD_EXTRACT_TIMESTAMP true
  SOURCE_SUBDIR  cmake
  )
FetchContent_MakeAvailable(
  spdlog
  glfw
  glad2
  )

# add subdirs cmakelists.txt
add_subdirectory(src/engine)

add_subdirectory(src/sandbox)
