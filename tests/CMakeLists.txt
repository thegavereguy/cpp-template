add_executable(tests test.cpp)

target_link_libraries(tests PUBLIC Catch2::Catch2WithMain)
target_link_libraries(tests PUBLIC model_library spdlog::spdlog)

catch_discover_tests(tests)
