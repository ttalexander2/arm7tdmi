cmake_minimum_required(VERSION 3.28)
project(arm7tdmi)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1


FetchContent_MakeAvailable(fmt)


add_executable(arm7tdmi main.cpp
        decoder.h
        types.h
        decoder.cpp
        util.h)

target_link_libraries(arm7tdmi fmt::fmt)
