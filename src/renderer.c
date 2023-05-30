#include "./include/renderer.h"

size_t rendererRow, rendererColumn;
enum Colors rendererColor;
__attribute__((unused)) uint16_t *videoMemory;

static inline enum Colors vgaEntryColor(enum Colors fg, enum Colors bg)
{
    return fg | (bg << 4);
}

static inline uint16_t vgaEntry(char displayChar, enum Colors color)
{
    return (uint16_t) displayChar | ((uint16_t) color << 8);
}

void rendererInit(void)
{
    rendererRow = 0;
    rendererColumn = 0;
    rendererColor = vgaEntryColor(COLOR_WHITE, COLOR_BLACK);
    videoMemory = (uint16_t *) 0xB8000;

    for (size_t y = 0; y < SCREEN_HEIGHT; ++y)
        for (size_t x = 0; x < SCREEN_WIDTH; ++x)
            videoMemory[y * SCREEN_WIDTH + x] = vgaEntry('\0', rendererColor);
}

void rendererSetColor(enum Colors fg, enum Colors bg)
{
    rendererColor = vgaEntryColor(fg, bg);
}

void rendererSetPosColor(enum Colors fg, enum Colors bg, size_t x1, size_t y1, size_t x2, size_t y2)
{
    for (size_t y = y1; y < y2; ++y)
        for (size_t x = x1; x < x2; ++x)
            videoMemory[y * SCREEN_WIDTH + x] = vgaEntry('\0', vgaEntryColor(fg, bg));
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
            rendererColumn += INDENTATION;
            break;
        case '\b':
            if (rendererColumn > 0)
            {
                rendererColumn--;
                rendererPutCharAt('\0', rendererColor, rendererColumn, rendererRow);
            }

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
        case '\e':
            rendererClearScreen();
            break;
        case '\a':
            outPort(0x61, inPort(0x61) | 3);
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
        videoMemory[(SCREEN_HEIGHT - 1) * SCREEN_WIDTH + x] = vgaEntry('\0', rendererColor);
}

void rendererWrite(const char *data, size_t size)
{
    for (size_t i = 0; i < size; ++i) rendererPutChar(data[i]);
}

void rendererWriteString(const char *data)
{
    rendererWrite(data, strlen(data));
}

void rendererClearScreen(void)
{
    for (size_t y = 0; y < SCREEN_HEIGHT; ++y)
        for (size_t x = 0; x < SCREEN_WIDTH; ++x)
            videoMemory[y * SCREEN_WIDTH + x] = vgaEntry('\0', rendererColor);
}

const char *rendererGetLine(size_t line)
{
    return (const char *) &videoMemory[line * SCREEN_WIDTH];
}

void rendererSetCaretPos(size_t x, size_t y)
{
    const size_t index = y * SCREEN_WIDTH + x;

    outPort(VGA_CTRL_PORT, VGA_CARET_LOW);
    outPort(VGA_DATA_PORT, (uint8_t) (index & 0xFF));
    outPort(VGA_CTRL_PORT, VGA_CARET_HIGH);
    outPort(VGA_DATA_PORT, (uint8_t) ((index >> 8) & 0xFF));
}

uint16_t rendererGetCaretPos(void)
{
    uint16_t pos = 0;

    outPort(VGA_CTRL_PORT, VGA_CARET_LOW);
    pos |= inPort(VGA_DATA_PORT);
    outPort(VGA_CTRL_PORT, VGA_CARET_HIGH);
    pos |= ((uint16_t) inPort(VGA_DATA_PORT)) << 8;

    return pos;
}

void rendererMoveCaret(int x, int y)
{
    const size_t index = rendererGetCaretPos();
    rendererSetCaretPos(mod(mod(index, SCREEN_WIDTH) + x, SCREEN_WIDTH),
                        mod((int) index / SCREEN_WIDTH + y, SCREEN_HEIGHT));
}

size_t rendererGetCaretPosX(void)
{
    return mod(rendererGetCaretPos(), SCREEN_WIDTH);
}

size_t rendererGetCaretPosY(void)
{
    return rendererGetCaretPos() / SCREEN_WIDTH;
}
