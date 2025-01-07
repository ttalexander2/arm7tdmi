//
// Created by talexander on 9/23/2024.
//
#include <arm7tdmi/memory.h>
#include <arm7tdmi/cpu.h>

namespace arm7tdmi {
    basic_memory::basic_memory(const u64 size) : _size(size) {
        _memory = new u8[size];
    }

    basic_memory::~basic_memory() {
        delete[] _memory;
    }

    u64 basic_memory::size() const {
        return _size;
    }

    u8 basic_memory::read_byte(const u32 address) const {
        if (address >= _size) {
            return 0;
        }
        return _memory[address];
    }

    void basic_memory::write_byte(const size_t address, const u8 value) {
        if (address >= _size) {
            return;
        }
        _memory[address] = value;
    }
}
