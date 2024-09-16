//
// Created by talexander on 9/16/2024.
//

#pragma once

#include <fstream>
#include <iterator>

#include "arm7tdmi/types.h"

template <typename T = u8>
inline std::vector<T> read_binary_from_file(const std::string& filename) {
    std::ifstream inputFile(filename, std::ios_base::binary);

    // Determine the length of the file by seeking
    // to the end of the file, reading the value of the
    // position indicator, and then seeking back to the beginning.
    inputFile.seekg(0, std::ios_base::end);
    auto length = inputFile.tellg();
    inputFile.seekg(0, std::ios_base::beg);

    // Make a buffer of the exact size of the file and read the data into it.
    std::vector<T> buffer(length);
    inputFile.read(reinterpret_cast<char*>(buffer.data()), length);

    inputFile.close();
    return buffer;
}

bool is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1;
}
