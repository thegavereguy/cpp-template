add_executable(app app.cpp)

target_link_libraries(
    app
    PUBLIC model_library tools_library arrow_static spdlog::spdlog reflectcpp
)

target_include_directories(
    app
    PUBLIC ${arrow_SOURCE_DIR}/cpp/src ${arrow_BINARY_DIR}/src
)
