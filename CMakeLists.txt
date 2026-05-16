cmake_minimum_required(VERSION 3.10)

project(template VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

message(STATUS "Fetching Catch2...")
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG
        v3.4.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

find_package(spdlog QUIET)

if(spdlog_FOUND)
    message(STATUS "Found system spdlog v${spdlog_VERSION}")
else()
    message(STATUS "Fetching spdlog...")
    include(FetchContent)
    FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.15.0
    )
    FetchContent_MakeAvailable(spdlog)
endif()

include(CTest)
include(Catch)

add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(tests)
