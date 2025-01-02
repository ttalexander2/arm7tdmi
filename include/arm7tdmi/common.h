//
// Created by talexander on 1/2/2025.
//

#pragma once

#include <arm7tdmi/types.h>

namespace arm7tdmi {

    enum class cpu_mode : u8 {
        arm,
        thumb
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