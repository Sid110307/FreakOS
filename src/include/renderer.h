#pragma once

#include <stddef.h>
#include <stdint.h>

#include "../lib/utils.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

void rendererInit(void);
void rendererSetColor(enum Colors fg, enum Colors bg);
void rendererPutCharAt(char c, enum Colors color, size_t x, size_t y);
void rendererPutChar(char c);
void rendererScroll(void);
void rendererWrite(const char *data, size_t size);
void rendererWriteString(const char *data);
void rendererClearScreen(void);
