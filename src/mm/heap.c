/*
 *  CREDITS: asterd-og on GitHub
 *  https://github.com/asterd-og/ZanOS/
 */

#include <mm/heap.h>
#include <lib/libc.h>
#include <lib/alloc.h>
#include <arch/x86_64/cpu/serial.h>
#include <mm/pmm.h>

heap* heap_create() {
    heap* h = (heap*)HIGHER_HALF(pmm_alloc(1));
    h->block_head = (heap_block*)HIGHER_HALF(pmm_alloc(1));
    h->block_head->magic = HEAP_MAGIC;
    h->block_head->next = h->block_head->prev = h->block_head;
    h->block_head->size = 0;
    h->block_head->state = 1;
    return h;
}

void* heap_alloc(heap* h, u64 size) {
    u64 pages = DIV_ROUND_UP(sizeof(heap_block) + size, PAGE_SIZE);
    void* buf = pmm_alloc(pages);
    if (h == kernel_heap)
        buf = HIGHER_HALF(buf);
    heap_block* block = (heap_block*)buf;
    block->magic = HEAP_MAGIC;
    block->size = size;
    block->state = 1;
    block->prev = h->block_head->prev;
    block->next = h->block_head;
    h->block_head->prev->next = block;
    h->block_head->prev = block;
    return block+1;
}

void heap_free(heap* h, void* ptr) {
    heap_block* block = (heap_block*)(ptr - sizeof(heap_block));
    if (block->magic != HEAP_MAGIC) {
        serial_printf("heap_free(): Invalid magic at pointer %lx.\n", ptr);
        return;
    }

    return;
    block->prev->next = block->next;
    block->next->prev = block->prev;
    u64 pages = DIV_ROUND_UP(sizeof(heap_block) + block->size, PAGE_SIZE);
    u8* buf = (u8*)(ptr - sizeof(heap_block));
    if (h == kernel_heap)
        buf = PHYSICAL(buf);
    pmm_free(buf, pages);
}

void* heap_realloc(heap* h, void* ptr, u64 size) {
    heap_block* block = (heap_block*)(ptr - sizeof(heap_block));
    if (block->magic != HEAP_MAGIC) {
        serial_printf("heap_realloc(): Invalid magic at pointer %lx.\n", ptr);
        return NULL;
    }
    void* new_ptr = heap_alloc(h, size);
    if (!new_ptr)
        return NULL;
    memcpy(new_ptr, ptr, block->size);
    heap_free(h, ptr);
    return new_ptr;
}