#pragma once

#include "../lib/utils.h"

#define INDENTATION 4

#define CONTROL_PORT 0x3D4
#define DATA_PORT 0x3D5
#define CARET_HIGH 0x0A
#define CARET_LOW 0x0B

#pragma once

#include "../lib/utils.h"

typedef struct
{
    uint32_t magic, version, headerSize, flags, numGlyphs, charSize, width, height;
} PSF1Header;

typedef struct
{
    uint8_t *address;
    size_t width, height, bytesPerPixel;
} Framebuffer;

void rendererInit(Framebuffer fb, const char *fontPath);
void rendererSetColor(enum Colors fg, enum Colors bg);
void rendererSetPosColor(enum Colors fg, enum Colors bg, size_t x1, size_t y1, size_t x2, size_t y2);
void rendererScroll(void);
void rendererPutCharAt(uint8_t c, enum Colors color, size_t x, size_t y);
void rendererPutChar(uint8_t c);
void rendererWrite(const char *data, size_t size);
void rendererWriteString(const char *data);
void rendererClearScreen(void);
const char *rendererGetLine(size_t line);
void rendererSetCaretPos(size_t x, size_t y);
uint16_t rendererGetCaretPos(void);
void rendererMoveCaret(size_t x, size_t y);
size_t rendererGetCaretPosX(void);
size_t rendererGetCaretPosY(void);
