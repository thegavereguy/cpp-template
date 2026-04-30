add_executable(tests test.cpp)

target_link_libraries(
    tests
    PRIVATE Catch2::Catch2WithMain test_library spdlog::spdlog
)

catch_discover_tests(tests)
