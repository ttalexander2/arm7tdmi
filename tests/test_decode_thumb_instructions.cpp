//
// Created by talexander on 9/4/2024.
//

#include <catch2/catch_test_macros.hpp>

#include <arm7tdmi/decoder.h>

TEST_CASE("decode_software_interrupt", "[thumb_instruction]")
 {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::software_interrupt);
}

TEST_CASE("decode_unconditional_branch", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::unconditional_branch);
}
TEST_CASE("decode_conditional_branch", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::conditional_branch);
}
TEST_CASE("decode_multiple_load_store", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::multiple_load_store);
}
TEST_CASE("decode_long_branch_with_link", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::long_branch_with_link);
}
TEST_CASE("decode_add_offset_to_stack_pointer", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::add_offset_to_stack_pointer);
}
TEST_CASE("decode_push_pop_registers", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::push_pop_registers);
}
TEST_CASE("decode_load_store_halfword", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::load_store_halfword);
}
TEST_CASE("decode_sp_relative_load_store", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::sp_relative_load_store);
}
TEST_CASE("decode_load_address", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::load_address);
}
TEST_CASE("decode_load_store_with_immediate_offset", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::load_store_with_immediate_offset);
}
TEST_CASE("decode_load_store_with_register_offset", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::load_store_with_register_offset);
}
TEST_CASE("decode_load_store_sign_extended_byte_halfword", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::load_store_sign_extended_byte_halfword);
}
TEST_CASE("decode_pc_relative_load", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::pc_relative_load);
}
TEST_CASE("decode_hi_register_operations_branch_exchange", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::hi_register_operations_branch_exchange);
}
TEST_CASE("decode_alu_operations", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::alu_operations);
}
TEST_CASE("decode_move_compare_add_subtract_immediate", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::move_compare_add_subtract_immediate);
}
TEST_CASE("decode_add_subtract", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::add_subtract);
}
TEST_CASE("decode_move_shifted_register", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::move_shifted_register);
}
TEST_CASE("decode_unknown", "[thumb_instruction]") {

    constexpr u16 opcode = 0x5190;
    const auto instr = arm7tdmi::thumb::decode(opcode);
    REQUIRE(instr == arm7tdmi::thumb::instruction::unknown);
}