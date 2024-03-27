#pragma once

#include <cstdint>
#include <cstddef>
#include <cstdarg>

#include <stdio.h>
#include <stdarg.h>

#include "./utils/utils.hpp"
#include "./graphics/frame_buffer_config.hpp"
#include "./graphics/graphics.hpp"
#include "./graphics/font.hpp"
#include "./console/console.hpp"
#include "./graphics/cursor.hpp"
#include "./pci/pci.hpp"
#include "interrupt.hpp"

char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter *pixel_writer;

char console_buf[sizeof(Console)];
extern Console *console;