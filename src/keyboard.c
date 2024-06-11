#include "include/keyboard.h"

void keyboardInit()
{
    while (inPort(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_BUFFER) inPort(PS2_DATA_PORT);
    outPort(PS2_DATA_PORT, 0xF5);

    while (inPort(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_BUFFER) inPort(PS2_DATA_PORT);
    outPort(PS2_DATA_PORT, 0xF4);

    while (inPort(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_BUFFER) inPort(PS2_DATA_PORT);
}

uint8_t keyboardGetScancode()
{
    while (!(inPort(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_BUFFER));
    return inPort(PS2_DATA_PORT);
}

const char *keyboardGetKey()
{
    static const char *scancodeMap[] = {
            "Unknown", "Escape", "1", "2", "3", "4", "5", "6",
            "7", "8", "9", "0", "-", "=", "Backspace", "Tab",
            "q", "w", "e", "r", "t", "y", "u", "i",
            "o", "p", "[", "]", "Enter", "Left Ctrl", "a", "s",
            "d", "f", "g", "h", "j", "k", "l", ";",
            "'", "`", "Left Shift", "\\", "z", "x", "c", "v",
            "b", "n", "m", ",", ".", "/", "Right Shift", "Print Screen", "Left Alt",
            "Space", "Caps Lock", "F1", "F2", "F3", "F4", "F5", "F6",
            "F7", "F8", "F9", "F10", "Num Lock", "Scroll Lock", "Home", "Up",
            "Page Up", "-", "Left", "5", "Right", "+", "End", "Down",
            "Page Down", "Insert", "Delete", "Unknown", "Unknown", "Unknown", "Unknown", "F11",
            "F12", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown"
    };

    static const char *shiftScancodeMap[] = {
            "Unknown", "Escape", "!", "@", "#", "$", "%", "^",
            "&", "*", "(", ")", "_", "+", "Backspace", "Tab",
            "Q", "W", "E", "R", "T", "Y", "U", "I",
            "O", "P", "{", "}", "Enter", "Left Ctrl", "A", "S",
            "D", "F", "G", "H", "J", "K", "L", ":",
            "\"", "~", "Left Shift", "|", "Z", "X", "C", "V",
            "B", "N", "M", "<", ">", "?", "Right Shift", "Print Screen", "Left Alt",
            "Space", "Caps Lock", "F1", "F2", "F3", "F4", "F5", "F6",
            "F7", "F8", "F9", "F10", "Num Lock", "Scroll Lock", "Home", "Up",
            "Page Up", "-", "Left", "5", "Right", "+", "End", "Down",
            "Page Down", "Insert", "Delete", "Unknown", "Unknown", "Unknown", "Unknown", "F11",
            "F12", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown"
    };

    static const char *capsScancodeMap[] = {
            "Unknown", "Escape", "1", "2", "3", "4", "5", "6",
            "7", "8", "9", "0", "-", "=", "Backspace", "Tab",
            "Q", "W", "E", "R", "T", "Y", "U", "I",
            "O", "P", "[", "]", "Enter", "Left Ctrl", "A", "S",
            "D", "F", "G", "H", "J", "K", "L", ";",
            "'", "`", "Left Shift", "\\", "Z", "X", "C", "V",
            "B", "N", "M", ",", ".", "/", "Right Shift", "Print Screen", "Left Alt",
            "Space", "Caps Lock", "F1", "F2", "F3", "F4", "F5", "F6",
            "F7", "F8", "F9", "F10", "Num Lock", "Scroll Lock", "Home", "Up",
            "Page Up", "-", "Left", "5", "Right", "+", "End", "Down",
            "Page Down", "Insert", "Delete", "Unknown", "Unknown", "Unknown", "Unknown", "F11",
            "F12", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
            "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown"
    };

    uint8_t scancode = keyboardGetScancode();
    static int shift = 0, caps = 0;

    if (scancode == 0x2A || scancode == 0x36) shift = 1;
    else if (scancode == 0xAA || scancode == 0xB6) shift = 0;
    else if (scancode == 0x3A) caps = !caps;

    return shift ? shiftScancodeMap[scancode] : caps ? capsScancodeMap[scancode] : scancodeMap[scancode];
}
