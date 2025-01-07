//
// Created by talexander on 1/2/2025.
//

#pragma once

#include <arm7tdmi/types.h>

namespace arm7tdmi {

    enum class cpu_state : u8 {
        arm = 0,
        thumb = 1
    };

    enum class cpu_mode : u32 {
        old_user       = 0x00,   // Old User Mode (backward compatibility)
        old_fiq        = 0x01,   // Old FIQ Mode
        old_irq        = 0x02,   // Old IRQ Mode
        old_supervisor = 0x03,   // Old Supervisor Mode
        user           = 0x10,   // User Mode (non-privileged)
        fiq            = 0x11,   // FIQ Mode
        irq            = 0x12,   // IRQ Mode
        supervisor     = 0x13,   // Supervisor Mode (SWI)
        abort          = 0x17,   // Abort Mode
        undefined      = 0x1B,   // Undefined Mode
        system         = 0x1F    // System Mode (privileged 'User' mode)
    };

    enum class condition_code : u8
    {
        equal = 0,
        nequal = 1,
        unsigned_higher_or_same = 2,
        unsigned_lower = 3,
        negative = 4,
        positive_or_zero = 5,
        overflow = 6,
        no_overflow = 7,
        unsigned_higher = 8,
        unsigned_lower_or_same = 9,
        greater_or_equal = 10,
        less_than = 11,
        greater_than = 12,
        less_than_or_equal = 13,
        always = 14,
        never = 15
    };
}