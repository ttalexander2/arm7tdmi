//
// Created by talexander on 9/4/2024.
//
#include <catch2/catch_test_macros.hpp>

#include <arm7tdmi/decoder.h>

// TODO: Create/generate valid opcodes for tests

TEST_CASE("decode_branch_and_exchange", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::branch_and_exchange);
}

TEST_CASE("decode_block_data_transfer", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::block_data_transfer);
}

TEST_CASE("decode_branch_and_branch_with_link", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::branch_and_branch_with_link);
}

TEST_CASE("decode_software_interupt", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::software_interupt);
}

TEST_CASE("decode_undefined", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::undefined);
}

TEST_CASE("decode_single_data_transfer", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::single_data_transfer);
}

TEST_CASE("decode_single_data_swap", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::single_data_swap);
}

TEST_CASE("decode_multiply", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::multiply);
}

TEST_CASE("decode_multiply_long", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::multiply_long);
}

TEST_CASE("decode_halfword_data_transfer_register", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::halfword_data_transfer_register);
}

TEST_CASE("decode_halfword_data_transfer_immediate", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::halfword_data_transfer_immediate);
}

TEST_CASE("decode_psr_transfer_mrs", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::psr_transfer_mrs);
}

TEST_CASE("decode_psr_transfer_msr", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::psr_transfer_msr);
}
TEST_CASE("decode_data_processing", "[arm_instruction]") {

    constexpr u32 opcode = 0x000A5190;
    const auto instr = arm7tdmi::arm::decode(opcode);
    REQUIRE(instr == arm7tdmi::arm::instruction::data_processing);
}