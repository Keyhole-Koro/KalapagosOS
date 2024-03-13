#pragma once

int snprintf(char *str, size_t size, const char *format, ...) {
    va_list args;
    va_start(args, format);

    int written = 0; // Total characters written so far

    // Iterate through the format string
    while (*format != '\0') {
        if (*format == '%') {
            // Handle format specifier
            // Use vsnprintf to format the argument into the buffer
            int ret = vsnprintf(str, size - written, format, args);
            if (ret < 0) {
                // Error handling
                va_end(args);
                return ret;
            }
            if (ret >= size - written) {
                // Buffer overflow detected
                va_end(args);
                return written + ret; // Return number of characters that would have been written
            }
            written += ret; // Update total characters written
            format += 2; // Skip format specifier and argument
        } else {
            // Copy regular characters to the buffer
            *str++ = *format++;
            written++;
            if (written >= size) {
                // Buffer full, null-terminate the output string
                *str = '\0';
                va_end(args);
                return written;
            }
        }
    }

    // Null-terminate the output string
    *str = '\0';

    va_end(args);

    // Return total characters written (excluding null terminator)
    return written;
}


int vsnprintf(char *str, size_t size, const char *format, va_list args) {
    int written = 0; // Total characters written so far
    int ret; // Return value of snprintf

    // Iterate through the format string
    while (*format != '\0') {
        if (*format == '%') {
            // Handle format specifier
            // Use snprintf to format the argument into the buffer
            ret = snprintf(str, size - written, format, args);
            if (ret < 0) {
                // Error handling
                return ret;
            }
            if (ret >= size - written) {
                // Buffer overflow detected
                return -1;
            }
            written += ret; // Update total characters written
            format += 2; // Skip format specifier and argument
        } else {
            // Copy regular characters to the buffer
            *str++ = *format++;
            written++;
        }
    }
    
    // Null-terminate the output string
    *str = '\0';

    // Return total characters written (excluding null terminator)
    return written;
}

int vsprintf(char *str, const char *format, va_list args) {
    int ret;
    ret = vsnprintf(str, SIZE_MAX, format, args); // Delegate to vsnprintf
    return ret;
}