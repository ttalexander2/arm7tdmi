cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)

option(ARM_VENDORED "Use vendored libraries" OFF)


set(OUTPUT_DIR "arm7tdmi-tests-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_BUILD_TYPE}")
string(TOLOWER "${OUTPUT_DIR}" OUTPUT_DIR)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${OUTPUT_DIR}/")

FetchContent_Declare(
        catch
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.7.0
)

FetchContent_MakeAvailable(catch)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

add_executable(tests
        test_arm_instructions.cpp
        test_thumb_instructions.cpp)

target_link_libraries(tests PRIVATE arm7tdmi Catch2::Catch2WithMain fmt::fmt)

catch_discover_tests(tests)