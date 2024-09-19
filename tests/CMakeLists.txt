cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)

option(ARM_VENDORED "Use vendored libraries" OFF)


set(OUTPUT_DIR "arm7tdmi-tests-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_BUILD_TYPE}")
string(TOLOWER "${OUTPUT_DIR}" OUTPUT_DIR)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${OUTPUT_DIR}")

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
        test_decode_arm_instructions.cpp
        test_decode_thumb_instructions.cpp
        utility.h
        utility.h
        test_arm_instructions.cpp
        test_arm_instructions.cpp)

target_link_libraries(tests PRIVATE arm7tdmi Catch2::Catch2WithMain fmt::fmt)

catch_discover_tests(tests)

SET(ARM_ASSEMBLER_PATH "" CACHE PATH "Arm GNU Toolchain path (arm-none-eabi)")

if (DEFINED CACHE{ARM_ASSEMBLER_PATH})
    message(STATUS  "Using ARM assembler in: ${ARM_ASSEMBLER_PATH}")

    add_compile_definitions(-DTEST_COMPILED_ASSEMBLY)
    file(GLOB_RECURSE ASSEMBLY_SOURCE CONFIGURE_DEPENDS *.s)

    if (WIN32)
        set(EX_END ".exe")
    elseif(UNIX)
        set(EX_END "")
    endif()

    add_custom_target(make-asm-output-dir ALL
            COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assembly")

    foreach(item IN LISTS ASSEMBLY_SOURCE)
        get_filename_component(item_file_name ${item} NAME)
        set(ASM_IM "${CMAKE_CURRENT_BINARY_DIR}/${item_file_name}.o")
        cmake_path(RELATIVE_PATH item BASE_DIRECTORY "${CMAKE_SOURCE_DIR}/tests" OUTPUT_VARIABLE ASM_OUT_DIR)
        get_filename_component(ASM_OUT_DIR "${ASM_OUT_DIR}" DIRECTORY)
        set(ASM_OUT "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${ASM_OUT_DIR}/${item_file_name}.bin")
        add_custom_command(
                OUTPUT "${ASM_OUT}"
                COMMAND ${ARM_ASSEMBLER_PATH}/arm-none-eabi-as${EX_END} ${item} -march=armv4t -o ${ASM_IM} && ${ARM_ASSEMBLER_PATH}/arm-none-eabi-ld${EX_END} ${ASM_IM} -o ${ASM_OUT}
                DEPENDS "${item}"
        )
        list(APPEND ASSEMBLY_BINARY_FILES ${ASM_OUT})
    endforeach()

    add_custom_target(
            assembly
            DEPENDS ${ASSEMBLY_BINARY_FILES}
    )

    add_dependencies(tests assembly)
else()
endif()


