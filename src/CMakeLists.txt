add_library(test_library lib.cpp ../include/lib/lib.h)

target_include_directories(test_library PUBLIC ../include)

target_link_libraries(test_library PUBLIC spdlog::spdlog)

target_include_directories(
    test_library
    PUBLIC
        ${reflectcpp_SOURCE_DIR}/include
        ${arrow_SOURCE_DIR}/cpp/src
        ${arrow_BINARY_DIR}/src
)
