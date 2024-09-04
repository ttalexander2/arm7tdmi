//
// Created by talexander on 9/4/2024.
//

#pragma once

#include "types.h"

#include <cstdint>

namespace arm7tdmi
{
    __forceinline constexpr bool bit_check(const u32 number, const u32 n)
    {
        return (number >> n) & 1u;
    }

    __forceinline constexpr bool bit_check_mask(const u32 number, const u32 mask)
    {
        return (number & mask) == mask;
    }

    __forceinline constexpr u32 bit_set(const u32 number, const u32 n)
    {
        return number | (1u << n);
    }

    __forceinline constexpr u32 bit_set_to(const u32 number, const u32 n, const bool value)
    {
        return (number & ~(1u << n)) | (static_cast<u32>(value) << n);
    }

    __forceinline constexpr u32 bit_toggle(const u32 number, const u32 n)
    {
        return number ^ (1u << n);
    }

    __forceinline constexpr u32 bit_clear(const u32 number, const u32 n)
    {
        return number & ~(1u << n);
    }

    __forceinline constexpr bool bit_check(const u16 number, const u16 n)
    {
        return (number >> n) & 1u;
    }

    __forceinline constexpr bool bit_check_mask(const u16 number, const u16 mask)
    {
        return (number & mask) == mask;
    }

    __forceinline constexpr u16 bit_set(const u16 number, const u16 n)
    {
        return number | (1u << n);
    }

    __forceinline constexpr u16 bit_set_to(const u16 number, const u16 n, const bool value)
    {
        return (number & ~(1u << n)) | (static_cast<u16>(value) << n);
    }

    __forceinline constexpr u16 bit_toggle(const u16 number, const u16 n)
    {
        return number ^ (1u << n);
    }

    __forceinline constexpr u16 bit_clear(const u16 number, const u16 n)
    {
        return number & ~(1u << n);
    }

    __forceinline constexpr bool bit_check(const u8 number, const u8 n)
    {
        return (number >> n) & 1u;
    }

    __forceinline constexpr bool bit_check_mask(const u8 number, const u8 mask)
    {
        return (number & mask) == mask;
    }

    __forceinline constexpr u8 bit_set(const u8 number, const u8 n)
    {
        return number | (1u << n);
    }

    __forceinline constexpr u8 bit_set_to(const u8 number, const u8 n, const bool value)
    {
        return (number & ~(1u << n)) | (static_cast<u8>(value) << n);
    }

    __forceinline constexpr u8 bit_toggle(const u8 number, const u8 n)
    {
        return number ^ (1u << n);
    }

    __forceinline constexpr u8 bit_clear(const u8 number, const u8 n)
    {
        return number & ~(1u << n);
    }


}
