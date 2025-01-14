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
    auto memory = arm7tdmi::basic_memory(4096);
    auto cpu = arm7tdmi::cpu(&memory);
    {

        {
            cpu.registers.cpsr_set_mode(arm7tdmi::cpu_mode::user);

            // write 3 values to the stack
            memory.write<u32>(0x0000, 0);
            memory.write<u32>(0x0004, 1);
            memory.write<u32>(0x0008, 2);

            for (int i = 0; i < 13; ++i)
            {
                cpu.registers.set(i, i * 5);
            }

            cpu.registers.sp(0x0000);
            cpu.registers.lr(0x0000);
            cpu.registers.pc(0x8000);
        }

        // LDMFD SP!,{R0,R1,R2}        @ Unstack 3 registers.
        {
            const u32 b = data[cpu.registers.pc() / sizeof(u32)];
            auto instr = arm7tdmi::arm::decode(b);

            REQUIRE(instr == arm7tdmi::arm::instruction::block_data_transfer);
            cpu.execute(instr, b);

            REQUIRE(cpu.registers.r0() == 0);
            REQUIRE(cpu.registers.r1() == 1);
            REQUIRE(cpu.registers.r2() == 2);
            REQUIRE(cpu.registers.sp() == 0x000C);
        }

        // STMIA R0,{R0-R15}           @ Save all registers.
        {
            const u32 b = data[(cpu.registers.pc() + sizeof(u32)) / sizeof(u32)];
            auto instr = arm7tdmi::arm::decode(b);

            REQUIRE(instr == arm7tdmi::arm::instruction::block_data_transfer);
            cpu.execute(instr, b);

            u32 val = 0;
            u32 base_addr = 0x0000;

            // Registers 0 - 2 should have the values loaded read from memory from the previous instruction
            for (int i = 0; i < 3; ++i)
            {
                REQUIRE(memory.read<u32>(base_addr + i * sizeof(u32), &val));
                REQUIRE(val == i);
            }

            // Registers 3 - 12 should have the original data stored (multiples of 5)
            for (int i = 4; i < 13; ++i) {
                REQUIRE(memory.read<u32>(base_addr + i * sizeof(u32), &val));
                REQUIRE(val == i * 5);
            }

            // Stack pointer shouldn't have changed???
            REQUIRE(memory.read<u32>(base_addr + 13 * sizeof(u32), &val));
            REQUIRE(val == 0x000C);

            // No branch so far, so this should still be 0'd
            REQUIRE(memory.read<u32>(base_addr + 14 * sizeof(u32), &val));
            REQUIRE(val == 0x0000);

            // We're manually loading instructions, so we're not incrementing PC at all
            REQUIRE(memory.read<u32>(base_addr + 15 * sizeof(u32), &val));
            REQUIRE(val == 0x8000);
        }

        // LDMFD SP!,{R15}             @ R15 <- (SP),CPSR unchanged.
        {
            cpu.registers.pc(0x8000);
            const u32 b = data[(cpu.registers.pc() + (sizeof(u32) * 2)) / sizeof(u32)];
            auto instr = arm7tdmi::arm::decode(b);

            u32 stack_ptr;
            memory.read<u32>(cpu.registers.sp(), &stack_ptr);
            u32 addr = cpu.registers.sp();

            REQUIRE(instr == arm7tdmi::arm::instruction::block_data_transfer);
            cpu.execute(instr, b);

            // Stack pointer should be stored in r15
            REQUIRE(cpu.registers.r15() == stack_ptr);

            // FD -> Full stack, descending
            // "SP is decremented when pushing/storing data, and incremented when popping/loading data"
            REQUIRE(cpu.registers.sp() == addr + sizeof(u32));
        }


        // LDMFD SP!,{R15}^            @ R15 <- (SP), CPSR <- SPSR_mode
        {
            // Allowed only in privileged modes, so we'll set to supervisor
            cpu.registers.cpsr_set_mode(arm7tdmi::cpu_mode::supervisor);

            cpu.registers.pc(0x8000);
            const u32 b = data[(cpu.registers.pc() + (sizeof(u32) * 3)) / sizeof(u32)];
            auto instr = arm7tdmi::arm::decode(b);

            u32 stack_ptr;
            memory.read<u32>(cpu.registers.sp(), &stack_ptr);
            u32 addr = cpu.registers.sp();
            u32 spsr = cpu.registers.spsr();

            REQUIRE(instr == arm7tdmi::arm::instruction::block_data_transfer);
            cpu.execute(instr, b);

            // Stack pointer should be stored in r15
            REQUIRE(cpu.registers.r15() == stack_ptr);

            // FD -> Full stack, descending
            // "SP is decremented when pushing/storing data, and incremented when popping/loading data"
            REQUIRE(cpu.registers.sp() == addr + sizeof(u32));

            REQUIRE(cpu.registers.cpsr() == spsr);
        }

        // STMFD R13,{R0-R14}^         @ Save user mode regs on stack
        {
            // Allowed only in privileged modes, so we'll set to supervisor
            cpu.registers.cpsr_set_mode(arm7tdmi::cpu_mode::supervisor);

            cpu.registers.pc(0x8000);
            const u32 b = data[(cpu.registers.pc() + (sizeof(u32) * 4)) / sizeof(u32)];
            auto instr = arm7tdmi::arm::decode(b);

            std::vector<u32> user_registers;
            for (int i = 0; i < 15; ++i)
            {
                user_registers.push_back(cpu.registers.get(i));
            }
            cpu.registers.sp(0x128);
            u32 old_sp = cpu.registers.sp();

            REQUIRE(instr == arm7tdmi::arm::instruction::block_data_transfer);
            cpu.execute(instr, b);

            // Stack pointer should be stored in r15
            for (int i = 0; i < 15; ++i)
            {
                u32 val;
                memory.read<u32>(cpu.registers.sp() + i * sizeof(u32), &val);
                REQUIRE(val == user_registers[i]);
            }

            REQUIRE(cpu.registers.r13() == old_sp);
        }

    }
}

#endif