

#include <fstream>
#include <arm7tdmi/decoder.h>
#include <arm7tdmi/cpu.h>

#include <fmt/format.h>

bool is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1;
}

int main() {

    u32 branch_and_exchange = 0x112fff14;
    const auto instr = arm7tdmi::arm::decode(branch_and_exchange);
    fmt::println("{:#034b} - {}", branch_and_exchange, instruction_to_string(instr));

    u32 multiply = 0x000A5190;
    const auto multiply_instr = arm7tdmi::arm::decode(multiply);
    fmt::println("{:#034b} - {}", multiply, instruction_to_string(multiply_instr));

    u32 multiply_long = 0x00FA8191;
    const auto multiply_long_instr = arm7tdmi::arm::decode(multiply_long);
    fmt::println("{:#034b} - {}", multiply_long, instruction_to_string(multiply_long_instr));

    arm7tdmi::cpu cpu = {};
    cpu.registers.cpsr = 32u;
    fmt::println("{:#034b}", cpu.registers.cpsr);

    cpu.registers.cpsr.set_c(true);
    bool c = cpu.registers.cpsr.get_c();
    cpu.registers.pc++;

    fmt::println("{:#034b}", cpu.registers.cpsr);
    fmt::println("cpu size: {}, data size: {}, register size: {}", sizeof(arm7tdmi::cpu) / sizeof(u32), 19,  sizeof(arm7tdmi::cpu_register) / sizeof(u32));

    fmt::println("Endianness: {}", is_big_endian() ? "big" : "little");

    return 0;
}
