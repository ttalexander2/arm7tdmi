//
// Created by talexander on 9/9/2024.
//
#include <arm7tdmi/cpu.h>

namespace arm7tdmi {


    void cpu::execute(const arm::instruction instr, const u32 opcode) {
        switch(instr) {
            case arm::instruction::branch_and_exchange: execute_arm_branch_and_exchange(opcode); break;
            case arm::instruction::block_data_transfer: execute_arm_block_data_transfer(opcode); break;
            case arm::instruction::branch_and_branch_with_link: execute_arm_branch_and_branch_with_link(opcode); break;
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
        void cpu::execute(thumb::instruction instr, u16 opcode) {
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

    void cpu::execute_arm_branch_and_exchange(const u32 opcode) {
    }

    void cpu::execute_arm_block_data_transfer(const u32 opcode) {
    }

    void cpu::execute_arm_branch_and_branch_with_link(const u32 opcode) {
    }

    void cpu::execute_arm_software_interupt(const u32 opcode) {
    }

    void cpu::execute_arm_undefined(const u32 opcode) {
    }

    void cpu::execute_arm_single_data_transfer(const u32 opcode) {
    }

    void cpu::execute_arm_single_data_swap(const u32 opcode) {
    }

    void cpu::execute_arm_multiply(const u32 opcode) {
    }

    void cpu::execute_arm_multiply_long(const u32 opcode) {
    }

    void cpu::execute_arm_halfword_data_transfer_register(const u32 opcode) {
    }

    void cpu::execute_arm_halfword_data_transfer_immediate(const u32 opcode) {
    }

    void cpu::execute_arm_psr_transfer_mrs(const u32 opcode) {
    }

    void cpu::execute_arm_psr_transfer_msr(const u32 opcode) {
    }

    void cpu::execute_arm_data_processing(const u32 opcode) {
    }

    void cpu::execute_arm_unknown(const u32 opcode) {
    }

    void cpu::execute_thumb_software_interrupt(u16 opcode) {
    }

    void cpu::execute_thumb_unconditional_branch(u16 opcode) {
    }

    void cpu::execute_thumb_conditional_branch(u16 opcode) {
    }

    void cpu::execute_thumb_multiple_load_store(u16 opcode) {
    }

    void cpu::execute_thumb_long_branch_with_link(u16 opcode) {
    }

    void cpu::execute_thumb_add_offset_to_stack_pointer(u16 opcode) {
    }

    void cpu::execute_thumb_push_pop_registers(u16 opcode) {
    }

    void cpu::execute_thumb_load_store_halfword(u16 opcode) {
    }

    void cpu::execute_thumb_sp_relative_load_store(u16 opcode) {
    }

    void cpu::execute_thumb_load_address(u16 opcode) {
    }

    void cpu::execute_thumb_load_store_with_immediate_offset(u16 opcode) {
    }

    void cpu::execute_thumb_load_store_with_register_offset(u16 opcode) {
    }

    void cpu::execute_thumb_load_store_sign_extended_byte_halfword(u16 opcode) {
    }

    void cpu::execute_thumb_pc_relative_load(u16 opcode) {
    }

    void cpu::execute_thumb_hi_register_operations_branch_exchange(u16 opcode) {
    }

    void cpu::execute_thumb_alu_operations(u16 opcode) {
    }

    void cpu::execute_thumb_move_compare_add_subtract_immediate(u16 opcode) {
    }

    void cpu::execute_thumb_add_subtract(u16 opcode) {
    }

    void cpu::execute_thumb_move_shifted_register(u16 opcode) {
    }

    void cpu::execute_thumb_unknown(u16 opcode) {
    }


}

