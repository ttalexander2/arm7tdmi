//
// Created by talexander on 9/23/2024.
//
#include <arm7tdmi/memory.h>

#include "arm7tdmi/cpu.h"

namespace arm7tdmi {
    basic_memory::basic_memory(u64 size) : _size(size) {
        _memory = new u32[size];
    }

    u32 basic_memory::read_arm(u64 address) const {
        if (_memory && address < _size) {
            return _memory[address];
        }
        return 0;
    }

    bool basic_memory::write_arm(u64 address, u32 value) {
        if (!_memory || address >= _size) {
            return false;
        }
        _memory[address] = value;
        return true;
    }

    u16 basic_memory::read_thumb(u64 address) const {
        if (_memory && address < _size * 2u) {
            return reinterpret_cast<u16*>(_memory)[address];
        }
        return 0;
    }

    bool basic_memory::write_thumb(u64 address, u16 value) {
        if (!_memory || address >= _size * 2u) {
            return false;
        }
        reinterpret_cast<u16*>(_memory)[address] = value;
        return true;
    }

    u64 basic_memory::get_size(cpu_mode mode) const {
        if (mode == cpu_mode::arm) {
            return _size;
        }
        return _size * 2;
    }
}
