#include "./include/keyboard.h"

static inline void outPort(uint8_t value)
{
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(PS2_DATA_PORT));
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
    outPort(0xF5);

    while (inPort(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_BUFFER) inPort(PS2_DATA_PORT);
    outPort(0xF4);

    while (inPort(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_BUFFER) inPort(PS2_DATA_PORT);
}

uint8_t keyboardGetScancode(void)
{
    while (!(inPort(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_BUFFER));
    return inPort(PS2_DATA_PORT);
}

const char *keyboardGetKey(int onlyChar)
{
    uint8_t scancode = keyboardGetScancode();
    static uint8_t shift = 0, capsLock = 0, numLock = 0;

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
                capsLock ^= 1;
                return "";
            case 0x45:
                numLock ^= 1;
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
            return onlyChar == 0 ? "Backspace" : "\b";
        case 0x0F:
            return onlyChar == 0 ? "Tab" : "\t";
        case 0x10:
            return (shift ^ capsLock) ? "Q" : "q";
        case 0x11:
            return (shift ^ capsLock) ? "W" : "w";
        case 0x12:
            return (shift ^ capsLock) ? "E" : "e";
        case 0x13:
            return (shift ^ capsLock) ? "R" : "r";
        case 0x14:
            return (shift ^ capsLock) ? "T" : "t";
        case 0x15:
            return (shift ^ capsLock) ? "Y" : "y";
        case 0x16:
            return (shift ^ capsLock) ? "U" : "u";
        case 0x17:
            return (shift ^ capsLock) ? "I" : "i";
        case 0x18:
            return (shift ^ capsLock) ? "O" : "o";
        case 0x19:
            return (shift ^ capsLock) ? "P" : "p";
        case 0x1A:
            return (shift ^ capsLock) ? "{" : "[";
        case 0x1B:
            return (shift ^ capsLock) ? "}" : "]";
        case 0x1C:
            return onlyChar == 0 ? "Enter" : "\n";
        case 0x1D:
            return onlyChar == 0 ? "Left Control" : "";
        case 0x1E:
            return (shift ^ capsLock) ? "A" : "a";
        case 0x1F:
            return (shift ^ capsLock) ? "S" : "s";
        case 0x20:
            return (shift ^ capsLock) ? "D" : "d";
        case 0x21:
            return (shift ^ capsLock) ? "F" : "f";
        case 0x22:
            return (shift ^ capsLock) ? "G" : "g";
        case 0x23:
            return (shift ^ capsLock) ? "H" : "h";
        case 0x24:
            return (shift ^ capsLock) ? "J" : "j";
        case 0x25:
            return (shift ^ capsLock) ? "K" : "k";
        case 0x26:
            return (shift ^ capsLock) ? "L" : "l";
        case 0x27:
            return (shift ^ capsLock) ? ":" : ";";
        case 0x28:
            return (shift ^ capsLock) ? "\"" : "'";
        case 0x29:
            return (shift ^ capsLock) ? "~" : "`";
        case 0x2A:
            shift = 1;
            return onlyChar == 0 ? "Left Shift" : "";
        case 0x2B:
            return (shift ^ capsLock) ? "|" : "\\";
        case 0x2C:
            return (shift ^ capsLock) ? "Z" : "z";
        case 0x2D:
            return (shift ^ capsLock) ? "X" : "x";
        case 0x2E:
            return (shift ^ capsLock) ? "C" : "c";
        case 0x2F:
            return (shift ^ capsLock) ? "V" : "v";
        case 0x30:
            return (shift ^ capsLock) ? "B" : "b";
        case 0x31:
            return (shift ^ capsLock) ? "N" : "n";
        case 0x32:
            return (shift ^ capsLock) ? "M" : "m";
        case 0x33:
            return (shift ^ capsLock) ? "<" : ",";
        case 0x34:
            return (shift ^ capsLock) ? ">" : ".";
        case 0x35:
            return (shift ^ capsLock) ? "?" : "/";
        case 0x36:
            shift = 1;
            return onlyChar == 0 ? "Right Shift" : "";
        case 0x37:
            return onlyChar == 0 ? "Keypad *" : "*";
        case 0x38:
            return onlyChar == 0 ? "Left Alt" : "";
        case 0x39:
            return onlyChar == 0 ? "Space" : " ";
        case 0x3A:
            capsLock ^= 1;
            return onlyChar == 0 ? "Caps Lock" : "";
        case 0x3B:
            return onlyChar == 0 ? "F1" : "";
        case 0x3C:
            return onlyChar == 0 ? "F2" : "";
        case 0x3D:
            return onlyChar == 0 ? "F3" : "";
        case 0x3E:
            return onlyChar == 0 ? "F4" : "";
        case 0x3F:
            return onlyChar == 0 ? "F5" : "";
        case 0x40:
            return onlyChar == 0 ? "F6" : "";
        case 0x41:
            return onlyChar == 0 ? "F7" : "";
        case 0x42:
            return onlyChar == 0 ? "F8" : "";
        case 0x43:
            return onlyChar == 0 ? "F9" : "";
        case 0x44:
            return onlyChar == 0 ? "F10" : "";
        case 0x45:
            return onlyChar == 0 ? "Num Lock" : "";
        case 0x46:
            return onlyChar == 0 ? "Scroll Lock" : "";
        case 0x47:
            return onlyChar == 0 ? "Keypad 7" : numLock ? "7" : "Home";
        case 0x48:
            return onlyChar == 0 ? "Keypad 8" : numLock ? "8" : "Up";
        case 0x49:
            return onlyChar == 0 ? "Keypad 9" : numLock ? "9" : "PgUp";
        case 0x4A:
            return onlyChar == 0 ? "Keypad -" : "-";
        case 0x4B:
            return onlyChar == 0 ? "Keypad 4" : numLock ? "4" : "Left";
        case 0x4C:
            return onlyChar == 0 ? "Keypad 5" : numLock ? "5" : "";
        case 0x4D:
            return onlyChar == 0 ? "Keypad 6" : numLock ? "6" : "Right";
        case 0x4E:
            return onlyChar == 0 ? "Keypad +" : "+";
        case 0x4F:
            return onlyChar == 0 ? "Keypad 1" : numLock ? "1" : "End";
        case 0x50:
            return onlyChar == 0 ? "Keypad 2" : numLock ? "2" : "Down";
        case 0x51:
            return onlyChar == 0 ? "Keypad 3" : numLock ? "3" : "PgDn";
        case 0x52:
            return onlyChar == 0 ? "Keypad 0" : numLock ? "0" : "Insert";
        case 0x53:
            return onlyChar == 0 ? "Keypad ." : numLock ? "." : "Delete";
        case 0x57:
            return onlyChar == 0 ? "F11" : "";
        case 0x58:
            return onlyChar == 0 ? "F12" : "";
        case 0x54:
        case 0x55:
        case 0x56:
        default:
            return onlyChar == 0 ? "Unknown" : "";
    }
}
