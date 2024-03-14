#include "main.hpp"

char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter *pixel_writer;

char console_buf[sizeof(Console)];
Console *console;

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
    
    int kFrameWidth = frame_buffer_config.horizontal_resolution;
    int kFrameHeight = frame_buffer_config.vertical_resolution;
    for (int x = 0; x < frame_buffer_config.horizontal_resolution; ++x) {
        for (int y = 0; y < frame_buffer_config.vertical_resolution; ++y) {
            pixel_writer->Write(x, y, {255, 255, 255});
        }
    }

    console = new(console_buf) Console{*pixel_writer, {0, 0, 0}, {255, 255, 255}};

    console->PutString("Welcome to console\n");

    drawCursor(pixel_writer);

    FillRectangle(*pixel_writer, {0,0}, {kFrameWidth, kFrameHeight - 50}, {140, 140, 140});
    FillRectangle(*pixel_writer, {0,kFrameHeight - 50}, {kFrameWidth, 50}, {1, 8, 17});
    FillRectangle(*pixel_writer, {0,kFrameHeight - 50}, {kFrameWidth/5, 50}, {80, 80, 80});
    DrawRectangle(*pixel_writer, {0,kFrameHeight - 40}, {30, 30}, {160, 160, 160});
    
    auto err = pci::ScanAllBus();

    for (int i = 0; i < pci::num_device; ++i) {
        const auto &dev = pci::devices[i];
        auto vendor_id = pci::ReadVendorId(dev.bus, dev.device, dev.function);
        auto class_code = pci::ReadClassCode(dev.bus, dev.device, dev.function);
    }
    while (1) __asm__("hlt");
}
