#pragma once

#include <stdint.h>

#define SHIFT_PRESSED 0x2A
#define SHIFT_RELEASED 0xAA
#define CAPS_LOCK_TOGGLE 0x3A

void keyboardInit(void);
uint8_t keyboardGetScancode(void);
const char* keyboardGetKey(void);
