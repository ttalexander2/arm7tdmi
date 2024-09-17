//
// Created by talexander on 9/4/2024.
//

#include <iostream>
#include <catch2/catch_test_macros.hpp>

#include <arm7tdmi/decoder.h>

#include "test_util.h"
#include "fmt/compile.h"

// NOTE(Thomas): These test the decoding of a single instruction, using the provided arm assembly code.
// This requires installation and configuration of the Arm GNU Toolchain.  The as.exe and ld.exe
// executables are used from arm-none-eabi to compile/link the assembly into a binary. Path to
// the toolchain can be configured by passing in -DARM_ASSEMBLER_PATH="my/path/to/toolchain" into
// cmake. Most assembly code is taken from the instruction examples in the arm7tdmi manual.
//
// Use: Arm Toolchain 10.3.1

#ifdef TEST_COMPILED_ASSEMBLY

constexpr u32 entrypoint = 0x8000 / sizeof(u32);

TEST_CASE("arm_decode_branch_and_exchange", "[arm_instruction]") {
    const auto data = read_binary_from_file<u32>("assembly/arm/test_decode_branch_and_exchange.s.bin");
    for (int i = 0; i < 3; ++i) {
        u32 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::arm::decode(opcode);
        REQUIRE(instr == arm7tdmi::arm::instruction::branch_and_exchange);
    }
}

TEST_CASE("arm_decode_block_data_transfer", "[arm_instruction]") {
    const auto data = read_binary_from_file<u32>("assembly/arm/test_decode_block_data_transfer.s.bin");
    for (int i = 0; i < 5; ++i) {
        u32 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::arm::decode(opcode);
        REQUIRE(instr == arm7tdmi::arm::instruction::block_data_transfer);
    }

}

TEST_CASE("arm_decode_branch", "[arm_instruction]") {
    const auto data = read_binary_from_file<u32>("assembly/arm/test_decode_branch.s.bin");
    for (int i = 0; i < 5; ++i) {
        u32 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::arm::decode(opcode);
        REQUIRE(instr == arm7tdmi::arm::instruction::branch);
    }
}

TEST_CASE("arm_decode_software_interrupt", "[arm_instruction]") {
    const auto data = read_binary_from_file<u32>("assembly/arm/test_software_interrupt.s.bin");
    for (int i = 0; i < 2; ++i) {
        u32 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::arm::decode(opcode);
        REQUIRE(instr == arm7tdmi::arm::instruction::software_interrupt);
    }
}

TEST_CASE("arm_decode_single_data_transfer", "[arm_instruction]") {
    const auto data = read_binary_from_file<u32>("assembly/arm/test_single_data_transfer.s.bin");
    for (int i = 0; i < 5; ++i) {
        u32 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::arm::decode(opcode);
        REQUIRE(instr == arm7tdmi::arm::instruction::single_data_transfer);
    }
}

TEST_CASE("arm_decode_single_data_swap", "[arm_instruction]") {
    const auto data = read_binary_from_file<u32>("assembly/arm/test_single_data_swap.s.bin");
    for (int i = 0; i < 3; ++i) {
        u32 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::arm::decode(opcode);
        REQUIRE(instr == arm7tdmi::arm::instruction::single_data_swap);
    }
}

TEST_CASE("arm_decode_multiply", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::multiply);
}

TEST_CASE("arm_decode_multiply_long", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::multiply_long);
}

TEST_CASE("arm_decode_halfword_data_transfer_register", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::halfword_data_transfer_register);
}

TEST_CASE("arm_decode_halfword_data_transfer_immediate", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::halfword_data_transfer_immediate);
}

TEST_CASE("arm_decode_psr_transfer_mrs", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::psr_transfer_mrs);
}

TEST_CASE("arm_decode_psr_transfer_msr", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::psr_transfer_msr);
}
TEST_CASE("arm_decode_data_processing", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::data_processing);
}

#endif