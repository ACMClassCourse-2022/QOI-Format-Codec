#ifndef QOI_UTILS_H_
#define QOI_UTILS_H_

#include <iostream>
#include <cstdint>
#include <cstring>
#include <string>

/// calculate the index of pixel (r,g,b,a) in the history table
inline int qoi_color_hash(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255u) {
    return (r * 3u + g * 5u + b * 7u + a * 11u) % 64;
}

/// read a character from the input stream
inline char qoi_read_char() {
    char ch;
    std::cin >> ch;
    return ch;
}

/// read an 8-bit unsigned integer from the input stream 
inline uint8_t qoi_read_u8() {
    uint8_t buf;
    std::cin.read(reinterpret_cast<char *>(&buf), sizeof(buf));
    return buf;
}

/// read a 32-bit unsigned integer from the input stream
inline uint32_t qoi_read_u32() {
    uint8_t buf[4];
    std::cin.read(reinterpret_cast<char *>(buf), sizeof(buf));
    return buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3];
}

/// write a character to the output stream
inline void qoi_write_char(char ch) {
    std::cout << ch;
}

/// write an 8-bit unsigned integer to the output stream
inline void qoi_write_u8(uint8_t buf) {
    std::cout.write(reinterpret_cast<const char *>(&buf), sizeof(buf));
}

/// write an 32-bit unsigned integer to the output stream
inline void qoi_write_u32(uint32_t buf) {
    uint8_t buz[4];
    buz[0] = (buf >> 24) & 0xff;
    buz[1] = (buf >> 16) & 0xff;
    buz[2] = (buf >>  8) & 0xff;
    buz[3] = (buf >>  0) & 0xff;
    std::cout.write(reinterpret_cast<const char *>(buz), sizeof(buz));
}

#endif // QOI_UTILS_H_
