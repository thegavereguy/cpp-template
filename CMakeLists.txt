cmake_minimum_required(VERSION 3.10)

project(knn-cpp VERSION 1.1.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Arrow QUIET)
# if(NOT TARGET arrow::arrow)
#     add_library(arrow::arrow INTERFACE IMPORTED)
#     target_link_libraries(arrow::arrow INTERFACE Arrow::arrow_shared)
#     target_include_directories(arrow::arrow INTERFACE ${ARROW_INCLUDE_DIR})
# endif()

if(Arrow_FOUND)
    message(STATUS "Found Arrow v${Arrow_VERSION} on system")
else()
    message(STATUS "fetching Arrow from GitHub...")

    FetchContent_Declare(
        arrow
        GIT_REPOSITORY https://github.com/apache/arrow.git
        GIT_TAG
            apache-arrow-20.0.0 # Use a specific version tag
        SOURCE_SUBDIR
        cpp
    )

    set(ARROW_BUILD_SHARED OFF CACHE INTERNAL "")
    set(ARROW_BUILD_STATIC ON CACHE INTERNAL "")
    set(ARROW_CSV ON CACHE INTERNAL "")
    set(ARROW_JSON ON CACHE INTERNAL "")
    set(ARROW_COMPUTE ON CACHE INTERNAL "")
    set(ARROW_SIMD_LEVEL "NONE" CACHE INTERNAL "")
    set(ARROW_DEPENDENCY_SOURCE "BUNDLED" CACHE INTERNAL "")

    FetchContent_MakeAvailable(arrow)
    # Manual population to ensure variables are defined in this scope
    FetchContent_GetProperties(arrow)
    if(NOT arrow_POPULATED)
        FetchContent_Populate(arrow)
        add_subdirectory(${arrow_SOURCE_DIR} ${arrow_BINARY_DIR})
    endif()

    # Now these will definitely be populated
    message(STATUS "Arrow source dir: ${arrow_SOURCE_DIR}")
    message(STATUS "Arrow binary dir: ${arrow_BINARY_DIR}")
endif()

message(STATUS "fetching Catch2 from GitHub...")
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG
        v3.4.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

FetchContent_MakeAvailable(Catch2)

message(STATUS "fetching refletcpp from GitHub...")
FetchContent_Declare(
    reflectcpp
    GIT_REPOSITORY https://github.com/getml/reflect-cpp
    GIT_TAG
        v0.24.0 # or a later release
)
FetchContent_MakeAvailable(reflectcpp)

find_package(spdlog QUIET)

if(spdlog_FOUND)
    message(STATUS "Found system spdlog v${spdlog_VERSION}")
else()
    message(STATUS "spdlog not found on system, fetching from GitHub...")
    include(FetchContent)
    FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.15.0
    )
    FetchContent_MakeAvailable(spdlog)
endif()

set(REFLECTCPP_CSV ON)
# set(REFLECTCPP_FLEXBUFFERS ON) # indagare questo

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

include(CTest)
include(Catch)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(apps)
