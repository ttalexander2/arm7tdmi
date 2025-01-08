//
// Created by talexander on 9/23/2024.
//

#pragma once
#include <limits>
#include <type_traits>

#include <arm7tdmi/common.h>

namespace arm7tdmi {

	enum class AlignmentType : u8 {
		Force,
		Rotate,
		None
	};

    class memory_interface {
    public:
        virtual ~memory_interface() = default;

        /**
         * 
         * @tparam T Type to read. Must be u8/byte, u16/halfword, or u32/word.
         * @param address 32-bit memory address.
         * @return Value stored the address.
         */
        template <typename T, AlignmentType Alignment = AlignmentType::Force>
    	bool read(u32 address, T* out) const;

        /**
         * 
         * @tparam T Type to write. Must be u8/byte, u16/halfword, or u32/word.
         * @param address 32-bit memory address.
         * @param value Value to write to memory at the address.
         */
        template <typename T, AlignmentType Alignment = AlignmentType::Force>
    	bool write(u32 address, T value);

        /**
         * 
         * @return Returns total memory block size in bytes
         */
        [[nodiscard]] virtual u64 size() const = 0;

    protected:
    	[[nodiscard]] virtual bool read_byte(u32 address, u8* out) const = 0;
    	virtual bool write_byte(size_t address, u8 value) = 0;
    };

	class basic_memory final : public memory_interface {
    public:
		explicit basic_memory(u64 size);
		~basic_memory() override;

		[[nodiscard]] u32 size() const override;

	protected:
		[[nodiscard]] bool read_byte(u32 address, u8* out) const override;
		bool write_byte(size_t address, u8 value) override;

	private:
		u8* _memory = nullptr;
	    u64 _size = 0;
    };

	template <typename T, AlignmentType Alignment>
	bool memory_interface::read(const u32 address, T* out) const {
		static_assert(std::is_same_v<T, u8> || std::is_same_v<T, u16> || std::is_same_v<T, u32>, "memory value must be u8/byte, u16/halfword, or u32/word");

		if (out == nullptr) {
			return false;
		}

		u32 aligned_address = address;
		u32 rotation = 0;
		T value = 0;

		if constexpr (Alignment == AlignmentType::Force) {
			// Force alignment by rounding down the address
			aligned_address = address & ~3;  // Mask lower 2 bits to align to 4-byte boundary
		}
		else if constexpr (Alignment == AlignmentType::Rotate) {
			// Calculate rotation based on misalignment
			rotation = (address & 3) * 8;  // Rotation in bits based on misalignment
			aligned_address = address & ~3;  // Mask lower 2 bits to align to 4-byte boundary
		}

		bool success = true;
		for (size_t i = 0; i < sizeof(T); ++i) {
			u8 byte_read = 0;
			success &= read_byte(aligned_address + i, &byte_read);  // Read the byte from memory

			// If rotating, apply the rotation on the first byte
			if constexpr (Alignment == AlignmentType::Rotate && i == 0 && rotation != 0) {
				byte_read = (byte_read << rotation) | (byte_read >> (8 - rotation));  // Rotate the byte
			}

			// Combine the byte into the value
			value |= static_cast<T>(byte_read) << (i * 8);
		}

		*out = value;

		return success;
	}

	template <typename T, AlignmentType Alignment>
	bool memory_interface::write(const u32 address, T value) {
		static_assert(std::is_same_v<T, u8> || std::is_same_v<T, u16> || std::is_same_v<T, u32>, "memory value must be u8/byte, u16/halfword, or u32/word");

		u32 aligned_address = address;
		u32 rotation = 0;

		if constexpr (Alignment == AlignmentType::Force) {
			// Force alignment by rounding down the address
			aligned_address = address & ~3;  // Mask lower 2 bits to align to 4-byte boundary
		}
		else if constexpr (Alignment == AlignmentType::Rotate) {
			// Calculate rotation based on misalignment
			rotation = (address & 3) * 8;  // Rotation in bits based on misalignment
			aligned_address = address & ~3;  // Mask lower 2 bits to align to 4-byte boundary
		}

		bool success = true;
		for (size_t i = 0; i < sizeof(T); ++i) {
			u8 byte_to_write = static_cast<u8>((value >> (i * 8)) & 0xFF);

			// If rotating, apply the rotation on the first byte
			if constexpr (Alignment == AlignmentType::Rotate && i == 0 && rotation != 0) {
				byte_to_write = (byte_to_write >> rotation) | (byte_to_write << (8 - rotation));
			}

			// Write the byte to memory at the aligned address
			success &= write_byte(aligned_address + i, byte_to_write);
		}

		return success;
	}
}
