#pragma once

#include "../lib/utils.h"

struct GDTEntry
{
    uint16_t limitLow;
    uint16_t baseLow;
    uint8_t baseMiddle;
    uint8_t access;
    uint8_t granularity;
    uint8_t baseHigh;
    uint32_t baseUpper;
    uint32_t reserved;
} __attribute__((packed));

struct GDTPointer
{
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

void gdtInit(void);
void gdtSetEntry(int index, uint64_t base, uint64_t limit, uint8_t access, uint8_t granularity);
void gdtFlush(void);
