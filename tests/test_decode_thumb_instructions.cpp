//
// Created by talexander on 9/4/2024.
//

#include <catch2/catch_test_macros.hpp>

#include <arm7tdmi/decoder.h>
#include "utility.h"

#ifdef TEST_COMPILED_ASSEMBLY

constexpr u32 entrypoint = 0x8000 / sizeof(u16);

TEST_CASE("thumb_decode_software_interrupt", "[decode]")
 {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_software_interrupt.s.bin");
    for (int i = 0; i < 3; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::software_interrupt);
    }
}

TEST_CASE("thumb_decode_unconditional_branch", "[decode]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_unconditional_branch.s.bin");
    for (int i = 0; i < 2; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::unconditional_branch);
    }
}
TEST_CASE("thumb_decode_conditional_branch", "[decode]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_conditional_branch.s.bin");
    for (int i = 1; i < 15; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::conditional_branch);
    }
}
TEST_CASE("thumb_decode_multiple_load_store", "[decode]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_multiple_load_store.s.bin");
    for (int i = 0; i < 1; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::multiple_load_store);
    }
}
TEST_CASE("thumb_decode_long_branch_with_link", "[decode]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_long_branch_with_link.s.bin");
    for (int i = 0; i < 3; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::long_branch_with_link);
    }
}
TEST_CASE("thumb_decode_add_offset_to_stack_pointer", "[decode]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_add_offset_to_stack_pointer.s.bin");
    for (int i = 0; i < 2; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::add_offset_to_stack_pointer);
    }
}
TEST_CASE("thumb_decode_push_pop_registers", "[decode]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_push_pop_registers.s.bin");
    for (int i = 0; i < 2; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::push_pop_registers);
    }
}
TEST_CASE("thumb_decode_load_store_halfword", "[decode]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_load_store_halfword.s.bin");
    for (int i = 0; i < 2; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::load_store_halfword);
    }
}
TEST_CASE("thumb_decode_sp_relative_load_store", "[decode]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_sp_relative_load_store.s.bin");
    for (int i = 0; i < 2; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::sp_relative_load_store);
    }
}
TEST_CASE("thumb_decode_load_address", "[decode]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_load_address.s.bin");
    for (int i = 0; i < 2; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::load_address);
    }
}
TEST_CASE("thumb_decode_load_store_with_immediate_offset", "[decode]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_load_store_with_immediate_offset.s.bin");
    for (int i = 0; i < 2; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::load_store_with_immediate_offset);
    }
}
TEST_CASE("thumb_decode_load_store_with_register_offset", "[decode]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_load_store_with_register_offset.s.bin");
    for (int i = 0; i < 2; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::load_store_with_register_offset);
    }
}
TEST_CASE("thumb_decode_load_store_sign_extended_byte_halfword", "[decode]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_load_store_sign_extended_byte_halfword.s.bin");
    for (int i = 0; i < 3; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::load_store_sign_extended_byte_halfword);
    }
}
TEST_CASE("thumb_decode_pc_relative_load", "[decode]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_pc_relative_load.s.bin");
    for (int i = 0; i < 1; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::pc_relative_load);
    }
}
TEST_CASE("thumb_decode_hi_register_operations_branch_exchange", "[decode]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_hi_register_operations_branch_exchange.s.bin");
    for (int i = 0; i < 5; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::hi_register_operations_branch_exchange);
    }
}
TEST_CASE("thumb_decode_alu_operations", "[decode]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_alu_operations.s.bin");
    for (int i = 0; i < 16; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::alu_operations);
    }
}
TEST_CASE("thumb_decode_move_compare_add_subtract_immediate", "[decode]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_move_compare_add_subtract_immediate.s.bin");
    for (int i = 0; i < 4; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::move_compare_add_subtract_immediate);
    }
}
TEST_CASE("thumb_decode_add_subtract", "[decode]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_add_subtract.s.bin");
    for (int i = 0; i < 4; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::add_subtract);
    }
}
TEST_CASE("thumb_decode_move_shifted_register", "[decode]") {
    const auto data = read_binary_from_file<u16>("assembly/thumb/decode/test_thumb_decode_move_shifted_register.s.bin");
    for (int i = 0; i < 3; ++i) {
        const u16 opcode = data[entrypoint + i];
        const auto instr = arm7tdmi::thumb::decode(opcode);
        REQUIRE(instr == arm7tdmi::thumb::instruction::move_shifted_register);
    }
}

#endif