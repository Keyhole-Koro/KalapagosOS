#pragma once

#include <cstdarg>
#include <cstring>

#include <stdio.h>
#include <stdarg.h>

void* memset(void* ptr, int value, size_t num) {
    unsigned char* p = (unsigned char*)ptr;
    for (size_t i = 0; i < num; ++i) {
        p[i] = (unsigned char)value;
    }
    return ptr;
}

void* memcpy(void* destination, const void* source, size_t num) {
    unsigned char* dst = (unsigned char*)destination;
    const unsigned char* src = (const unsigned char*)source;
    for (size_t i = 0; i < num; ++i) {
        dst[i] = src[i];
    }
    return destination;
}