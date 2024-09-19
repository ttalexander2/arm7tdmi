//
// Created by talexander on 9/19/2024.
//

#include <catch2/catch_test_macros.hpp>

#include <arm7tdmi/cpu.h>
#include "utility.h"

#ifdef TEST_COMPILED_ASSEMBLY


TEST_CASE("arm_instruction_branch", "[arm instructions]")
{
    const auto data = read_binary_from_file<u32>("assembly/arm/instructions/test_branch.s.bin");
    arm7tdmi::cpu cpu{};
    {
        cpu.registers.pc = 0x8000;
        const u32 b = data[cpu.registers.pc / sizeof(u32)];
        cpu.execute_arm_branch(b);
        REQUIRE(cpu.registers.pc == 0x8014);
    }
    {
        cpu.registers.pc = 0x8004;
        const u32 bl = data[0x8004 / sizeof(u32)];
        cpu.execute_arm_branch(bl);
        REQUIRE(cpu.registers.pc == 0x8014);
        REQUIRE(cpu.registers.lr == 0x8008);
    }
    {
        // branch and link, carry clear. i.e. only branches if c is 0
        cpu.registers.pc = 0x8008;
        const u32 blcc = data[0x8008 / sizeof(u32)];
        cpu.execute_arm_branch(blcc);

        // carry is clear, so should branch and link
        REQUIRE(cpu.registers.pc == 0x8014);
        REQUIRE(cpu.registers.lr == 0x800c);
    }
    {
        // branch and link, carry clear. i.e. only branches if c is 0
        cpu.registers.pc = 0x8008;
        const u32 blcc = data[0x8008 / sizeof(u32)];
        cpu.registers.cpsr.set_c(true);
        cpu.execute_arm_branch(blcc);

        // carry is not clear, shouldn't branch or link. pc remains the same
        REQUIRE(cpu.registers.pc == 0x8008);
        cpu.registers.cpsr.set_c(false);
    }
    {
        // BEQ - Branch if equal (Z == 1)
        cpu.registers.pc = 0x800c;
        const u32 beq = data[0x800c / sizeof(u32)];

        // Set Z to 1, should branch
        cpu.registers.cpsr.set_z(true);
        cpu.execute_arm_branch(beq);
        REQUIRE(cpu.registers.pc == 0x8014);

        // Set Z to 0, should not branch. i.e. program counter doesn't change
        cpu.registers.pc = 0x800c;
        cpu.registers.cpsr.set_z(false);
        cpu.execute_arm_branch(beq);
        REQUIRE(cpu.registers.pc == 0x800c);
    }

}

#endif