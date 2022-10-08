#ifndef QOI_FORMAT_CODEC_CONVERTOR_H_
#define QOI_FORMAT_CODEC_CONVERTOR_H_

#include <cstdint>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>

void RgbToPpm(std::istream &is, std::ostream &os, uint32_t width, uint32_t height) {
    if (width == 0 || height == 0 || 1ll * width * height > 1e9) {
        throw "illegal image size";
    }

    os << "P3" << std::endl;
    os << width << " " << height << std::endl;
    os << 255 << std::endl;

    uint8_t rgb[3];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (is.eof()) throw "imcomplete pixel data";
            is.read(reinterpret_cast<char *>(rgb), 3);
            os << std::setw(3) << std::setfill(' ') << static_cast<int>(rgb[0]) << ' ';
            os << std::setw(3) << std::setfill(' ') << static_cast<int>(rgb[1]) << ' ';
            os << std::setw(3) << std::setfill(' ') << static_cast<int>(rgb[2]) << ' ';
            os << '\t';
        }
        os << '\n';
    }
}

void PpmToRgb(std::istream &is, std::ostream &os, uint32_t &width, uint32_t &height) {

    std::string magic;
    if (is.eof()) throw "empty input";
    is >> magic;
    if (magic != "P3") {
        throw "expect plain .ppm image but got something else";
    }

    if (is.eof()) throw "missing image width info";
    is >> width;
    if (is.eof()) throw "missing image height info";
    is >> height;
    if (width == 0 || height == 0 || 1ll * width * height > 1e9) {
        throw "illegal image size";
    }

    int maxval;
    if (is.eof()) throw "missing maxval info";
    is >> maxval;
    if (maxval != 255) {
        throw "expect 255 as maxval but got something else";
    }

    uint8_t rgb[3];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int temp;
            if (is.eof()) throw "incomplete pixel data";
            is >> temp;
            rgb[0] = static_cast<uint8_t>(temp);
            if (is.eof()) throw "incomplete pixel data";
            is >> temp;
            rgb[1] = static_cast<uint8_t>(temp);
            if (is.eof()) throw "incomplete pixel data";
            is >> temp;
            rgb[2] = static_cast<uint8_t>(temp);
            os.write(reinterpret_cast<const char *>(rgb), 3);
        }
    }
}

void RgbaToPam(std::istream &is, std::ostream &os, uint32_t width, uint32_t height) {
    if (width == 0 || height == 0 || 1ll * width * height > 1e9) {
        throw "illegal image size";
    }

    os << "P7" << std::endl;
    os << "WIDTH " << width << std::endl;
    os << "HEIGHT " << height << std::endl;
    os << "DEPTH 4" << std::endl;
    os << "MAXVAL 255" << std::endl;
    os << "TUPLTYPE RGB_ALPHA" << std::endl;
    os << "ENDHDR" << std::endl;

    uint8_t rgba[4];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (is.eof()) throw "incomplete pixel data";
            is.read(reinterpret_cast<char *>(rgba), 4);
            os << std::setw(3) << std::setfill(' ') << static_cast<int>(rgba[3]) << ' ';
            os << std::setw(3) << std::setfill(' ') << static_cast<int>(rgba[0]) << ' ';
            os << std::setw(3) << std::setfill(' ') << static_cast<int>(rgba[1]) << ' ';
            os << std::setw(3) << std::setfill(' ') << static_cast<int>(rgba[2]) << ' ';
            os << '\t';
        }
        os << '\n';
    }
}

void PamToRgba(std::istream &is, std::ostream &os, uint32_t &width, uint32_t &height) {

    std::string magic;
    if (is.eof()) throw "empty input";
    is >> magic;
    if (magic != "P7") {
        throw "expect .pam image but got something else";
    }

    std::map<std::string, bool> info;

    std::string id;
    if (is.eof()) throw "missing header info";
    do {
        if (is.eof()) throw "unclosed header";
        is >> id;
        if (id == "WIDTH") {
            if (is.eof()) throw "missing image width info";
            is >> width;
            info["wd"] = true;
        }
        if (id == "HEIGHT") {
            if (is.eof()) throw "missing image height info";
            is >> height;
            info["ht"] = true;
        }
        if (id == "DEPTH") {
            if (is.eof()) throw "missing pixel depth info";
            int temp;
            is >> temp;
            info["dp"] = true;
            if (temp != 4) {
                throw "exepct 4 as depth but got something else";
            }
        }
        if (id == "MAXVAL") {
            if (is.eof()) throw "missing maxval info";
            int temp;
            is >> temp;
            info["mv"] = true;
            if (temp != 255) {
                throw "expect 255 as maxval but got something else";
            }
        }
        if (id == "TUPLTYPE") {
            if (is.eof()) throw "missing tuple type info";
            std::string tupltype;
            is >> tupltype;
            info["tu"] = true;
            if (tupltype != "RGB_ALPHA") {
                throw "expect RGB_ALPHA as tupltype but got something else";
            }
        }
    } while (id != "ENDHDR");

    if (!info["wd"] || !info["ht"] || !info["dp"] || !info["mv"] || !info["tu"]) {
        throw "imcomplete header info";
    }

    if (width == 0 || height == 0 || 1ll * width * height > 1e9) {
        throw "illegal image size";
    }

    uint8_t rgba[4];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int temp;
            if (is.eof()) throw "incomplete pixel data";
            is >> temp;
            rgba[3] = static_cast<uint8_t>(temp);
            if (is.eof()) throw "incomplete pixel data";
            is >> temp;
            rgba[0] = static_cast<uint8_t>(temp);
            if (is.eof()) throw "incomplete pixel data";
            is >> temp;
            rgba[1] = static_cast<uint8_t>(temp);
            if (is.eof()) throw "incomplete pixel data";
            is >> temp; rgba[2] = static_cast<uint8_t>(temp);
            os.write(reinterpret_cast<const char *>(rgba), 4);
        }
    }
}

#endif // QOI_FORMAT_CODEC_CONVERTOR_H_
