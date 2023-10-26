#pragma once

#include "./types.h"

static char memory[1024];
typedef struct
{
    size_t size;
    int isFree;
} BlockHeader;

static inline void *malloc(size_t size)
{
    BlockHeader *header = (BlockHeader *) memory;
    while (header->size != 0)
    {
        if (header->isFree && header->size >= size + sizeof(BlockHeader))
        {
            BlockHeader *newBlock = (BlockHeader *) ((uint64_t) header + sizeof(BlockHeader) + size);
            newBlock->size = header->size - size - sizeof(BlockHeader);
            newBlock->isFree = 1;

            header->size = size;
            header->isFree = 0;

            return (void *) ((uint64_t) header + sizeof(BlockHeader));
        }

        header = (BlockHeader *) ((uint64_t) header + sizeof(BlockHeader) + header->size);
    }

    return 0;
}

static inline void free(void *ptr)
{
    BlockHeader *header = (BlockHeader *) memory;
    while (header->size != 0)
    {
        if ((uint64_t) header + sizeof(BlockHeader) == (uint64_t) ptr)
        {
            header->isFree = 1;
            return;
        }

        header = (BlockHeader *) ((uint64_t) header + sizeof(BlockHeader) + header->size);
    }
}
