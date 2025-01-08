

#include <fstream>
#include <arm7tdmi/decoder.h>
#include <arm7tdmi/cpu.h>

#include <fmt/format.h>

#include "arm7tdmi/memory.h"

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

    auto memory = arm7tdmi::basic_memory(256);
    auto cpu = arm7tdmi::cpu(&memory);

    cpu.registers.cpsr(32u);
    fmt::println("{:#034b}", cpu.registers.cpsr());

    cpu.registers.cpsr_set_c(true);
    bool c = cpu.registers.cpsr_get_c();
    cpu.registers.pc(cpu.registers.pc() + 1);

    return 0;
}
