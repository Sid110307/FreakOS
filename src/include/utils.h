#pragma once

#include <stdarg.h>
#include "io.h"

enum Colors
{
    COLOR_BLACK = 0,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_CYAN,
    COLOR_RED,
    COLOR_MAGENTA,
    COLOR_BROWN,
    COLOR_LIGHT_GREY,
    COLOR_DARK_GREY,
    COLOR_LIGHT_BLUE,
    COLOR_LIGHT_GREEN,
    COLOR_LIGHT_CYAN,
    COLOR_LIGHT_RED,
    COLOR_LIGHT_MAGENTA,
    COLOR_LIGHT_BROWN,
    COLOR_WHITE,
};

static void delay(uint32_t ms) { for (uint32_t i = 0; i < ms; ++i) __asm__("hlt"); }
static void log(const char *str, ...)
{
    va_list args;
    va_start(args, str);

    while (*str)
    {
        if (*str == '%')
        {
            ++str;
            if (*str == 'd')
            {
                int num = va_arg(args, int);
                char numStr[32];
                int i = 0;
                while (num)
                {
                    numStr[i++] = (char) (num % 10 + '0');
                    num /= 10;
                }

                while (i--) outPort(0x3F8, numStr[i]);
            } else if (*str == 'c')
            {
                char c = va_arg(args, int);
                outPort(0x3F8, c);
            } else if (*str == 's')
            {
                char *s = va_arg(args, char *);
                while (*s) outPort(0x3F8, *s++);
            }
        } else outPort(0x3F8, *str);

        ++str;
    }

    va_end(args);
}
