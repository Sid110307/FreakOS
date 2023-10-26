#pragma once

#include "./types.h"

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

static inline const char *strstr(const char *str, const char *substr)
{
    while (*str)
    {
        const char *str1 = str;
        const char *str2 = substr;
        size_t n = strlen(substr);

        while (n && *str1 && *str1 == *str2)
        {
            ++str1;
            ++str2;

            n--;
        }

        if (n == 0) return str;
        ++str;
    }

    return 0;
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
