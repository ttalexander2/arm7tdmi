//
// Created by talexander on 9/4/2024.
//
#include <catch2/catch_test_macros.hpp>

#include <arm7tdmi/decoder.h>

TEST_CASE("branch_and_exchange") {

    constexpr u32 branch_and_exchange = 0x112fff14;

    const auto instr = arm7tdmi::arm::decode(branch_and_exchange);
    REQUIRE(instr == arm7tdmi::arm::instruction::branch_and_exchange);

}