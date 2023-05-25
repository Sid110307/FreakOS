// TODO:
// - Move from VGA text mode to a graphical mode
// - Implement terminal scrolling
// - Render colorful ASCII art
// - Implement a keyboard driver
// - Implement a filesystem driver
// - Implement a simple shell
// - Add support for mouse input
// - Add audio support
// - Implement a graphical interface

#include <stddef.h>
#include <stdint.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

enum Colors
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHT_GREY = 7,
	DARK_GREY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	LIGHT_MAGENTA = 13,
	LIGHT_BROWN = 14,
	WHITE = 15,
};

static inline enum Colors vgaEntryColor(enum Colors fg, enum Colors bg)
{
	return fg | (bg << 4);
}

static inline uint16_t vgaEntry(unsigned char displayChar, enum Colors color)
{
	return (uint16_t) displayChar | ((uint16_t) color << 8);
}

static inline size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len]) len++;

	return len;
}

size_t terminalRow, terminalColumn;
enum Colors terminalColor;
__attribute__((unused)) uint16_t* videoMemory;

void terminalInit(void)
{
	terminalRow = 0;
	terminalColumn = 0;
	terminalColor = vgaEntryColor(LIGHT_GREY, BLACK);
	videoMemory = (uint16_t*) 0xB8000;

	for (size_t y = 0; y < SCREEN_HEIGHT; y++)
		for (size_t x = 0; x < SCREEN_WIDTH; x++)
			videoMemory[y * SCREEN_WIDTH + x] = vgaEntry(' ', terminalColor);
}

void terminalSetColor(enum Colors fg, enum Colors bg)
{
	terminalColor = vgaEntryColor(fg, bg);
}

void terminalPutCharAt(char c, enum Colors color, size_t x, size_t y)
{
	const size_t index = y * SCREEN_WIDTH + x;
	videoMemory[index] = vgaEntry(c, color);
}

void terminalPutChar(char c)
{
	switch (c)
	{
		case '\n':
			terminalColumn = 0;
			terminalRow++;
			break;
		case '\t':
			terminalColumn += 4;
			break;
		case '\b':
			terminalColumn--;
			break;
		case '\r':
			terminalColumn = 0;
			break;
		case '\f':
			terminalRow = 0;
			break;
		case '\v':
			terminalRow++;
			break;
		default:
			terminalPutCharAt(c, terminalColor, terminalColumn, terminalRow);
			terminalColumn++;

			break;
	}
}

void terminalWrite(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++) terminalPutChar(data[i]);
}

void terminalWriteString(const char* data)
{
	terminalWrite(data, strlen(data));
}

void main(void)
{
	terminalInit();
	terminalWriteString("Hello, world!\n");
}
