cmake_minimum_required(VERSION 3.20)

project(MFlow VERSION 0.4.1 DESCRIPTION "Independent native multimedia processing engine" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(MFLOW_BUILD_TESTS "Build MFlow tests" ON)
option(MFLOW_BUILD_BENCHMARKS "Build MFlow benchmarks" ON)
option(MFLOW_BUILD_EXAMPLES "Build MFlow examples" ON)

add_library(mflow_core
    core/src/media.cpp
    core/src/stream.cpp
    core/src/memory.cpp
    core/src/pipeline.cpp
    core/src/scheduler.cpp
    core/src/system.cpp
    core/src/converter.cpp
)

target_include_directories(mflow_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core/include)
target_compile_features(mflow_core PUBLIC cxx_std_20)

if(MSVC)
    target_compile_options(mflow_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(mflow_core PRIVATE -Wall -Wextra -Wpedantic -Wshadow)
endif()

add_executable(mflow cli/main.cpp)
target_link_libraries(mflow PRIVATE mflow_core)

if(MFLOW_BUILD_TESTS)
    enable_testing()
    add_executable(mflow_tests tests/test_core.cpp)
    target_link_libraries(mflow_tests PRIVATE mflow_core)
    add_test(NAME mflow_tests COMMAND mflow_tests)
endif()

if(MFLOW_BUILD_BENCHMARKS)
    add_executable(mflow_bench benchmarks/benchmark.cpp)
    target_link_libraries(mflow_bench PRIVATE mflow_core)
endif()

if(MFLOW_BUILD_EXAMPLES)
    add_executable(mflow_pipeline_example examples/pipeline.cpp)
    target_link_libraries(mflow_pipeline_example PRIVATE mflow_core)
endif()

# User-local installation is supported through CMAKE_INSTALL_PREFIX.
# Windows example: %LOCALAPPDATA%\\MFlow
# Linux example:   $HOME/.local
install(TARGETS mflow RUNTIME DESTINATION bin)
