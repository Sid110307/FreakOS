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

void main(void)
{
    gdtInit();
    terminalInit();

    terminalSetColor(COLOR_BROWN, COLOR_LIGHT_GREY);
    terminalWriteString("Hello, world!\n");

    terminalSetColor(COLOR_LIGHT_RED, COLOR_LIGHT_GREEN);
    terminalWriteString("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc semper enim nec pretium "
                        "tincidunt. Donec tincidunt mauris elementum neque sodales congue. Nulla in nisl eu nibh "
                        "luctus vestibulum vitae a neque. Pellentesque ac nulla tincidunt, tristique diam ut, feugiat "
                        "tortor. Sed nisl sem, ultricies nec condimentum vel, hendrerit vel dolor. Vivamus ultricies "
                        "sollicitudin neque, eget aliquet augue gravida at. Nullam fermentum diam quis mollis auctor. "
                        "Phasellus elementum ultrices arcu eu porta. Vestibulum ante enim, ornare eu efficitur a, "
                        "finibus eu arcu. Nam justo quam, suscipit at metus at, luctus pharetra felis. Curabitur "
                        "finibus porttitor lacinia. Aliquam sapien justo, fermentum ac risus quis, volutpat sodales "
                        "dolor.\n");
}
