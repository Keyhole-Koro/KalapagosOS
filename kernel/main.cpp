#include "main.hpp"

extern "C" void KernelMain(const FrameBufferConfig &frame_buffer_config) {
    for (int x = 0; x < frame_buffer_config.horizontal_resolution; ++x) {
        for (int y = 0; y < frame_buffer_config.vertical_resolution; ++y) {
            WritePixel(frame_buffer_config, x, y, {255, 255, 255});
        }
        for (int x = 0; x < 200; ++x) {
            for (int y = 0; y < 100; ++y) {
                WritePixel(frame_buffer_config, 100 + x, 100 + y, {0, 255, 0});
            }
        }
    }
    while (1) __asm__("hlt");
}