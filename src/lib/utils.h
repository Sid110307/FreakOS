#pragma once

#include "./libc/string.h"

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

static inline void outPort(uint16_t port, uint8_t value)
{
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline uint8_t inPort(uint16_t port)
{
    uint8_t value;
    asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));

    return value;
}

static inline uint16_t mod(uint16_t dividend, uint16_t divisor)
{
    uint16_t remainder = dividend;
    while (remainder >= divisor) remainder -= divisor;

    return remainder;
}

static inline void *readFile(const char *path, const uint8_t *buffer)
{
    uint32_t size = 0;

    char *message = "Reading file \"";
    char *message2 = "\"...\n";

    for (int i = 0; message[i]; ++i) outPort(0x3F8, message[i]);
    for (int i = 0; path[i]; ++i) outPort(0x3F8, path[i]);
    for (int i = 0; message2[i]; ++i) outPort(0x3F8, message2[i]);

    // TODO: Fix this ASM code (it's not working)
    asm volatile (
            "movl $5, %%eax\n"
            "movl %0, %%ebx\n"
            "xorl %%ecx, %%ecx\n"
            "int $0x80\n"
            "movl %%eax, %1\n"
            :
            : "r" (path), "m" (size)
            : "eax", "ebx", "ecx"
            );

    asm volatile (
            "movl $3, %%eax\n"
            "movl %0, %%ebx\n"
            "movl %1, %%ecx\n"
            "int $0x80\n"
            :
            : "r" (path), "r" (buffer)
            : "eax", "ebx", "ecx"
            );

    return (void *) size;
}
