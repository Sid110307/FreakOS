#include "include/string.h"

int strcmp(const char *str1, const char *str2)
{
    while (*str1 && *str1 == *str2)
    {
        ++str1;
        ++str2;
    }

    return *(const unsigned char *) str1 - *(const unsigned char *) str2;
}

size_t strlen(const char *str)
{
    size_t len = 0;
    while (str[len]) ++len;

    return len;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
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
