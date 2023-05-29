#include "./include/idt.h"

void idtInit(void)
{
    struct IDTDescriptor idtDescriptor;
    idtDescriptor.size = 256 * sizeof(struct IDTDescEntry) - 1;
    idtDescriptor.offset = (uint32_t) idtSetEntry;

    idtLoad(&idtDescriptor);
}

void idtSetEntry(uint8_t index, uint32_t offset, uint16_t selector, uint8_t typeAttr)
{
    struct IDTDescEntry *entry = (struct IDTDescEntry *) (0x800 + index * sizeof(struct IDTDescEntry));

    entry->offset1 = offset & 0xFFFF;
    entry->offset2 = (offset >> 16) & 0xFFFF;
    entry->selector = selector;
    entry->zero = 0;
    entry->typeAttr = typeAttr;
}
