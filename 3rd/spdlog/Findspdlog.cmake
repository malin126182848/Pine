if (NOT spdlog_FOUND)
    include(FetchContent)
    FetchContent_Declare(
      spdlog
      URL file://${CMAKE_SOURCE_DIR}/3rd/spdlog/spdlog-1.11.0.zip
      URL_HASH MD5=cd620e0f103737a122a3b6539bd0a57a
      DOWNLOAD_EXTRACT_TIMESTAMP true
    )
    set(SPDLOG_NO_TLS ON)
    FetchContent_MakeAvailable(spdlog)
    set(spdlog_FOUND TRUE)
endif()