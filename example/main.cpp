#include <fmt/format.h>

#include <arm7tdmi/decoder.h>

#include "arm7tdmi/cpu.h"

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

    arm7tdmi::cpu cpu{};
    cpu.registers.cpsr = 32;
    bool c = cpu.registers.cpsr.set_c(false);
    cpu.registers.pc++;
    fmt::println("{}, {}", static_cast<u32>(cpu.registers.cpsr), c);

    fmt::println("cpu size: {}", sizeof(arm7tdmi::cpu) / sizeof(u32));


    return 0;
}
