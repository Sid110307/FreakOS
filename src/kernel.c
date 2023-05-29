// TODO:
// - Implement terminal scrolling
// - Render colorful ASCII art
// - Implement a keyboard driver
// - Implement a filesystem driver
// - Implement a simple shell
// - Add support for mouse input
// - Add audio support
// - Implement a graphical interface

#include "./include/renderer.h"
#include "./include/gdt.h"
#include "./include/idt.h"
#include "./include/keyboard.h"

static inline int strcmp(const char *str1, const char *str2)
{
    while (*str1 && *str1 == *str2)
    {
        str1++;
        str2++;
    }

    return *(const unsigned char *) str1 - *(const unsigned char *) str2;
}

void main(void)
{
    gdtInit();
    idtInit();
    keyboardInit();
    rendererInit();

    rendererSetColor(COLOR_WHITE, COLOR_BLACK);
    while (1)
    {
        const char *c = keyboardGetKey();

        rendererWriteString("Scancode: 0x");
        rendererWriteHex(keyboardGetScancode());
        rendererWriteString(" | Char: ");

        if (strcmp(c, "ERROR") == 0) rendererSetColor(COLOR_RED, COLOR_BLACK);
        else rendererSetColor(COLOR_WHITE, COLOR_BLACK);

        rendererWriteString(c);
        rendererWriteString("                \r");
    }
}
