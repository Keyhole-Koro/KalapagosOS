#pragma once

#include "cstdint"

#include "frame_buffer_config.hpp"

struct PixelColor {
    uint8_t r, g, b;
};

template <typename T>
struct Vector2D {
    T x, y;

    template <typename U>
    Vector2D<T> &operator += (const Vector2D<U> &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
};

class PixelWriter {
    public:
        PixelWriter(const FrameBufferConfig &config) : config_{config} {
        }
        virtual ~PixelWriter() = default;
        virtual void Write(int x, int y, const PixelColor &c) = 0;
    protected:
        uint8_t *PixelAt(int x, int y) {
            return config_.frame_buffer + 4 * (config_.pixels_per_scan_line * y + x);
        }
    
    private:
        const FrameBufferConfig &config_;
};

class RGBResv8BitPerColorPixelWriter : public PixelWriter {
    public:
        using PixelWriter::PixelWriter;

    virtual void Write(int x, int y, const PixelColor &c) override {
        auto p = PixelAt(x, y);
        p[0] = c.r;
        p[1] = c.g;
        p[2] = c.b;
    }
};

class BGRResv8BitPerColorPixelWriter : public PixelWriter {
    public:
        using PixelWriter::PixelWriter;

    virtual void Write(int x, int y, const PixelColor &c) override {
        auto p = PixelAt(x, y);
        p[0] = c.b;
        p[1] = c.g;
        p[2] = c.r;
    }
};

void FillRectangle(PixelWriter &writer, const Vector2D<int> &pos,
                    const Vector2D<int> &size, const PixelColor &c) {
                        for (int dy = 0; dy < size.y; ++dy) {
                            for (int dx = 0; dx < size.x; ++dx) {
                                writer.Write(pos.x + dx, pos.y + dy, c);
                            }
                        }
                    }