#pragma once

#include <types.h>
#include <mm/heap.h>

extern heap* kernel_heap;

void  kheap_init(u64 initial_size);
void* kmalloc(u64 size);
void  kfree(void* ptr);