#include "./include/renderer.h"

size_t rendererRow, rendererColumn;
enum Colors rendererColor;
__attribute__((unused)) uint16_t *videoMemory;

static inline enum Colors vgaEntryColor(enum Colors fg, enum Colors bg)
{
    return fg | (bg << 4);
}

static inline uint16_t vgaEntry(unsigned char displayChar, enum Colors color)
{
    return (uint16_t) displayChar | ((uint16_t) color << 8);
}

static inline size_t strlen(const char *str)
{
    size_t len = 0;
    while (str[len]) len++;

    return len;
}

void rendererInit(void)
{
    rendererRow = 0;
    rendererColumn = 0;
    rendererColor = vgaEntryColor(COLOR_WHITE, COLOR_BLACK);
    videoMemory = (uint16_t *) 0xB8000;

    for (size_t y = 0; y < SCREEN_HEIGHT; ++y)
        for (size_t x = 0; x < SCREEN_WIDTH; ++x)
            videoMemory[y * SCREEN_WIDTH + x] = vgaEntry(' ', rendererColor);
}

void rendererSetColor(enum Colors fg, enum Colors bg)
{
    rendererColor = vgaEntryColor(fg, bg);
}

void rendererPutCharAt(char c, enum Colors color, size_t x, size_t y)
{
    const size_t index = y * SCREEN_WIDTH + x;
    videoMemory[index] = vgaEntry(c, color);
}

void rendererPutChar(char c)
{
    switch (c)
    {
        case '\n':
            rendererColumn = 0;
            rendererRow++;
            break;
        case '\t':
            rendererColumn += 4;
            break;
        case '\b':
            rendererColumn--;
            break;
        case '\r':
            rendererColumn = 0;
            break;
        case '\f':
            rendererRow = 0;
            break;
        case '\v':
            rendererRow++;
            break;
        default:
            rendererPutCharAt(c, rendererColor, rendererColumn, rendererRow);
            rendererColumn++;

            break;
    }

    if (rendererColumn >= SCREEN_WIDTH)
    {
        rendererColumn = 0;
        rendererRow++;
    }

    if (rendererRow >= SCREEN_HEIGHT)
    {
        rendererScroll();
        rendererRow--;
    }
}

void rendererScroll(void)
{
    for (size_t y = 0; y < SCREEN_HEIGHT - 1; ++y)
        for (size_t x = 0; x < SCREEN_WIDTH; ++x)
            videoMemory[y * SCREEN_WIDTH + x] = videoMemory[(y + 1) * SCREEN_WIDTH + x];

    for (size_t x = 0; x < SCREEN_WIDTH; ++x)
        videoMemory[(SCREEN_HEIGHT - 1) * SCREEN_WIDTH + x] = vgaEntry(' ', rendererColor);
}

void rendererWrite(const char *data, size_t size)
{
    for (size_t i = 0; i < size; ++i) rendererPutChar(data[i]);
}

void rendererWriteString(const char *data)
{
    rendererWrite(data, strlen(data));
}

void rendererWriteHex(uint32_t n)
{
    char *hex = "0123456789ABCDEF";
    char buffer[9] = {0};

    for (int i = 7; i >= 0; --i)
    {
        buffer[i] = hex[n & 0xF];
        n >>= 4;
    }

    rendererWriteString(buffer);
}
