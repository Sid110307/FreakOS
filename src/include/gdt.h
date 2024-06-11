#pragma once

#include "types.h"

struct GDTEntry
{
    uint16_t limitLow, baseLow;
    uint8_t baseMiddle, access, granularity, baseHigh;
    uint32_t baseUpper, reserved;
} __attribute__((packed));

struct GDTPointer
{
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

void gdtInit();
void gdtSetEntry(int index, uint64_t base, uint64_t limit, uint8_t access, uint8_t granularity);
void gdtFlush();
