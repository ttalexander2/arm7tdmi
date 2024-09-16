//
// Created by talexander on 9/3/2024.
//

#include <arm7tdmi/decoder.h>

namespace arm7tdmi {

    namespace arm {

        namespace {
            bool is_branch_and_exchange(const u32 opcode) {
                constexpr u32 format = 0x012fff10;
                constexpr u32 mask = 0x0ffffff0;
                return (opcode & mask) == format;
            }

            bool is_block_data_transfer(const u32 opcode) {
                constexpr u32 format = 0x08000000;
                constexpr u32 mask = 0x0e000000;
                return (opcode & mask) == format;
            }

            bool is_branch(const u32 opcode) {
                constexpr u32 branch_format = 0x0a000000;
                constexpr u32 link_format = 0x0b000000;
                constexpr u32 mask = 0x0f000000;
                const u32 format = opcode & mask;
                return format == branch_format || format == link_format;
            }

            bool is_software_interrupt(const u32 opcode) {
                constexpr u32 format = 0x0f000000;
                constexpr u32 mask = 0x0f000000;
                return (opcode & mask) == format;
            }

            bool is_undefined(const u32 opcode) {
                constexpr u32 format = 0x06000010;
                constexpr u32 mask = 0x0e000010;
                return (opcode & mask) == format;
            }

            bool is_single_data_transfer(const u32 opcode) {
                constexpr u32 format = 0x04000000;
                constexpr u32 mask = 0x0c000000;
                return (opcode & mask) == format;
            }

            bool is_single_data_swap(const u32 opcode) {
                constexpr u32 format = 0x00000090;
                constexpr u32 mask = 0x0f800ff0;
                return (opcode & mask) == format;
            }

            bool is_multiply(const u32 opcode) {
                constexpr u32 format = 0x00000090;
                constexpr u32 mask = 0x0f8000f0;
                return (opcode & mask) == format;
            }

            bool is_multiply_long(const u32 opcode) {
                constexpr u32 format = 0x00800090;
                constexpr u32 mask = 0x0f8000f0;
                return (opcode & mask) == format;
            }

            bool is_halfword_data_transfer_register(const u32 opcode) {
                constexpr u32 format = 0x00000090;
                constexpr u32 mask = 0x0e400f90;
                return (opcode & mask) == format;
            }

            bool is_halfword_data_transfer_immediate(const u32 opcode) {
                constexpr u32 format = 0x00400090;
                constexpr u32 mask = 0x0e400090;
                return (opcode & mask) == format;
            }

            bool is_psr_transfer_mrs(const u32 opcode) {
                constexpr u32 format = 0x010f0000;
                constexpr u32 mask = 0x0fbf0000;
                return (opcode & mask) == format;
            }

            bool is_psr_transfer_msr(const u32 opcode) {
                constexpr u32 format = 0x0120f000;
                constexpr u32 mask = 0x0db0f000;
                return (opcode & mask) == format;
            }

            bool is_data_processing(const u32 opcode) {
                constexpr u32 format = 0x00000000;
                constexpr u32 mask = 0x0c000000;
                return (opcode & mask) == format;
            }
        }

