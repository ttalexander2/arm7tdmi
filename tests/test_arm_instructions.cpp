//
// Created by talexander on 9/19/2024.
//

#include <catch2/catch_test_macros.hpp>

#include <arm7tdmi/cpu.h>

#include "utility.h"
#include "arm7tdmi/memory.h"

#ifdef TEST_COMPILED_ASSEMBLY


TEST_CASE("arm_instruction_branch", "[arm instructions]")
{
    const auto data = read_binary_from_file<u32>("assembly/arm/instructions/test_branch.s.bin");
    auto memory = arm7tdmi::basic_memory(60);
    auto cpu = arm7tdmi::cpu(&memory);
    {
        cpu.registers.pc(0x8000);
        const u32 b = data[cpu.registers.pc() / sizeof(u32)];
        cpu.execute_arm_branch(b);
        REQUIRE(cpu.registers.pc() == 0X8014);
    }
    {
        cpu.registers.pc(0x8004);
        const u32 bl = data[0x8004 / sizeof(u32)];
        cpu.execute_arm_branch(bl);
        REQUIRE(cpu.registers.pc() == 0X8014);
        REQUIRE(cpu.registers.lr() == 0X8008);
    }
    {
        // branch and link, carry clear. i.e. only branches if c is 0
        cpu.registers.pc(0x8008);
        const u32 blcc = data[0x8008 / sizeof(u32)];
        cpu.execute_arm_branch(blcc);

        // carry is clear, so should branch and link
        REQUIRE(cpu.registers.pc() == 0X8014);
        REQUIRE(cpu.registers.lr() == 0X800C);
    }
    {
        // branch and link, carry clear. i.e. only branches if c is 0
        cpu.registers.pc(0x8008);
        const u32 blcc = data[0x8008 / sizeof(u32)];
        cpu.registers.cpsr_set_c(true);
        cpu.execute_arm_branch(blcc);

        // carry is not clear, shouldn't branch or link. pc remains the same
        REQUIRE(cpu.registers.pc() == 0X8008);
        cpu.registers.cpsr_set_c(false);
    }
    {
        // BEQ - Branch if equal (Z == 1)
        cpu.registers.pc(0x800c);
        const u32 beq = data[0x800c / sizeof(u32)];

        // Set Z to 1, should branch
        cpu.registers.cpsr_set_z(true);
        cpu.execute_arm_branch(beq);
        REQUIRE(cpu.registers.pc() == 0X8014);

        // Set Z to 0, should not branch. i.e. program counter doesn't change
        cpu.registers.pc(0x800c);
        cpu.registers.cpsr_set_z(false);
        cpu.execute_arm_branch(beq);
        REQUIRE(cpu.registers.pc() == 0X800C);
    }
}

TEST_CASE("arm_instruction_branch_and_exchange", "[arm instructions]")
{
    const auto data = read_binary_from_file<u32>("assembly/arm/instructions/test_branch_and_exchange.s.bin");
    {
        auto memory = arm7tdmi::basic_memory(60);
        auto cpu = arm7tdmi::cpu(&memory);
        cpu.registers.pc(0x8004); // BX r0

        // Since we're switching to thumb, we expect the address to be misalligned by 1
        // This matches the expected usage of BX, where we would first store the
        // Destination label + 1 to switch to thumb
        cpu.registers.r0(0x8010 + 1u);

        const u32 b = data[cpu.registers.pc() / sizeof(u32)];
        cpu.execute_arm_branch_and_exchange(b);
        REQUIRE(cpu.registers.pc() == 0X8010);
        REQUIRE(cpu.get_state() == arm7tdmi::cpu_state::thumb);
    }
    {
        auto memory = arm7tdmi::basic_memory(60);
        auto cpu = arm7tdmi::cpu(&memory);
        cpu.registers.pc(0x800c); // BX r1

        // Since we're branching to another ARM section, we'll just store the address
        cpu.registers.r1(0x8014);

        const u32 b = data[cpu.registers.pc() / sizeof(u32)];
        cpu.execute_arm_branch_and_exchange(b);
        REQUIRE(cpu.registers.pc() == 0X8014);
        REQUIRE(cpu.get_state() == arm7tdmi::cpu_state::arm);
    }
}

TEST_CASE("arm_instruction_block_data_transfer", "[arm instructions]")
{
    const auto data = read_binary_from_file<u32>("assembly/arm/instructions/test_block_data_transfer.s.bin");
    auto memory = arm7tdmi::basic_memory(256);
    auto cpu = arm7tdmi::cpu(&memory);
    {
        cpu.registers.cpsr_set_mode(arm7tdmi::cpu_mode::supervisor);
        // write 3 values to the stack
        memory.write<u32>(0x0, 33);
        memory.write<u32>(0x1, 44);
        memory.write<u32>(0x2, 55);
        cpu.registers.sp(0x0);
        cpu.registers.pc(0x8000);
        const u32 b = data[cpu.registers.pc() / sizeof(u32)];
        auto instr = arm7tdmi::arm::decode(b);
        REQUIRE(instr == arm7tdmi::arm::instruction::block_data_transfer);
        fmt::println("{:b}", b);
        cpu.execute_arm_block_data_transfer(b);
        REQUIRE(cpu.registers.r0() == 33);
        REQUIRE(cpu.registers.r1() == 44);
        REQUIRE(cpu.registers.r2() == 55);
    }
}

#endif