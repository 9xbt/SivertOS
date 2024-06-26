/*
 *  CREDITS: asterd-og on GitHub
 *  https://github.com/asterd-og/ZanOS/
 */

#pragma once

#include <types.h>

#define HEAP_MAGIC 0xdeadbeef

typedef struct heap_block {
    struct heap_block* next;
    struct heap_block* prev;
    u8 state;
    u32 magic;
    u64 size;
} heap_block;

typedef struct {
    heap_block* block_head;
} heap;

heap* heap_create();

void* heap_alloc(heap* h, u64 size);
void  heap_free(heap* h, void* ptr);
void* heap_realloc(heap* h, void* ptr, u64 size);