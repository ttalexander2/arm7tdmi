cmake_minimum_required(VERSION 3.28)
project(arm7tdmi
        VERSION 0.1
        DESCRIPTION "arm7tdmi emulator library"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_TESTING "Build tests for arm7tdmi" ON)

include(arm7tdmi.cmake)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_STANDARD 20)
    option(ARM_VENDORED "Use vendored libraries" OFF)

    set(OUTPUT_DIR "arm7tdmi-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_BUILD_TYPE}")
    string(TOLOWER "${OUTPUT_DIR}" OUTPUT_DIR)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${OUTPUT_DIR}/")

endif()

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1


FetchContent_MakeAvailable(fmt)



add_library(arm7tdmi STATIC)

include_directories(include)

target_sources(arm7tdmi PUBLIC ${ARM_HEADERS})
target_sources(arm7tdmi PRIVATE ${ARM_SOURCE})

target_link_libraries(${PROJECT_NAME} PRIVATE
        fmt::fmt
)

add_subdirectory(example)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
        AND BUILD_TESTING)
    add_subdirectory(tests)
endif()
