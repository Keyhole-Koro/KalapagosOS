#pragma once

#include "cstdint"

#include "frame_buffer_config.hpp"

struct PixelColor {
    uint8_t r, g, b;
};

int WritePixel(const struct FrameBufferConfig &config,
                int x, int y, const PixelColor &c) {
    const int pixel_position = config.pixels_per_scan_line * y + x;
    if (config.pixel_format == kPixelRGBResv8BitPerColor) {
        uint8_t *p = &config.frame_buffer[4 * pixel_position];
        p[0] = c.r;
        p[1] = c.g;
        p[2] = c.b;
    } else if (config.pixel_format == kPixelBGRResv8BitPerColor) {
        uint8_t *p = &config.frame_buffer[4 * pixel_position]; // 4 is the byte size of a pixel
        p[0] = c.b;
        p[1] = c.g;
        p[2] = c.r;
    } else {
        return -1; // failed
    }
    return 0; // success
}