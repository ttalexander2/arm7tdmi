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

        [[nodiscard]] virtual u32 read_arm(u64 address) const = 0;
        virtual bool write_arm(u64 address, u32 value) = 0;

        [[nodiscard]] virtual u16 read_thumb(u64 address) const = 0;
        virtual bool write_thumb(u64 address, u16 value) = 0;

        [[nodiscard]] virtual u64 get_size(cpu_mode mode) const = 0;
    };

	class basic_memory final : public memory_interface {
    public:
		explicit basic_memory(u64 size);

        [[nodiscard]] u32 read_arm(u64 address) const override;

        bool write_arm(u64 address, u32 value) override;

        [[nodiscard]] u16 read_thumb(u64 address) const override;

        bool write_thumb(u64 address, u16 value) override;

        [[nodiscard]] u64 get_size(cpu_mode mode) const override;
	private:
		u32* _memory = nullptr;
	    u64 _size = 0;
    };

}
