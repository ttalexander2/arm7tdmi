## arm7tdmi
This project's aim is to be an emulator of the arm7tdmi processor in c++20. The goal is to provide a library, providing a simple api for constructing, interfacing, and running an arm7tdmi cpu. 

**This project is in very early stages, and is a work in progress.**

### Currently:
- All ARM & THUMB instruction decoding is finished and tested
- Arm "Branch", "Branch and Exchange", "Block Data Transfer", are implemented. Branch instructions are tested.
- Basic memory interface is defined.

### Building:
Currently builds with CMake (temporarily requires fmt):
```cmake
cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)

add_executable(app main.cpp)
target_link_libraries(app PRIVATE arm7tdmi fmt::fmt)
```

### Tests:
- Tests can be enabled with CMake cache variable `BUILD_TESTING` set to `On`.
- Additionally, `ARM_ASSEMBLER_PATH` must be passed to cmake, in order to build and test with real ARM assembly. This expects a path to the `bin` folder of the ARM GNU Toolchain.
- Requires [Version 10.3-2021.10](https://developer.arm.com/downloads/-/gnu-rm/10-3-2021-10) of the ARM GNU Toolchain. Later versions have been found to not support `-march=armv4t`, required to build executables for this architecture.

### Resources:
- [ARM7TDMI Instruction Set](https://www.dwedit.org/files/ARM7TDMI.pdf)
- [gbatek - Arm Cpu Overview](https://mgba-emu.github.io/gbatek/#armcpuoverview)

