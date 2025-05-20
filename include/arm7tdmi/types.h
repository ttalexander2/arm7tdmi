//
// Created by talexander on 9/3/2024.
//

#pragma once

#include <cstdint>
#include <string>
#include <vector>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint32_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;



namespace arm7tdmi {

    typedef u8 byte;
    typedef u16 halfword;
    typedef u32 word;

    enum class error : u8 {
        ALLOCATION_ERROR,
    };


    template <typename T, typename E = error, typename = std::enable_if_t<std::is_same_v<T, std::decay_t<T>>>>
    class result {
        union {
            T _data;
            E _error;
        };
        bool _valid;
    public:
        result() = delete;
        // ReSharper disable once CppNonExplicitConvertingConstructor
        result(T returnValue) noexcept : _data(returnValue), _valid(true) {} // NOLINT(*-explicit-constructor)
        // ReSharper disable once CppNonExplicitConvertingConstructor
        result(E errorValue) noexcept : _error(errorValue), _valid(false) {} // NOLINT(*-explicit-constructor)

        [[nodiscard]] bool valid() const noexcept { return _valid; }

        [[nodiscard]] T value() const noexcept { return std::move(_data); }
        [[nodiscard]] E error() const noexcept { return std::move(_error); }

        T* operator->() const noexcept { return &_data; }
    };

    const char * error_to_string(error instr) noexcept;

}

inline auto format_as(const arm7tdmi::error f) noexcept { return arm7tdmi::error_to_string(f); }
