#include "./include/renderer.h"

size_t terminalRow, terminalColumn;
enum Colors terminalColor;
__attribute__((unused)) uint16_t* videoMemory;

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

void terminalInit(void)
{
	terminalRow = 0;
	terminalColumn = 0;
	terminalColor = vgaEntryColor(COLOR_WHITE, COLOR_BLACK);
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

	if (terminalColumn >= SCREEN_WIDTH)
	{
		terminalColumn = 0;
		terminalRow++;
	}

	if (terminalRow >= SCREEN_HEIGHT)
	{
		terminalScroll();
		terminalRow--;
	}
}

void terminalScroll(void)
{
	for (size_t y = 0; y < SCREEN_HEIGHT - 1; y++)
		for (size_t x = 0; x < SCREEN_WIDTH; x++)
			videoMemory[y * SCREEN_WIDTH + x] = videoMemory[(y + 1) * SCREEN_WIDTH + x];

	for (size_t x = 0; x < SCREEN_WIDTH; x++)
		videoMemory[(SCREEN_HEIGHT - 1) * SCREEN_WIDTH + x] = vgaEntry(' ', terminalColor);
}

void terminalWrite(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++) terminalPutChar(data[i]);
}

void terminalWriteString(const char* data)
{
	terminalWrite(data, strlen(data));
}
