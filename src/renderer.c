#include "include/renderer.h"

Framebuffer framebuffer;
size_t rendererRow, rendererColumn;
enum Colors rendererColor;

void rendererInit(Framebuffer fb)
{
    framebuffer = fb;

    rendererRow = 0;
    rendererColumn = 0;
    rendererColor = COLOR_WHITE;

    outPort(CONTROL_PORT, CARET_HIGH);
    outPort(DATA_PORT, (inPort(DATA_PORT) & 0xC0) | 14);
    outPort(CONTROL_PORT, CARET_LOW);
    outPort(DATA_PORT, (inPort(DATA_PORT) & 0xE0) | 15);
}

void rendererSetColor(enum Colors fg, enum Colors bg) { rendererColor = fg | bg << 4; }

void rendererSetPosColor(enum Colors fg, enum Colors bg, size_t x1, size_t y1, size_t x2, size_t y2)
{
    for (size_t y = y1; y < y2; ++y)
        for (size_t x = x1; x < x2; ++x)
        {
            size_t pixelOffset = (y * framebuffer.width + x) * framebuffer.bytesPerPixel;
            framebuffer.address[pixelOffset] = fg;
            framebuffer.address[pixelOffset + 1] = bg;
        }
}

void rendererScroll()
{
    for (size_t y = 0; y < framebuffer.height - 1; ++y)
        for (size_t x = 0; x < framebuffer.width; ++x)
        {
            size_t pixelOffset = (y * framebuffer.width + x) * framebuffer.bytesPerPixel,
                    pixelOffsetBelow = ((y + 1) * framebuffer.width + x) * framebuffer.bytesPerPixel;

            framebuffer.address[pixelOffset] = framebuffer.address[pixelOffsetBelow];
            framebuffer.address[pixelOffset + 1] = framebuffer.address[pixelOffsetBelow + 1];
            framebuffer.address[pixelOffset + 2] = framebuffer.address[pixelOffsetBelow + 2];
            framebuffer.address[pixelOffset + 3] = framebuffer.address[pixelOffsetBelow + 3];
        }

    for (size_t x = 0; x < framebuffer.width; ++x)
    {
        size_t pixelOffset = ((framebuffer.height - 1) * framebuffer.width + x) * framebuffer.bytesPerPixel;

        framebuffer.address[pixelOffset] = 0;
        framebuffer.address[pixelOffset + 1] = 0;
        framebuffer.address[pixelOffset + 2] = 0;
        framebuffer.address[pixelOffset + 3] = 255;
    }
}

void rendererPutCharAt(uint8_t c, enum Colors color, size_t x, size_t y)
{
    size_t pixelOffset = (y * framebuffer.width + x) * framebuffer.bytesPerPixel;

    framebuffer.address[pixelOffset] = c;
    framebuffer.address[pixelOffset + 1] = color;
}

void rendererPutChar(uint8_t c)
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
            if (rendererColumn > 0) rendererColumn--;
            break;
        case '\r':
            rendererColumn = 0;
            break;
        case '\f':
            rendererClearScreen();
            break;
        case '\v':
            rendererScroll();
            break;
        case '\a':
            playSound(440, 100);
            break;
        default:
            rendererPutCharAt(c, rendererColor, rendererColumn, rendererRow);
            rendererColumn++;
            break;
    }

    if (rendererColumn >= framebuffer.width)
    {
        rendererColumn = 0;
        rendererRow++;
    }

    if (rendererRow >= framebuffer.height)
    {
        rendererScroll();
        rendererRow--;
    }
}

void rendererWriteString(const char *data, size_t size) { for (size_t i = 0; i < size; ++i) rendererPutChar(data[i]); }
void rendererWrite(const char *data)
{
    rendererWriteString(data, strlen(data));

    char test[256];
    for (size_t i = 0; i < strlen(data); ++i)
    {
        if (data[i] == '\n')test[i] = '\\', test[i + 1] = 'n';
        else if (data[i] == '\t')test[i] = '\\', test[i + 1] = 't';
        else if (data[i] == '\b')test[i] = '\\', test[i + 1] = 'b';
        else if (data[i] == '\r')test[i] = '\\', test[i + 1] = 'r';
        else if (data[i] == '\f')test[i] = '\\', test[i + 1] = 'f';
        else if (data[i] == '\v')test[i] = '\\', test[i + 1] = 'v';
        else if (data[i] == '\a')test[i] = '\\', test[i + 1] = 'a';
        else test[i] = data[i];
    }

    log("%s: %dx%d\n", test, rendererColumn, rendererRow);
}

void rendererClearScreen()
{
    for (size_t y = 0; y < framebuffer.height; ++y)
        for (size_t x = 0; x < framebuffer.width; ++x)
        {
            size_t pixelOffset = (y * framebuffer.width + x) * framebuffer.bytesPerPixel;

            framebuffer.address[pixelOffset] = 0;
            framebuffer.address[pixelOffset + 1] = 0;
            framebuffer.address[pixelOffset + 2] = 0;
            framebuffer.address[pixelOffset + 3] = 255;
        }

}

const char *rendererGetLine(size_t line)
{
    return (const char *) framebuffer.address + (line * framebuffer.width * framebuffer.bytesPerPixel);
}

void rendererSetCaretPos(size_t x, size_t y)
{
    rendererColumn = x;
    rendererRow = y;
}

uint16_t rendererGetCaretPos() { return (uint16_t) (rendererRow * framebuffer.width + rendererColumn); }

void rendererMoveCaret(size_t x, size_t y)
{
    rendererColumn += x;
    rendererRow += y;

    if (rendererColumn >= framebuffer.width)
    {
        rendererColumn = 0;
        ++rendererRow;
    }

    if (rendererRow >= framebuffer.height)
    {
        rendererScroll();
        rendererRow--;
    }
}

size_t rendererGetCaretPosX() { return rendererColumn; }
size_t rendererGetCaretPosY() { return rendererRow; }
