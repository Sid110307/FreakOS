#pragma once

#include "../lib/utils.h"

#define PS2_DATA_PORT 0x60
#define PS2_STATUS_PORT 0x64

#define PS2_STATUS_OUTPUT_BUFFER 0x01

void keyboardInit(void);
uint8_t keyboardGetScancode(void);
const char *keyboardGetKey(int onlyChar);
