//
// Created by talexander on 9/23/2024.
//

#pragma once
#include <limits>
#include <type_traits>

#include "types.h"

namespace arm7tdmi {

    class cpu;

    class allocator {
        [[nodiscard]] u32* allocate(u64 n) noexcept;
        void deallocate(const u32* p) noexcept;
    };

    template <u32 Size, typename Allocator = allocator>
    class memory_interface final {
        static_assert(std::is_same_v<decltype(&Allocator::allocate),
                             u32* (Allocator::*)(u64)>, "Allocator must include 'allocate' function: u32* allocate(uint64_t)");
        static_assert(std::is_same_v<decltype(&Allocator::deallocate),
                             void (Allocator::*)(const u32*)>, "Allocator must include 'deallocate' function: deallocate(const u32* p)");
        friend class cpu;
    public:
        memory_interface();
        ~memory_interface();
    private:
        u32* data = nullptr;
    };

    template<u32 Size, typename Allocator>
    memory_interface<Size, Allocator>::memory_interface() {
        data = Allocator::allocate(Size);
    }

    template<u32 Size, typename Allocator>
    memory_interface<Size, Allocator>::~memory_interface() {
        Allocator::deallocate(data);
    }
}
