//
// Created by talexander on 9/6/2024.
//

#pragma once

#include <arm7tdmi/common.h>
#include "decoder.h"
#include "register.h"
#include "util.h"

namespace arm7tdmi {

    class memory_interface;

    class cpu final {
    public:

        cpu_registers registers = {};

        explicit cpu(memory_interface* memory);
        ~cpu() = default;

        [[nodiscard]] inline cpu_state get_state() const { return _state; }

        void execute(arm::instruction instr, u32 opcode);
        void execute(thumb::instruction instr, u16 opcode);

        void execute_arm_branch_and_exchange(u32 instr);
        void execute_arm_block_data_transfer(u32 instr);
        void execute_arm_branch(u32 instr);
        void execute_arm_software_interrupt(u32 instr);
        void execute_arm_undefined(u32 instr);
        void execute_arm_single_data_transfer(u32 instr);
        void execute_arm_single_data_swap(u32 instr);
        void execute_arm_multiply(u32 instr);
        void execute_arm_multiply_long(u32 instr);
        void execute_arm_halfword_data_transfer_register(u32 instr);
        void execute_arm_halfword_data_transfer_immediate(u32 instr);
        void execute_arm_psr_transfer_mrs(u32 instr);
        void execute_arm_psr_transfer_msr(u32 instr);
        void execute_arm_data_processing(u32 instr);
        void execute_arm_unknown(u32 instr);

        [[nodiscard]] bool check_condition(u32 instr) const;

        void execute_thumb_software_interrupt(u16 instr);
        void execute_thumb_unconditional_branch(u16 instr);
        void execute_thumb_conditional_branch(u16 instr);
        void execute_thumb_multiple_load_store(u16 instr);
        void execute_thumb_long_branch_with_link(u16 instr);
        void execute_thumb_add_offset_to_stack_pointer(u16 instr);
        void execute_thumb_push_pop_registers(u16 instr);
        void execute_thumb_load_store_halfword(u16 instr);
        void execute_thumb_sp_relative_load_store(u16 instr);
        void execute_thumb_load_address(u16 instr);
        void execute_thumb_load_store_with_immediate_offset(u16 instr);
        void execute_thumb_load_store_with_register_offset(u16 instr);
        void execute_thumb_load_store_sign_extended_byte_halfword(u16 instr);
        void execute_thumb_pc_relative_load(u16 instr);
        void execute_thumb_hi_register_operations_branch_exchange(u16 instr);
        void execute_thumb_alu_operations(u16 instr);
        void execute_thumb_move_compare_add_subtract_immediate(u16 instr);
        void execute_thumb_add_subtract(u16 instr);
        void execute_thumb_move_shifted_register(u16 instr);
        void execute_thumb_unknown(u16 instr);

    private:
        cpu_state _state = cpu_state::arm;
        memory_interface* _memory = nullptr;

    };
}
