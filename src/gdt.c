#include "include/gdt.h"

struct GDTEntry gdtEntries[3];
struct GDTPointer gdtPointer;

void gdtInit()
{
    gdtPointer.limit = (sizeof(struct GDTEntry) * 3) - 1;
    gdtPointer.base = (uintptr_t) &gdtEntries;

    gdtSetEntry(0, 0, 0, 0, 0);
    gdtSetEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdtSetEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    gdtFlush();
}

void gdtSetEntry(int index, uint64_t base, uint64_t limit, uint8_t access, uint8_t granularity)
{
    gdtEntries[index].baseLow = (base & 0xFFFF);
    gdtEntries[index].baseMiddle = (base >> 16) & 0xFF;
    gdtEntries[index].baseHigh = (base >> 24) & 0xFF;
    gdtEntries[index].baseUpper = (base >> 32) & 0xFFFFFFFF;

    gdtEntries[index].limitLow = (limit & 0xFFFF);
    gdtEntries[index].granularity = ((limit >> 16) & 0x0F);
    gdtEntries[index].granularity |= (granularity & 0xF0);

    gdtEntries[index].access = access;
    gdtEntries[index].reserved = 0;
}

void gdtFlush() { __asm__ volatile("lgdt (%0)" : : "r" (&gdtPointer)); }
