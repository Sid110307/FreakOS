#pragma once

#include "../lib/utils.h"

#define INDENTATION 4

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

#define VGA_CTRL_PORT 0x3D4
#define VGA_DATA_PORT 0x3D5
#define VGA_CARET_HIGH 0x0E
#define VGA_CARET_LOW 0x0F

void rendererInit(void);
void rendererSetColor(enum Colors fg, enum Colors bg);
void rendererSetPosColor(enum Colors fg, enum Colors bg, size_t x1, size_t y1, size_t x2, size_t y2);
void rendererPutCharAt(char c, enum Colors color, size_t x, size_t y);
void rendererPutChar(char c);
void rendererScroll(void);
void rendererWrite(const char *data, size_t size);
void rendererWriteString(const char *data);
void rendererClearScreen(void);
const char *rendererGetLine(size_t line);

void rendererSetCaretPos(size_t x, size_t y);
uint16_t rendererGetCaretPos(void);
void rendererMoveCaret(int x, int y);
size_t rendererGetCaretPosX(void);
size_t rendererGetCaretPosY(void);
