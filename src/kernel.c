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

void kernelInit(void)
{
    gdtInit();
    idtInit();
    keyboardInit();
    rendererInit();

    rendererSetColor(COLOR_WHITE, COLOR_BLACK);
    rendererWriteString("Kernel initialized successfully!\n");
}

void main(void)
{
    kernelInit();
    while (1) rendererWriteString(keyboardGetKey(1));
}
