set(CMAKE_CXX_STANDARD 20)

set(OUTPUT_DIR "arm7tdmi-example-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_BUILD_TYPE}")
string(TOLOWER "${OUTPUT_DIR}" OUTPUT_DIR)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${OUTPUT_DIR}/")


add_executable(example main.cpp)

target_compile_features(example PRIVATE cxx_std_20)

target_link_libraries(example PRIVATE arm7tdmi fmt::fmt)