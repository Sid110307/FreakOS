#pragma once

#include "../lib/utils.h"

struct IDTDescEntry
{
    uint16_t offset1, offset2, selector;
    uint8_t zero, typeAttr;
} __attribute__((packed));

struct IDTDescriptor
{
    uint16_t size;
    uint32_t offset;
} __attribute__((packed));

extern void idtLoad(struct IDTDescriptor *idtDescriptor);

void idtInit();
void idtSetEntry(uint8_t index, uint32_t offset, uint16_t selector, uint8_t typeAttr);
