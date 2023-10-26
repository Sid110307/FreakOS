// TODO:
//  - Add support for insert and delete keys (type and overwrite modes, using rendererSetPosColor)
//  - Implement paging
//  - Implement terminal scrolling
//  - Add support for page up and page down keys
//  - Implement a simple shell
//  - Implement a filesystem driver
//  - Add support for mouse input
//  - Add audio support
//  - Implement a graphical interface

#include "./include/renderer.h"
#include "./include/gdt.h"
#include "./include/idt.h"
#include "./include/keyboard.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

void kernelInit(void)
{
    Framebuffer framebuffer = {
            .address = (uint8_t *) 0x000B8000,
            .width = SCREEN_WIDTH,
            .height = SCREEN_HEIGHT,
            .bytesPerPixel = 2
    };

    gdtInit();
    idtInit();
    keyboardInit();
    rendererInit(framebuffer, "fonts/zap-ext-light18.psf");

    rendererSetColor(COLOR_BLUE, COLOR_BLACK);
    rendererWriteString("  ______                  _       ____    _____ \n");
    rendererSetColor(COLOR_GREEN, COLOR_BLACK);
    rendererWriteString(" |  ____|                | |     / __ \\  / ____|\n");
    rendererSetColor(COLOR_CYAN, COLOR_BLACK);
    rendererWriteString(" | |__  _ __  ___   __ _ | | __ | |  | || (___  \n");
    rendererSetColor(COLOR_RED, COLOR_BLACK);
    rendererWriteString(" |  __|| '__|/ _ \\ / _` || |/ / | |  | | \\___ \\ \n");
    rendererSetColor(COLOR_MAGENTA, COLOR_BLACK);
    rendererWriteString(" | |   | |  |  __/| (_| ||   <  | |__| | ____) |\n");
    rendererSetColor(COLOR_BROWN, COLOR_BLACK);
    rendererWriteString(" |_|   |_|   \\___| \\__,_||_|\\_\\  \\____/ |_____/ \n\n");
    rendererSetColor(COLOR_LIGHT_GREY, COLOR_BLACK);
    rendererWriteString("========================================================\n");
    rendererSetColor(COLOR_DARK_GREY, COLOR_BLACK);
    rendererWriteString("||   A simple operating system written in C and ASM   ||\n");
    rendererSetColor(COLOR_LIGHT_BLUE, COLOR_BLACK);
    rendererWriteString("========================================================\n");
    rendererSetColor(COLOR_LIGHT_GREEN, COLOR_BLACK);
    rendererWriteString("||  Author:  ||      Siddharth Praveen Bharadwaj      ||\n");
    rendererSetColor(COLOR_LIGHT_CYAN, COLOR_BLACK);
    rendererWriteString("||  License: ||              MIT License              ||\n");
    rendererSetColor(COLOR_LIGHT_RED, COLOR_BLACK);
    rendererWriteString("||  GitHub:  ||      https://github.com/Sid110307     ||\n");
    rendererSetColor(COLOR_LIGHT_MAGENTA, COLOR_BLACK);
    rendererWriteString("||  Website: || https://sid110307.github.io/Sid110307 ||\n");
    rendererSetColor(COLOR_LIGHT_BROWN, COLOR_BLACK);
    rendererWriteString("========================================================\n\n");
    rendererSetColor(COLOR_WHITE, COLOR_BLACK);

    rendererMoveCaret(0, 16);
}

void main(void)
{
    kernelInit();
    while (1)
    {
        const char *key = keyboardGetKey();

        if (strcmp(key, "Escape") == 0)
        {
            rendererWriteString("\e");
            rendererSetCaretPos(0, 0);
        } else if (strcmp(key, "Space") == 0)
        {
            rendererWriteString(" ");
            rendererMoveCaret(1, 0);
        } else if (strcmp(key, "Home") == 0) rendererSetCaretPos(0, rendererGetCaretPosY());
        else if (strcmp(key, "End") == 0)
            rendererSetCaretPos((int) strlen(rendererGetLine(rendererGetCaretPosY())), rendererGetCaretPosY());
        else if (strcmp(key, "Up") == 0) rendererMoveCaret((int) rendererGetCaretPosX(), -1);
        else if (strcmp(key, "Down") == 0) rendererMoveCaret((int) rendererGetCaretPosX(), 1);
        else if (strcmp(key, "Left") == 0) rendererMoveCaret(-1, (int) rendererGetCaretPosY());
        else if (strcmp(key, "Right") == 0) rendererMoveCaret(1, (int) rendererGetCaretPosY());
        else if (strcmp(key, "Tab") == 0)
        {
            rendererWriteString("\t");
            rendererMoveCaret(INDENTATION, 0);
        } else if (strcmp(key, "Enter") == 0)
        {
            rendererWriteString("\n");
            rendererSetCaretPos(0, rendererGetCaretPosY() + 1);
        } else if (strcmp(key, "Backspace") == 0)
        {
            rendererWriteString("\b");
            rendererMoveCaret(-1, 0);
        } else if (strcmp(key, "Insert") == 0)
        {
            if (keyboardGetMode() == MODE_TYPE) keyboardSetMode(MODE_OVERWRITE);
            else keyboardSetMode(MODE_TYPE);
        } else if (strcmp(key, "Delete") == 0)
        {
            rendererWriteString("\b");
            rendererMoveCaret(1, 0);
        } else if (
                strcmp(key, "PgUp") == 0 || strcmp(key, "PgDn") == 0 ||
                strcmp(key, "Control") == 0 || strcmp(key, "Shift") == 0 || strcmp(key, "Alt") == 0 ||
                strcmp(key, "Num Lock") == 0 || strcmp(key, "Scroll Lock") == 0 || strcmp(key, "Caps Lock") == 0)
            continue;
        else
        {
            rendererWriteString(key);
            rendererMoveCaret((int) strlen(key), 0);
        }

        if (keyboardGetMode() == MODE_OVERWRITE)
            rendererSetPosColor(COLOR_BLACK, COLOR_WHITE, rendererGetCaretPosX(), rendererGetCaretPosY(),
                                rendererGetCaretPosX() + 1, rendererGetCaretPosY());
        else
            rendererSetPosColor(COLOR_WHITE, COLOR_BLACK, rendererGetCaretPosX(), rendererGetCaretPosY(),
                                rendererGetCaretPosX() + 1, rendererGetCaretPosY());
    }
}
