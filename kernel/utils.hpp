#pragma once

#include "cstddef"

void *operator new(size_t size, void *buf) {
    return buf;
}

void operator delete(void *obj) noexcept {}
