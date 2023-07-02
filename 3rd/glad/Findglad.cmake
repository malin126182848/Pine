if (NOT glad_FOUND)
    include(FetchContent)
    FetchContent_Declare(
      glad2
      URL file://${CMAKE_SOURCE_DIR}/3rd/glad/glad-2.0.4.zip
      URL_HASH MD5=4929d9825531a70fb56a8a7e5440a940
      DOWNLOAD_EXTRACT_TIMESTAMP true
      SOURCE_SUBDIR cmake
    )
    FetchContent_MakeAvailable(glad2)
    glad_add_library(glad REPRODUCIBLE API gl:core=4.5)
    set (glad_FOUND TRUE)
endif()