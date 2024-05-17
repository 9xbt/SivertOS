#include <lib/alloc.h>

heap* kernel_heap;

void kheap_init() {
    kernel_heap = heap_create();

    printf("\033[92m[  OK  ]\033[0m Kernel Heap Created.\n");
}

void* kmalloc(u64 size) {
    void* ptr = heap_alloc(kernel_heap, size);
    if (ptr == NULL) return NULL;
    return HIGHER_HALF(ptr);
}

void kfree(void* ptr) {
    heap_free(kernel_heap, PHYSICAL(ptr));
}