        instruction decode(const u32 opcode) {
            if (is_branch_and_exchange(opcode)) return instruction::branch_and_exchange;
            if (is_block_data_transfer(opcode)) return instruction::block_data_transfer;
            if (is_branch(opcode)) return instruction::branch;
            if (is_software_interrupt(opcode)) return instruction::software_interrupt;
            if (is_undefined(opcode)) return instruction::undefined;
            if (is_single_data_transfer(opcode)) return instruction::single_data_transfer;
            if (is_single_data_swap(opcode)) return instruction::single_data_swap;
            if (is_multiply(opcode)) return instruction::multiply;
            if (is_multiply_long(opcode)) return instruction::multiply_long;
            if (is_halfword_data_transfer_register(opcode)) return instruction::halfword_data_transfer_register;
            if (is_halfword_data_transfer_immediate(opcode)) return instruction::halfword_data_transfer_immediate;
            if (is_psr_transfer_mrs(opcode)) return instruction::psr_transfer_mrs;
            if (is_psr_transfer_msr(opcode)) return instruction::psr_transfer_msr;
            if (is_data_processing(opcode)) return instruction::data_processing;
            return instruction::unknown;
        }

        
        const char * instruction_to_string(const instruction instr) {
            switch(instr) {
                case instruction::branch_and_exchange: return "branch_and_exchange";
                case instruction::block_data_transfer: return "block_data_transfer";
                case instruction::branch: return "branch_and_branch_with_link";
                case instruction::software_interrupt: return "software_interupt";
                case instruction::undefined: return "undefined";
                case instruction::single_data_transfer: return "single_data_transfer";
                case instruction::single_data_swap: return "single_data_swap";
                case instruction::multiply: return "multiply";
                case instruction::multiply_long: return "multiply_long";
                case instruction::halfword_data_transfer_register: return "halfword_data_transfer_register";
                case instruction::halfword_data_transfer_immediate: return "halfword_data_transfer_immediate";
                case instruction::psr_transfer_mrs: return "psr_transfer_mrs";
                case instruction::psr_transfer_msr: return "psr_transfer_msr";
                case instruction::data_processing: return "data_processing";
                default: return "unknown";
            }
        }
    }

    namespace thumb {

        namespace {
            
            bool is_software_interrupt(const u16 opcode) {
                constexpr u16 format = 0xdf00;
                constexpr u16 mask = 0xff00;
                return (opcode & mask) == format;
            }

            bool is_unconditional_branch(const u16 opcode) {
                constexpr u16 format = 0xe000;
                constexpr u16 mask = 0xf800;
                return (opcode & mask) == format;
            }

            bool is_conditional_branch(const u16 opcode) {
                constexpr u16 format = 0xd000;
                constexpr u16 mask = 0xf000;
                return (opcode & mask) == format;
            }

            bool is_multiple_load_store(const u16 opcode) {
                constexpr u16 format = 0xc000;
                constexpr u16 mask = 0xf000;
                return (opcode & mask) == format;
            }

            bool is_long_branch_with_link(const u16 opcode) {
                constexpr u16 format = 0xf000;
                constexpr u16 mask = 0xf000;
                return (opcode & mask) == format;
            }

            bool is_add_offset_to_stack_pointer(const u16 opcode) {
                constexpr u16 format = 0xb000;
                constexpr u16 mask = 0xff00;
                return (opcode & mask) == format;
            }

            bool is_push_pop_registers(const u16 opcode) {
                constexpr u16 format = 0xb400;
                constexpr u16 mask = 0xf600;
                return (opcode & mask) == format;
            }

            bool is_load_store_halfword(const u16 opcode) {
                constexpr u16 format = 0x8000;
                constexpr u16 mask = 0xf000;
                return (opcode & mask) == format;
            }

            bool is_sp_relative_load_store(const u16 opcode) {
                constexpr u16 format = 0x9000;
                constexpr u16 mask = 0xf000;
                return (opcode & mask) == format;
            }

            bool is_load_address(const u16 opcode) {
                constexpr u16 format = 0xa000;
                constexpr u16 mask = 0xf000;
                return (opcode & mask) == format;
            }

            bool is_load_store_with_immediate_offset(const u16 opcode) {
                constexpr u16 format = 0x6000;
                constexpr u16 mask = 0xe000;
                return (opcode & mask) == format;
            }

            bool is_load_store_with_register_offset(const u16 opcode) {
                constexpr u16 format = 0x5000;
                constexpr u16 mask = 0xf200;
                return (opcode & mask) == format;
            }

            bool is_load_store_sign_extended_byte_halfword(const u16 opcode) {
                constexpr u16 format = 0x5200;
                constexpr u16 mask = 0xf200;
                return (opcode & mask) == format;
            }

            bool is_pc_relative_load(const u16 opcode) {
                constexpr u16 format = 0x4800;
                constexpr u16 mask = 0xf800;
                return (opcode & mask) == format;
            }

            bool is_hi_register_operations_branch_exchange(const u16 opcode) {
                constexpr u16 format = 0x4400;
                constexpr u16 mask = 0xfc00;
                return (opcode & mask) == format;
            }

