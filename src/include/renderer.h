#pragma once

#include <stddef.h>
#include <stdint.h>

#include "../lib/colors.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

void terminalInit(void);
void terminalSetColor(enum Colors fg, enum Colors bg);
void terminalPutCharAt(char c, enum Colors color, size_t x, size_t y);
void terminalPutChar(char c);
void terminalScroll(void);
void terminalWrite(const char *data, size_t size);
void terminalWriteString(const char *data);
