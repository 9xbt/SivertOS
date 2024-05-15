#pragma once

#include <types.h>
#include <mm/pmm.h>
#include <mm/vmm.h>

#define HEAP_MAGIC 0xdeadbeef

typedef struct heap_pool {
    struct heap_pool* next;
    struct heap_pool* prev;
    u8 state;
    u32 magic;
    u64 size;
} heap_block;

typedef struct {
    heap_block* block_head;
} heap;

heap* heap_create();

void* heap_alloc(heap* h, u64 size);
void  heap_free (heap* h, void* ptr);