#pragma once

#include <stdint.h>

struct IDTDescEntry
{
    uint16_t offset1;
    uint16_t offset2;
    uint16_t selector;
    uint8_t zero;
    uint8_t typeAttr;
} __attribute__((packed));

struct IDTDescriptor
{
    uint16_t size;
    uint32_t offset;
} __attribute__((packed));

extern void idtLoad(struct IDTDescriptor *idtDescriptor);

void idtInit(void);
void idtSetEntry(uint8_t index, uint32_t offset, uint16_t selector, uint8_t typeAttr);
