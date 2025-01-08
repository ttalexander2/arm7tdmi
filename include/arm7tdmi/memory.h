//
// Created by talexander on 9/23/2024.
//

#pragma once
#include <limits>
#include <type_traits>

#include <arm7tdmi/common.h>

namespace arm7tdmi {

    class memory_interface {
    public:
        virtual ~memory_interface() = default;

        /**
         * 
         * @tparam T Type to read. Must be u8/byte, u16/halfword, or u32/word.
         * @param address 32-bit memory address.
         * @return Value stored the address.
         */
        template <typename T>
    	T read(u32 address) const;

        /**
         * 
         * @tparam T Type to write. Must be u8/byte, u16/halfword, or u32/word.
         * @param address 32-bit memory address.
         * @param value Value to write to memory at the address.
         */
        template <typename T>
    	void write(u32 address, T value);

        /**
         * 
         * @return Returns total memory block size in bytes
         */
        [[nodiscard]] virtual u64 size() const = 0;

    protected:
    	[[nodiscard]] virtual u8 read_byte(u32 address) const = 0;
    	virtual void write_byte(size_t address, u8 value) = 0;
    };

	class basic_memory final : public memory_interface {
    public:
		explicit basic_memory(u64 size);
		~basic_memory() override;

		[[nodiscard]] u32 size() const override;

	protected:
		[[nodiscard]] u8 read_byte(u32 address) const override;
		void write_byte(size_t address, u8 value) override;

	private:
		u8* _memory = nullptr;
	    u64 _size = 0;
    };

	template <typename T>
	T memory_interface::read(const u32 address) const {
		static_assert(std::is_same_v<T, u8> || std::is_same_v<T, u16> || std::is_same_v<T, u32>, "memory value must be u8/byte, u16/halfword, or u32/word");
		T value = 0;
		for (size_t i = 0; i < sizeof(T); ++i) {
			value |= static_cast<T>(read_byte(address + i)) << (i * 8);
		}
		return value;
	}

	template <typename T>
	void memory_interface::write(const u32 address, T value) {
		static_assert(std::is_same_v<T, u8> || std::is_same_v<T, u16> || std::is_same_v<T, u32>, "memory value must be u8/byte, u16/halfword, or u32/word");
		for (size_t i = 0; i < sizeof(T); ++i) {
			write_byte(address + i, static_cast<uint8_t>((value >> (i * 8)) & 0xFF));
		}
	}
}
