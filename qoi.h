#ifndef QOI_QOI_H_
#define QOI_QOI_H_

#include "utils.h"

constexpr uint8_t QOI_OP_INDEX_TAG = 0x00;
constexpr uint8_t QOI_OP_DIFF_TAG  = 0x40;
constexpr uint8_t QOI_OP_LUMA_TAG  = 0x80;
constexpr uint8_t QOI_OP_RUN_TAG   = 0xc0; 
constexpr uint8_t QOI_OP_RGB_TAG   = 0xfe;
constexpr uint8_t QOI_OP_RGBA_TAG  = 0xff;
constexpr uint8_t QOI_PADDING[8] = {0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u};
constexpr uint8_t QOI_MASK_2 = 0xc0;

/**
 * @brief encode the raw pixel data of an image to qoi format.
 * 
 * @param[in] width image width in pixels
 * @param[in] height image height in pixels
 * @param[in] channels number of color channels, 3 = RGB, 4 = RGBA 
 * @param[in] colorspace image color space, 0 = sRGB with linear alpha, 1 = all channels linear
 * 
 * @return bool true if it is a valid qoi format image, false ohterwise
 */
bool qoi_encode(uint32_t width, uint32_t height, uint8_t channels, uint8_t colorspace = 0);

/**
 * @brief decode the qoi format of an image to raw pixel data
 * 
 * @param[out] width image width in pixels
 * @param[out] height image height in pixels
 * @param[out] channels number of color channels, 3 = RGB, 4 = RGBA 
 * @param[out] colorspace image color space, 0 = sRGB with linear alpha, 1 = all channels linear
 * 
 * @return bool true if it is a valid qoi format image, false ohterwise
 */
bool qoi_decode(uint32_t &width, uint32_t &height, uint8_t &channels, uint8_t &colorspace);


bool qoi_encode(uint32_t width, uint32_t height, uint8_t channels, uint8_t colorspace) {

    /* qoi-header part */

    // write magic bytes "qoif"
    qoi_write_char('q');
    qoi_write_char('o');
    qoi_write_char('i');
    qoi_write_char('f');
    // write image width
    qoi_write_u32(width);
    // write image height
    qoi_write_u32(height);
    // write channel number
    qoi_write_u8(channels);
    // write color space identifer
    qoi_write_u8(colorspace);

    /* qoi-data part */
    int run = 0;
    int px_num = width * height;

    uint8_t history[64][4];
    memset(history, 0, sizeof(history));

    uint8_t r, g, b, a;
    a = 255u;
    uint8_t pre_r, pre_g, pre_b, pre_a;
    pre_r = 0u;
    pre_g = 0u;
    pre_b = 0u;
    pre_a = 255u;

    for (int i = 0; i < px_num; ++i) {
        r = qoi_read_u8();
        g = qoi_read_u8();
        b = qoi_read_u8();
        if (channels == 4) a = qoi_read_u8();

        // TODO

        pre_r = r;
        pre_g = g;
        pre_b = b;
        pre_a = a;
    }

    /* qoi-padding part */
    for (int i = 0; i < sizeof(QOI_PADDING) / sizeof(QOI_PADDING[0]); ++i) {
        qoi_write_u8(QOI_PADDING[i]);
    }

    return true;
}

bool qoi_decode(uint32_t &width, uint32_t &height, uint8_t &channels, uint8_t &colorspace) {

    char c1 = qoi_read_char();
    char c2 = qoi_read_char();
    char c3 = qoi_read_char();
    char c4 = qoi_read_char();
    if (c1 != 'q' || c2 != 'o' || c3 != 'i' || c4 != 'f') {
        return false;
    }

    // read image width
    width = qoi_read_u32();
    // read image height
    height = qoi_read_u32();
    // read channel number
    channels = qoi_read_u8();
    // read color space identifer
    colorspace = qoi_read_u8();

    int run = 0;    
    int px_num = width * height;

    uint8_t history[64][4];
    memset(history, 0, sizeof(history));

    uint8_t r, g, b, a;
    a = 255u;

    for (int i = 0; i < px_num; ++i) {

        // TODO

        qoi_write_u8(r);
        qoi_write_u8(g);
        qoi_write_u8(b);
        if (channels == 4) qoi_write_u8(a);
    }

    bool valid = true;
    for (int i = 0; i < sizeof(QOI_PADDING) / sizeof(QOI_PADDING[0]); ++i) {
        if (qoi_read_u8() != QOI_PADDING[i]) valid = false;
    }

    return valid;
}

#endif // QOI_QOI_H_
