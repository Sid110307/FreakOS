#pragma once

#include "../lib/utils.h"

#define PS2_DATA_PORT 0x60
#define PS2_STATUS_PORT 0x64

#define PS2_STATUS_OUTPUT_BUFFER 0x01

enum Mode
{
    MODE_TYPE,
    MODE_OVERWRITE
};

void keyboardInit();
uint8_t keyboardGetScancode();
const char *keyboardGetKey();

void keyboardSetMode(enum Mode mode);
enum Mode keyboardGetMode();
