#include "./include/keyboard.h"

enum Mode keyboardMode = MODE_TYPE;
const char *scancodeTable[] = {
        "Unknown", "Escape", "1", "2", "3", "4", "5", "6", "7", "8",
        "9", "0", "-", "=", "Backspace", "Tab", "q", "w", "e", "r",
        "t", "y", "u", "i", "o", "p", "[", "]", "Enter", "Left Ctrl",
        "a", "s", "d", "f", "g", "h", "j", "k", "l", ";",
        "'", "`", "Right Shift", "\\", "z", "x", "c", "v", "b",
        "n", "m", ",", ".", "/", "Left Shift", "Keypad *", "Left Alt", "Space"
};

void keyboardInit(void)
{
    while (inPort(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_BUFFER) inPort(PS2_DATA_PORT);
    outPort(PS2_DATA_PORT, 0xF5);

    while (inPort(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_BUFFER) inPort(PS2_DATA_PORT);
    outPort(PS2_DATA_PORT, 0xF4);

    while (inPort(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_BUFFER) inPort(PS2_DATA_PORT);
}

uint8_t keyboardGetScancode(void)
{
    while (!(inPort(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_BUFFER));
    return inPort(PS2_DATA_PORT);
}

const char *keyboardGetKey()
{
    uint8_t scancode = keyboardGetScancode();
    static int shift = 0, caps = 0;

    switch (scancode)
    {
        case 0x2A:
        case 0x36:
            shift = 1;
            return "";
        case 0xAA:
        case 0xB6:
            shift = 0;
            return "";
        case 0x3A:
            caps ^= 1;
            return "";
        case 0x0E:
            return "Backspace";
        case 0x1C:
            return "Enter";
        case 0x39:
            return "Space";
        default:
            if (scancode > sizeof(scancodeTable) / sizeof(*scancodeTable) - 1) return "";
            return shift ^ caps
                   ? scancodeTable[scancode][0] >= 'a' && scancodeTable[scancode][0] <= 'z'
                     ? scancodeTable[scancode] - 32
                     : scancodeTable[scancode]
                   : scancodeTable[scancode];
    }
}

void keyboardSetMode(enum Mode mode) { keyboardMode = mode; }
enum Mode keyboardGetMode(void) { return keyboardMode; }
