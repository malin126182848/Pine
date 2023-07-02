if (NOT glfw_FOUND)
    include(FetchContent)
    FetchContent_Declare(
      glfw
      URL file://${CMAKE_SOURCE_DIR}/3rd/glfw/glfw-3.3.8.zip
      URL_HASH MD5=b06789a44e82a8a3ebd2e0301fb0484a
      DOWNLOAD_EXTRACT_TIMESTAMP true
      )
    set(GLFW_BUILD_EXAMPLES OFF)
    set(GLFW_BUILD_TESTS OFF)
    set(GLFW_BUILD_DOCS OFF)
    set(GLFW_INSTALL OFF)
    FetchContent_MakeAvailable(glfw)
    set(glfw_FOUND TRUE)
endif()