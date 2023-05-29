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

const char *keyboardGetKey(void)
{
    uint8_t scancode = keyboardGetScancode();
    static uint8_t shift = 0, caps = 0;

    if (scancode & 0x80)
    {
        scancode &= 0x7F;
        switch (scancode)
        {
            case 0x2A:
            case 0x36:
                shift = 0;
                return "";
            case 0x3A:
                caps ^= 1;
                return "";
            default:
                return "";
        }
    }

    switch (scancode)
    {
        case 0x02:
            return shift ? "!" : "1";
        case 0x03:
            return shift ? "@" : "2";
        case 0x04:
            return shift ? "#" : "3";
        case 0x05:
            return shift ? "$" : "4";
        case 0x06:
            return shift ? "%" : "5";
        case 0x07:
            return shift ? "^" : "6";
        case 0x08:
            return shift ? "&" : "7";
        case 0x09:
            return shift ? "*" : "8";
        case 0x0A:
            return shift ? "(" : "9";
        case 0x0B:
            return shift ? ")" : "0";
        case 0x0C:
            return shift ? "_" : "-";
        case 0x0D:
            return shift ? "+" : "=";
        case 0x0E:
            return "Backspace";
        case 0x0F:
            return "Tab";
        case 0x10:
            return (shift ^ caps) ? "Q" : "q";
        case 0x11:
            return (shift ^ caps) ? "W" : "w";
        case 0x12:
            return (shift ^ caps) ? "E" : "e";
        case 0x13:
            return (shift ^ caps) ? "R" : "r";
        case 0x14:
            return (shift ^ caps) ? "T" : "t";
        case 0x15:
            return (shift ^ caps) ? "Y" : "y";
        case 0x16:
            return (shift ^ caps) ? "U" : "u";
        case 0x17:
            return (shift ^ caps) ? "I" : "i";
        case 0x18:
            return (shift ^ caps) ? "O" : "o";
        case 0x19:
            return (shift ^ caps) ? "P" : "p";
        case 0x1A:
            return (shift ^ caps) ? "{" : "[";
        case 0x1B:
            return (shift ^ caps) ? "}" : "]";
        case 0x1C:
            return "Enter";
        case 0x1D:
            return "Left Control";
        case 0x1E:
            return (shift ^ caps) ? "A" : "a";
        case 0x1F:
            return (shift ^ caps) ? "S" : "s";
        case 0x20:
            return (shift ^ caps) ? "D" : "d";
        case 0x21:
            return (shift ^ caps) ? "F" : "f";
        case 0x22:
            return (shift ^ caps) ? "G" : "g";
        case 0x23:
            return (shift ^ caps) ? "H" : "h";
        case 0x24:
            return (shift ^ caps) ? "J" : "j";
        case 0x25:
            return (shift ^ caps) ? "K" : "k";
        case 0x26:
            return (shift ^ caps) ? "L" : "l";
        case 0x27:
            return (shift ^ caps) ? ":" : ";";
        case 0x28:
            return (shift ^ caps) ? "\"" : "'";
        case 0x29:
            return (shift ^ caps) ? "~" : "`";
        case 0x2A:
            shift = 1;
            return "Left Shift";
        case 0x2B:
            return (shift ^ caps) ? "|" : "\\";
        case 0x2C:
            return (shift ^ caps) ? "Z" : "z";
        case 0x2D:
            return (shift ^ caps) ? "X" : "x";
        case 0x2E:
            return (shift ^ caps) ? "C" : "c";
        case 0x2F:
            return (shift ^ caps) ? "V" : "v";
        case 0x30:
            return (shift ^ caps) ? "B" : "b";
        case 0x31:
            return (shift ^ caps) ? "N" : "n";
        case 0x32:
            return (shift ^ caps) ? "M" : "m";
        case 0x33:
            return (shift ^ caps) ? "<" : ",";
        case 0x34:
            return (shift ^ caps) ? ">" : ".";
        case 0x35:
            return (shift ^ caps) ? "?" : "/";
        case 0x36:
            shift = 1;
            return "Right Shift";
        case 0x37:
            return "Keypad *";
        case 0x38:
            return "Left Alt";
        case 0x39:
            return "Space";
        case 0x3A:
            caps ^= 1;
            return "Caps Lock";
        case 0x3B:
            return "F1";
        case 0x3C:
            return "F2";
        case 0x3D:
            return "F3";
        case 0x3E:
            return "F4";
        case 0x3F:
            return "F5";
        case 0x40:
            return "F6";
        case 0x41:
            return "F7";
        case 0x42:
            return "F8";
        case 0x43:
            return "F9";
        case 0x44:
            return "F10";
        case 0x45:
            return "Num Lock";
        case 0x46:
            return "Scroll Lock";
        case 0x47:
            return "Keypad 7";
        case 0x48:
            return "Keypad 8";
        case 0x49:
            return "Keypad 9";
        case 0x4A:
            return "Keypad -";
        case 0x4B:
            return "Keypad 4";
        case 0x4C:
            return "Keypad 5";
        case 0x4D:
            return "Keypad 6";
        case 0x4E:
            return "Keypad +";
        case 0x4F:
            return "Keypad 1";
        case 0x50:
            return "Keypad 2";
        case 0x51:
            return "Keypad 3";
        case 0x52:
            return "Keypad 0";
        case 0x53:
            return "Keypad .";
        case 0x54:
            return "Unknown";
        case 0x55:
            return "Unknown";
        case 0x56:
            return "Unknown";
        case 0x57:
            return "F11";
        case 0x58:
            return "F12";
        default:
            return "Unknown";
    }
}
