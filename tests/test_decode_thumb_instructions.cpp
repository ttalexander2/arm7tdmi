//
// Created by talexander on 9/4/2024.
//

#include <catch2/catch_test_macros.hpp>

#include <arm7tdmi/decoder.h>
#include "test_util.h"

#ifdef TEST_COMPILED_ASSEMBLY

constexpr u32 entrypoint = 0x8000 / sizeof(u16);

TEST_CASE("thumb_decode_software_interrupt", "[thumb_instruction]")
 {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_software_interrupt.s.bin");
    for (int i = 0; i < 3; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::software_interrupt);
    }
}

TEST_CASE("thumb_decode_unconditional_branch", "[thumb_instruction]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_unconditional_branch.s.bin");
    for (int i = 0; i < 2; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::unconditional_branch);
    }
}
TEST_CASE("thumb_decode_conditional_branch", "[thumb_instruction]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_conditional_branch.s.bin");
    for (int i = 1; i < 15; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::conditional_branch);
    }
}
TEST_CASE("thumb_decode_multiple_load_store", "[thumb_instruction]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_multiple_load_store.s.bin");
    for (int i = 0; i < 1; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::multiple_load_store);
    }
}
TEST_CASE("thumb_decode_long_branch_with_link", "[thumb_instruction]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_long_branch_with_link.s.bin");
    for (int i = 0; i < 3; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::long_branch_with_link);
    }
}
TEST_CASE("thumb_decode_add_offset_to_stack_pointer", "[thumb_instruction]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_add_offset_to_stack_pointer.s.bin");
    for (int i = 0; i < 2; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::add_offset_to_stack_pointer);
    }
}
TEST_CASE("thumb_decode_push_pop_registers", "[thumb_instruction]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_push_pop_registers.s.bin");
    for (int i = 0; i < 2; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::push_pop_registers);
    }
}
TEST_CASE("thumb_decode_load_store_halfword", "[thumb_instruction]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_load_store_halfword.s.bin");
    for (int i = 0; i < 2; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::load_store_halfword);
    }
}
TEST_CASE("thumb_decode_sp_relative_load_store", "[thumb_instruction]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_sp_relative_load_store.s.bin");
    for (int i = 0; i < 2; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::sp_relative_load_store);
    }
}
TEST_CASE("thumb_decode_load_address", "[thumb_instruction]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_load_address.s.bin");
    for (int i = 0; i < 2; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::load_address);
    }
}
TEST_CASE("thumb_decode_load_store_with_immediate_offset", "[thumb_instruction]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_load_store_with_immediate_offset.s.bin");
    for (int i = 0; i < 2; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::load_store_with_immediate_offset);
    }
}
TEST_CASE("thumb_decode_load_store_with_register_offset", "[thumb_instruction]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_load_store_with_register_offset.s.bin");
    for (int i = 0; i < 2; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::load_store_with_register_offset);
    }
}
TEST_CASE("thumb_decode_load_store_sign_extended_byte_halfword", "[thumb_instruction]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_load_store_sign_extended_byte_halfword.s.bin");
    for (int i = 0; i < 3; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::load_store_sign_extended_byte_halfword);
    }
}
TEST_CASE("thumb_decode_pc_relative_load", "[thumb_instruction]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_pc_relative_load.s.bin");
    for (int i = 0; i < 1; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::pc_relative_load);
    }
}
TEST_CASE("thumb_decode_hi_register_operations_branch_exchange", "[thumb_instruction]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_hi_register_operations_branch_exchange.s.bin");
    for (int i = 0; i < 5; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::hi_register_operations_branch_exchange);
    }
}
TEST_CASE("thumb_decode_alu_operations", "[thumb_instruction]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_alu_operations.s.bin");
    for (int i = 0; i < 16; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::alu_operations);
    }
}
TEST_CASE("thumb_decode_move_compare_add_subtract_immediate", "[thumb_instruction]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_move_compare_add_subtract_immediate.s.bin");
    for (int i = 0; i < 4; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::move_compare_add_subtract_immediate);
    }
}
TEST_CASE("thumb_decode_add_subtract", "[thumb_instruction]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_add_subtract.s.bin");
    for (int i = 0; i < 4; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::add_subtract);
    }
}
TEST_CASE("thumb_decode_move_shifted_register", "[thumb_instruction]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/test_thumb_decode_move_shifted_register.s.bin");
    for (int i = 0; i < 3; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::move_shifted_register);
    }
}

#endif