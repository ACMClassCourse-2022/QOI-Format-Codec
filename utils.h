#ifndef QOI_FORMAT_CODEC_UTILS_H_
#define QOI_FORMAT_CODEC_UTILS_H_

#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

/// calculate the index of pixel (r,g,b,a) in the history table
inline int QoiColorHash(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255u) {
    return (r * 3u + g * 5u + b * 7u + a * 11u) % 64;
}

/// read a character from the input stream
inline char QoiReadChar() {
    char ch;
    std::cin >> ch;
    return ch;
}

/// read an 8-bit unsigned integer from the input stream 
inline uint8_t QoiReadU8() {
    uint8_t buf;
    std::cin.read(reinterpret_cast<char *>(&buf), sizeof(buf));
    return buf;
}

/// read a 32-bit unsigned integer from the input stream
inline uint32_t QoiReadU32() {
    uint8_t buf[4];
    std::cin.read(reinterpret_cast<char *>(buf), sizeof(buf));
    return buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3];
}

/// write a character to the output stream
inline void QoiWriteChar(char ch) {
    std::cout << ch;
}

/// write an 8-bit unsigned integer to the output stream
inline void QoiWriteU8(uint8_t buf) {
    std::cout.write(reinterpret_cast<const char *>(&buf), sizeof(buf));
}

/// write an 32-bit unsigned integer to the output stream
inline void QoiWriteU32(uint32_t buf) {
    uint8_t buz[4];
    buz[0] = (buf >> 24) & 0xff;
    buz[1] = (buf >> 16) & 0xff;
    buz[2] = (buf >>  8) & 0xff;
    buz[3] = (buf >>  0) & 0xff;
    std::cout.write(reinterpret_cast<const char *>(buz), sizeof(buz));
}

#endif // QOI_FORMAT_CODEC_UTILS_H_
