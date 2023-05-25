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

void main(void)
{
	terminalInit();
	terminalWriteString("Hello, World!\n");

	terminalSetColor(COLOR_BROWN, COLOR_LIGHT_GREEN);
	terminalWriteString("This is weird!\n");

	terminalSetColor(COLOR_LIGHT_RED, COLOR_LIGHT_BLUE);
	terminalWriteString("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum elementum, enim at facilisis viverra, urna ante congue sem, consectetur vehicula nisl odio id urna. Nullam consequat libero in nibh lobortis hendrerit.\n");
}