            bool is_alu_operations(const u16 opcode) {
                constexpr u16 format = 0x4000;
                constexpr u16 mask = 0xfc00;
                return (opcode & mask) == format;
            }

            bool is_move_compare_add_subtract_immediate(const u16 opcode) {
                constexpr u16 format = 0x2000;
                constexpr u16 mask = 0xe000;
                return (opcode & mask) == format;
            }

            bool is_add_subtract(const u16 opcode) {
                constexpr u16 format = 0x1800;
                constexpr u16 mask = 0xf800;
                return (opcode & mask) == format;
            }

            bool is_move_shifted_register(const u16 opcode) {
                constexpr u16 format = 0x0000;
                constexpr u16 mask = 0xe000;
                return (opcode & mask) == format;
            }
            
        }

        instruction decode(const u16 opcode) {
            if (is_software_interrupt(opcode)) return instruction::software_interrupt;
            if (is_unconditional_branch(opcode)) return instruction::unconditional_branch;
            if (is_conditional_branch(opcode)) return instruction::conditional_branch;
            if (is_multiple_load_store(opcode)) return instruction::multiple_load_store;
            if (is_long_branch_with_link(opcode)) return instruction::long_branch_with_link;
            if (is_add_offset_to_stack_pointer(opcode)) return instruction::add_offset_to_stack_pointer;
            if (is_push_pop_registers(opcode)) return instruction::push_pop_registers;
            if (is_load_store_halfword(opcode)) return instruction::load_store_halfword;
            if (is_sp_relative_load_store(opcode)) return instruction::sp_relative_load_store;
            if (is_load_address(opcode)) return instruction::load_address;
            if (is_load_store_with_immediate_offset(opcode)) return instruction::load_store_with_immediate_offset;
            if (is_load_store_with_register_offset(opcode)) return instruction::load_store_with_register_offset;
            if (is_load_store_sign_extended_byte_halfword(opcode)) return instruction::load_store_sign_extended_byte_halfword;
            if (is_pc_relative_load(opcode)) return instruction::pc_relative_load;
            if (is_hi_register_operations_branch_exchange(opcode)) return instruction::hi_register_operations_branch_exchange;
            if (is_alu_operations(opcode)) return instruction::alu_operations;
            if (is_move_compare_add_subtract_immediate(opcode)) return instruction::move_compare_add_subtract_immediate;
            if (is_add_subtract(opcode)) return instruction::add_subtract;
            if (is_move_shifted_register(opcode)) return instruction::move_shifted_register;
            return instruction::unknown;
        }

        const char * instruction_to_string(const instruction instr) {
            switch(instr) {
                case instruction::software_interrupt: return "software_interrupt";
                case instruction::unconditional_branch: return "unconditional_branch";
                case instruction::conditional_branch: return "conditional_branch";
                case instruction::multiple_load_store: return "multiple_load_store";
                case instruction::long_branch_with_link: return "long_branch_with_link";
                case instruction::add_offset_to_stack_pointer: return "add_offset_to_stack_pointer";
                case instruction::push_pop_registers: return "push_pop_registers";
                case instruction::load_store_halfword: return "load_store_halfword";
                case instruction::sp_relative_load_store: return "sp_relative_load_store";
                case instruction::load_address: return "load_address";
                case instruction::load_store_with_immediate_offset: return "load_store_with_immediate_offset";
                case instruction::load_store_with_register_offset: return "load_store_with_register_offset";
                case instruction::load_store_sign_extended_byte_halfword: return "load_store_sign_extended_byte_halfword";
                case instruction::pc_relative_load: return "pc_relative_load";
                case instruction::hi_register_operations_branch_exchange: return "hi_register_operations_branch_exchange";
                case instruction::alu_operations: return "alu_operations";
                case instruction::move_compare_add_subtract_immediate: return "move_compare_add_subtract_immediate";
                case instruction::add_subtract: return "add_subtract";
                case instruction::move_shifted_register: return "move_shifted_register";
                default: return "unknown";
            }
        }
    }


}
