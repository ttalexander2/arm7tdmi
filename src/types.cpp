//
// Created by talexander on 9/24/2024.
//

#include <arm7tdmi/types.h>

namespace arm7tdmi {
    const char * error_to_string(const error instr) {
        switch(instr) {
            case error::ALLOCATION_ERROR: return "Memory allocation error!";
            default: return "unknown error!";
        }
    }
}
