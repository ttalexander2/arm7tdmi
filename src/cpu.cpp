//
// Created by talexander on 9/9/2024.
//
#include <cassert>
#include <arm7tdmi/cpu.h>

namespace arm7tdmi {


    void cpu::execute(const arm::instruction instr, const u32 opcode) {
        switch(instr) {
            case arm::instruction::branch_and_exchange: execute_arm_branch_and_exchange(opcode); break;
            case arm::instruction::block_data_transfer: execute_arm_block_data_transfer(opcode); break;
            case arm::instruction::branch: execute_arm_branch(opcode); break;
            case arm::instruction::software_interupt: execute_arm_software_interupt(opcode); break;
            case arm::instruction::undefined: execute_arm_undefined(opcode); break;
            case arm::instruction::single_data_transfer: execute_arm_single_data_transfer(opcode); break;
            case arm::instruction::single_data_swap: execute_arm_single_data_swap(opcode); break;
            case arm::instruction::multiply: execute_arm_multiply(opcode); break;
            case arm::instruction::multiply_long: execute_arm_multiply_long(opcode); break;
            case arm::instruction::halfword_data_transfer_register: execute_arm_halfword_data_transfer_register(opcode); break;
            case arm::instruction::halfword_data_transfer_immediate: execute_arm_halfword_data_transfer_immediate(opcode); break;
            case arm::instruction::psr_transfer_mrs: execute_arm_psr_transfer_mrs(opcode); break;
            case arm::instruction::psr_transfer_msr: execute_arm_psr_transfer_msr(opcode); break;
            case arm::instruction::data_processing: execute_arm_data_processing(opcode); break;
            default:
            case arm::instruction::unknown: execute_arm_unknown(opcode);
        }
    }
        void cpu::execute(const thumb::instruction instr, const u16 opcode) {
        switch(instr) {
            case thumb::instruction::software_interrupt: execute_thumb_software_interrupt(opcode); break;
            case thumb::instruction::unconditional_branch: execute_thumb_unconditional_branch(opcode); break;
            case thumb::instruction::conditional_branch: execute_thumb_conditional_branch(opcode); break;
            case thumb::instruction::multiple_load_store: execute_thumb_multiple_load_store(opcode); break;
            case thumb::instruction::long_branch_with_link: execute_thumb_long_branch_with_link(opcode); break;
            case thumb::instruction::add_offset_to_stack_pointer: execute_thumb_add_offset_to_stack_pointer(opcode); break;
            case thumb::instruction::push_pop_registers: execute_thumb_push_pop_registers(opcode); break;
            case thumb::instruction::load_store_halfword: execute_thumb_load_store_halfword(opcode); break;
            case thumb::instruction::sp_relative_load_store: execute_thumb_sp_relative_load_store(opcode); break;
            case thumb::instruction::load_address: execute_thumb_load_address(opcode); break;
            case thumb::instruction::load_store_with_immediate_offset: execute_thumb_load_store_with_immediate_offset(opcode); break;
            case thumb::instruction::load_store_with_register_offset: execute_thumb_load_store_with_register_offset(opcode); break;
            case thumb::instruction::load_store_sign_extended_byte_halfword: execute_thumb_load_store_sign_extended_byte_halfword(opcode); break;
            case thumb::instruction::pc_relative_load: execute_thumb_pc_relative_load(opcode); break;
            case thumb::instruction::hi_register_operations_branch_exchange: execute_thumb_hi_register_operations_branch_exchange(opcode); break;
            case thumb::instruction::alu_operations: execute_thumb_alu_operations(opcode); break;
            case thumb::instruction::move_compare_add_subtract_immediate: execute_thumb_move_compare_add_subtract_immediate(opcode); break;
            case thumb::instruction::add_subtract: execute_thumb_add_subtract(opcode); break;
            case thumb::instruction::move_shifted_register: execute_thumb_move_shifted_register(opcode); break;
            default:
            case thumb::instruction::unknown: execute_thumb_unknown(opcode); break;

        }
    }

    void cpu::execute_arm_branch_and_exchange(const u32 instr) {

        if (!check_condition(instr))
            return;

        // register number
        const u32 rn = instr & 0xf;
        assert(rn < 15);

        const cpu_mode exchange_mode = (instr & 1u) == 1u ? cpu_mode::thumb : cpu_mode::arm;

        if (mode == cpu_mode::arm && exchange_mode == cpu_mode::thumb)
        {
            registers.pc = register_data[rn | 1u] - 1u; // set bit 0 to 1, use Rn - 1
        }
        else
        {
            registers.pc = register_data[rn]; // Either in same mode, or switching to arm, use Rn
        }

        // if bit 0 of RN == 1 subsequent instructions are THUMB, else ARM
        mode = exchange_mode;
    }

