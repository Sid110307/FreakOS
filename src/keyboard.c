#include "./include/keyboard.h"

static inline void outPort(uint16_t port, uint8_t value)
{
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline uint8_t inPort(uint16_t port)
{
    uint8_t value;
    asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));

    return value;
}

void keyboardInit(void)
{
    outPort(0x20, 0x11);
    outPort(0xA0, 0x11);
    outPort(0x21, 0x20);
    outPort(0xA1, 0x28);
    outPort(0x21, 0x04);
    outPort(0xA1, 0x02);
    outPort(0x21, 0x01);
    outPort(0xA1, 0x01);
    outPort(0x21, 0x0);
    outPort(0xA1, 0x0);
}

uint8_t keyboardGetScancode(void)
{
    return inPort(0x60);
}

const char *keyboardGetKey(void)
{
    static const char *scancodeMap[] = {
            "ERROR", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "BACKSPACE", "TAB", "q", "w",
            "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "ENTER", "LEFT CTRL", "a", "s", "d", "f", "g", "h", "j",
            "k", "l", ";", "'", "`", "LEFT SHIFT", "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/",
            "RIGHT SHIFT", "PRINT SCREEN", "LEFT ALT", "SPACE", "CAPS LOCK", "F1", "F2", "F3", "F4", "F5", "F6", "F7",
            "F8", "F9", "F10", "NUM LOCK", "SCROLL LOCK", "HOME", "UP", "PAGE UP", "-", "LEFT ARROW", "MIDDLE MOUSE",
            "RIGHT ARROW", "+", "END", "DOWN", "PAGE DOWN", "INSERT", "DELETE", "ERROR", "ERROR", "ERROR", "F11", "F12",
            "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "RIGHT CTRL", "/", "PRINT SCREEN",
            "RIGHT ALT", "RIGHT ALT", "HOME", "UP", "PAGE UP", "LEFT ARROW", "RIGHT ARROW", "END", "DOWN", "PAGE DOWN",
            "INSERT", "DELETE", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "ERROR", "PAUSE", "LEFT SUPER",
            "RIGHT SUPER"
    };

    static uint8_t isShiftPressed = 0;
    static uint8_t isCapsLockOn = 0;

    uint8_t scancode = keyboardGetScancode();
    switch (scancode)
    {
        case SHIFT_PRESSED:
        case SHIFT_RELEASED:
            isShiftPressed = (scancode == SHIFT_PRESSED);
            return "";
        case CAPS_LOCK_TOGGLE:
            isCapsLockOn = !isCapsLockOn;
            return "";
        default:
            if (scancode & 0x80) return "";
            if (isShiftPressed)
            {
                char *str = (char *) scancodeMap[scancode];
                for (uint8_t i = 0; str[i] != '\0'; i++)
                {
                    if (str[i] >= 'a' && str[i] <= 'z') str[i] -= 32;
                    else if (str[i] >= 'A' && str[i] <= 'Z') str[i] += 32;
                }

                return str;
            } else if (isCapsLockOn)
            {
                char *str = (char *) scancodeMap[scancode];
                for (uint8_t i = 0; str[i] != '\0'; i++)
                {
                    if (str[i] >= 'a' && str[i] <= 'z') str[i] -= 32;
                    else if (str[i] >= 'A' && str[i] <= 'Z') str[i] += 32;
                }

                return str;
            } else return scancodeMap[scancode];
    }
}
