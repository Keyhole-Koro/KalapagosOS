#include "main.hpp"

char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter *pixel_writer;

char console_buf[sizeof(Console)];
Console *console;

void set_xmm_register(float value) {
    // XMM00
    asm volatile (
        "movss %[value], %%xmm0"
        :
        : [value] "m" (value)
        : "%xmm0"
    );
}

extern "C" void KernelMain(const FrameBufferConfig &frame_buffer_config) {
    switch (frame_buffer_config.pixel_format) {
        case kPixelRGBResv8BitPerColor:
            pixel_writer = new(pixel_writer_buf)
                RGBResv8BitPerColorPixelWriter(frame_buffer_config);
            break;
        case kPixelBGRResv8BitPerColor:
            pixel_writer = new(pixel_writer_buf)
                BGRResv8BitPerColorPixelWriter(frame_buffer_config);
            break;
    }
    
    for (int x = 0; x < frame_buffer_config.horizontal_resolution; ++x) {
        for (int y = 0; y < frame_buffer_config.vertical_resolution; ++y) {
            pixel_writer->Write(x, y, {255, 255, 255});
        }
    }

    console = new(console_buf) Console{*pixel_writer, {0, 0, 0}, {255, 255, 255}};

    console->PutString("welcome\n");
    
    while (1) __asm__("hlt");
}
