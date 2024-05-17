#include <types.h>
#include <lib/printf.h>

void sse_enable() {
    u64 cr0;
    u64 cr4;
    asm volatile("mov %%cr0, %0" :"=r"(cr0) :: "memory");
    cr0 &= ~((u64)1 << 2);
    cr0 |= (u64)(1 << 1);
    asm volatile("mov %0, %%cr0" :: "r"(cr0) : "memory");
    asm volatile("mov %%cr4, %0" :"=r"(cr4) :: "memory");
    cr4 |= (u64)(3 << 9);
    asm volatile("mov %0, %%cr4" :: "r"(cr4) : "memory");

    printf("\033[92m[  OK  ]\033[0m SSE Enabled.\n");
}