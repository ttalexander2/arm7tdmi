//
// Created by talexander on 9/23/2024.
//
#include <arm7tdmi/memory.h>
#include <arm7tdmi/cpu.h>

namespace arm7tdmi {
    basic_memory::basic_memory(const u64 size) noexcept : _size(size) {
        _memory = new u8[size];
    }

    basic_memory::~basic_memory() noexcept {
        delete[] _memory;
    }

    u64 basic_memory::size() const noexcept {
        return _size;
    }

    bool basic_memory::read_byte(const u32 address, u8* out) const noexcept {
        if (address >= _size) {
            return false;
        }
        *out = _memory[address];
        return true;
    }

    bool basic_memory::write_byte(const size_t address, const u8 value) noexcept {
        if (address >= _size) {
            return false;
        }
        _memory[address] = value;
        return true;
    }
}
