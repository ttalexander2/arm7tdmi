//
// Created by talexander on 9/3/2024.
//

#pragma once

#include "types.h"

namespace arm7tdmi {

    namespace arm {

        enum class instruction : u8 {
            branch_and_exchange,
            block_data_transfer,
            branch,
            software_interupt,
            undefined,
            single_data_transfer,
            single_data_swap,
            multiply,
            multiply_long,
            halfword_data_transfer_register,
            halfword_data_transfer_immediate,
            psr_transfer_mrs,
            psr_transfer_msr,
            data_processing,
            unknown
        };

        const char* instruction_to_string(instruction instr);

        instruction decode(u32 opcode);

    }

    namespace thumb {

        enum class instruction : u8 {
            software_interrupt,
            unconditional_branch,
            conditional_branch,
            multiple_load_store,
            long_branch_with_link,
            add_offset_to_stack_pointer,
            push_pop_registers,
            load_store_halfword,
            sp_relative_load_store,
            load_address,
            load_store_with_immediate_offset,
            load_store_with_register_offset,
            load_store_sign_extended_byte_halfword,
            pc_relative_load,
            hi_register_operations_branch_exchange,
            alu_operations,
            move_compare_add_subtract_immediate,
            add_subtract,
            move_shifted_register,
            unknown
        };

        const char* instruction_to_string(instruction instr);

        instruction decode(u16 opcode);


    }



}
