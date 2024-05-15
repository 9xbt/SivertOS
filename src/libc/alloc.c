#include <libc/alloc.h>

heap_ctrl* kernel_heap;

void kheap_init(u64 initial_size) {
    kernel_heap = heap_create(initial_size);
}

void* kmalloc(u64 size) {
    void* ptr = heap_alloc(kernel_heap, size);
    if (ptr == NULL) return NULL;
    return HIGHER_HALF(ptr);
}

void kfree(void* ptr) {
    heap_free(kernel_heap, PHYSICAL(ptr));
}