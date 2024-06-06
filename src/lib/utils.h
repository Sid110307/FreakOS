#pragma once

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long int uintptr_t;
typedef unsigned long long uint64_t;
typedef uint64_t size_t;

static inline int strcmp(const char *str1, const char *str2)
{
    while (*str1 && *str1 == *str2)
    {
        ++str1;
        ++str2;
    }

    return *(const unsigned char *) str1 - *(const unsigned char *) str2;
}

static inline size_t strlen(const char *str)
{
    size_t len = 0;
    while (str[len]) ++len;

    return len;
}

static inline int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
    const unsigned char *p1 = ptr1, *p2 = ptr2;
    while (num--)
    {
        if (*p1 != *p2) return *p1 - *p2;

        ++p1;
        ++p2;
    }

    return 0;
}

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

static inline void outPort(uint16_t port, uint8_t value) { __asm__ volatile("outb %0, %1" : : "a"(value), "Nd"(port)); }

static inline uint8_t inPort(uint16_t port)
{
    uint8_t value;
    __asm__ volatile("inb %1, %0" : "=a"(value) : "Nd"(port));

    return value;
}

static inline uint16_t mod(uint16_t dividend, uint16_t divisor)
{
    uint16_t remainder = dividend;
    while (remainder >= divisor) remainder -= divisor;

    return remainder;
}
