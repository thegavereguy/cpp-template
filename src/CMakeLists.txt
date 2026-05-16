add_library(model_library model.cpp ../include/lib/model.h)
add_library(tools_library tools.cpp ../include/lib/tools.h)

target_include_directories(model_library PUBLIC ../include)
target_include_directories(tools_library PUBLIC ../include)

target_link_libraries(tools_library PUBLIC spdlog::spdlog)
target_link_libraries(model_library PUBLIC spdlog::spdlog)

target_include_directories(
    tools_library
    PUBLIC
        ${reflectcpp_SOURCE_DIR}/include
        ${arrow_SOURCE_DIR}/cpp/src
        ${arrow_BINARY_DIR}/src
)