    void cpu::execute_arm_block_data_transfer(const u32 instr) {

    }

    void cpu::execute_arm_branch(const u32 instr) {

        if (!check_condition(instr))
            return;

        const u32 opcode = (instr >> 23) & 1;

        const u32 offset = instr & 0x00ffffff;

        registers.pc = registers.pc + 8 + offset * 4;

        if (opcode == 1) // branch with link - return address in REG_LR
        {
            registers.lr = registers.pc + 4;
        }
    }

    void cpu::execute_arm_software_interupt(const u32 instr) {
    }

    void cpu::execute_arm_undefined(const u32 instr) {
    }

    void cpu::execute_arm_single_data_transfer(const u32 instr) {
    }

    void cpu::execute_arm_single_data_swap(const u32 instr) {
    }

    void cpu::execute_arm_multiply(const u32 instr) {
    }

    void cpu::execute_arm_multiply_long(const u32 instr) {
    }

    void cpu::execute_arm_halfword_data_transfer_register(const u32 instr) {
    }

    void cpu::execute_arm_halfword_data_transfer_immediate(const u32 instr) {
    }

    void cpu::execute_arm_psr_transfer_mrs(const u32 instr) {
    }

    void cpu::execute_arm_psr_transfer_msr(const u32 instr) {
    }

    void cpu::execute_arm_data_processing(const u32 instr) {
    }

    void cpu::execute_arm_unknown(const u32 instr) {
    }

    bool cpu::check_condition(const u32 instr) const {

        u32 cond = (instr >> 28) & 0xf;

        const u8 N = registers.cpsr.get_n();
        const u8 Z = registers.cpsr.get_z();
        const u8 C = registers.cpsr.get_c();
        const u8 V = registers.cpsr.get_v();

        switch(static_cast<condition_code>(cond))
        {
            case condition_code::equal:
                return Z == 1;
            case condition_code::nequal:
                return Z == 0;
            case condition_code::unsigned_higher_or_same:
                return C == 1;
            case condition_code::unsigned_lower:
                return C == 0;
            case condition_code::negative:
                return N == 1;
            case condition_code::positive_or_zero:
                return N == 0;
            case condition_code::overflow:
                return V == 1;
            case condition_code::unsigned_higher:
                return C == 1 && Z == 0;
            case condition_code::unsigned_lower_or_same:
                return C == 0 || Z == 1;
            case condition_code::greater_or_equal:
                return N == V;
            case condition_code::less_than:
                return N != V;
            case condition_code::greater_than:
                return Z == 0 && N == V;
            case condition_code::less_than_or_equal:
                return Z == 1 || N != V;
            case condition_code::always:
                return true;
            case condition_code::never:
                return false;
            default:
                return true;
        }
    }

    void cpu::execute_thumb_software_interrupt(u16 instr) {
    }

    void cpu::execute_thumb_unconditional_branch(u16 instr) {
    }

    void cpu::execute_thumb_conditional_branch(u16 instr) {
    }

    void cpu::execute_thumb_multiple_load_store(u16 instr) {
    }

    void cpu::execute_thumb_long_branch_with_link(u16 instr) {
    }

    void cpu::execute_thumb_add_offset_to_stack_pointer(u16 instr) {
    }

    void cpu::execute_thumb_push_pop_registers(u16 instr) {
    }

    void cpu::execute_thumb_load_store_halfword(u16 instr) {
    }

    void cpu::execute_thumb_sp_relative_load_store(u16 instr) {
    }

    void cpu::execute_thumb_load_address(u16 instr) {
    }

    void cpu::execute_thumb_load_store_with_immediate_offset(u16 instr) {
    }

    void cpu::execute_thumb_load_store_with_register_offset(u16 instr) {
    }

    void cpu::execute_thumb_load_store_sign_extended_byte_halfword(u16 instr) {
    }

    void cpu::execute_thumb_pc_relative_load(u16 instr) {
    }

    void cpu::execute_thumb_hi_register_operations_branch_exchange(u16 instr) {
    }

    void cpu::execute_thumb_alu_operations(u16 instr) {
    }

    void cpu::execute_thumb_move_compare_add_subtract_immediate(u16 instr) {
    }

    void cpu::execute_thumb_add_subtract(u16 instr) {
    }

    void cpu::execute_thumb_move_shifted_register(u16 instr) {
    }

    void cpu::execute_thumb_unknown(u16 instr) {
    }


}

