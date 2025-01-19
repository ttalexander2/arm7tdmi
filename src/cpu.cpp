//
// Created by talexander on 9/9/2024.
//
#include <cassert>
#include <utility>
#include <arm7tdmi/cpu.h>
#include <arm7tdmi/memory.h>

namespace arm7tdmi {
    cpu::cpu(memory_interface *memory) : _memory(memory) {
    }

    void cpu::execute(const arm::instruction instr, const u32 opcode) {
        switch(instr) {
            case arm::instruction::branch_and_exchange: execute_arm_branch_and_exchange(opcode); break;
            case arm::instruction::block_data_transfer: execute_arm_block_data_transfer(opcode); break;
            case arm::instruction::branch: execute_arm_branch(opcode); break;
            case arm::instruction::software_interrupt: execute_arm_software_interrupt(opcode); break;
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
        assert(rn < 15u);

        const cpu_state exchange_mode = (registers.get(static_cast<Register>(rn)) & 1u) == 1u ? cpu_state::thumb : cpu_state::arm;

        if (_state == cpu_state::arm && exchange_mode == cpu_state::thumb)
        {
            registers.pc(registers.get(rn) - 1u); // set bit 0 to 1, use Rn - 1
        }
        else
        {
            registers.pc(registers.get(rn)); // Either in same mode, or switching to arm, use Rn
        }

        // if bit 0 of RN == 1 subsequent instructions are THUMB, else ARM
        _state = exchange_mode;
    }

    void cpu::execute_arm_block_data_transfer(const u32 instr) {
        if (!check_condition(instr))
            return;

        u8 register_list [16] = {};
        u8 register_list_n = 0;

        bool r15_in_list = false;

        for (u32 i = 0; i < 16; ++i) {
            if (util::bit_check(instr, i)) {
                register_list[register_list_n] = i;
                register_list_n++;

                if (i == 15) r15_in_list = true;
            }
        }

        const u8 base_register = (instr >> 16) & 0xf;
        const bool load = util::bit_check(instr, 20u);
        const bool write_back = util::bit_check(instr, 21u);
        const bool psr = util::bit_check(instr, 22u);
        const bool up = util::bit_check(instr, 23u);
        const bool pre_indexing = util::bit_check(instr, 24u);

        u32 base_addr = registers.get(base_register);
        u32 write_back_addr = base_addr + ((up ? 1 : -1) * sizeof(u32) * register_list_n);

        //const u32 offset = register_list_n * sizeof(u32); // Number of registers * word (size of register)


        const auto mode = registers.cpsr_get_mode();
        // if user bank transfer, we'll temporarily set the mode to user
        if (!(psr && r15_in_list)) {
            registers.cpsr_set_mode(cpu_mode::user);
        }

        //u32 addr = base_addr + (((up ? 1 : -1)) * (psr ? sizeof(u32) : 0)) - ((up ? 0 : (register_list_n - 1) * sizeof(u32)));
        u32 addr = base_addr;

        // Store in memory
        if (!_memory) {
            // Something went very wrong
            return;
        }

        for (int i = 0; i < register_list_n; ++i) {
            if (pre_indexing) {
                addr += sizeof(u32);
            }
            if (load) {
                u32 result;
                if (_memory->read<u32>(addr, &result)) {
                    registers.set(register_list[i], result);
                }
                else {
                    //TODO(Thomas): Address invalid, raise abort signal
                    return;
                }
            }
            else {
                if (!_memory->write<u32>(addr, registers.get(register_list[i]))) {
                    // TODO(Thomas): Address invalid, raise data abort signal
                    return;
                }
            }
            if (!pre_indexing) {
                addr += sizeof(u32);
            }
        }


        if (psr && r15_in_list) {
            // Instruction is LDM and R15 in list, mode changes
            registers.cpsr(registers.spsr());
        } else {
            // Restore mode to previous (user bank transfer)
            registers.cpsr_set_mode(mode);
        }

        // Write back address to base register
        if (write_back) {
            registers.set(base_register, base_addr);
        }

    }

    void cpu::execute_arm_branch(const u32 instr) {

        if (!check_condition(instr))
            return;

        const u32 opcode = util::bit_check(instr, 24);

        const i32 offset = util::twos_compliment(instr, 24);
        const u32 calling_pc = registers.pc();
        registers.pc(calling_pc + 8u + offset * 4u);

        if (opcode == 1u) // branch with link - return address in REG_LR
        {
            registers.lr(calling_pc + 4u);
        }
    }

    void cpu::execute_arm_software_interrupt(const u32 instr) {
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

        const u8 N = registers.cpsr_get_n();
        const u8 Z = registers.cpsr_get_z();
        const u8 C = registers.cpsr_get_c();
        const u8 V = registers.cpsr_get_v();

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

