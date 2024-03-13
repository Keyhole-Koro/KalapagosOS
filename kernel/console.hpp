#pragma once

#include <cstdint>
#include <cstring>

#include "font.hpp"

class Console {
    public:
        static const int kRows = 25, kColumns = 80;
        Console(PixelWriter &writer,
            const PixelColor &fg_color, const PixelColor &bg_color);
        void PutString(const char *s);
    private:
        void Newline();
        PixelWriter &writer_;
        const PixelColor fg_color_, bg_color_;
        char buffer_[kRows][kColumns + 1];
        int cursor_row_, cursor_column_;
};

Console::Console(PixelWriter &writer,
                 const PixelColor &fg_color, const PixelColor &bg_color)
    : writer_(writer), fg_color_(fg_color), bg_color_(bg_color),
      cursor_row_(0), cursor_column_(0) {}

void Console::PutString(const char *s) {}