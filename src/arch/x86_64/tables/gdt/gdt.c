#include <arch/x86_64/tables/gdt/gdt.h>

u64 gdt_table[] = {
    0x0000000000000000, // Null segment
    0xFFFF0000009AAF00, // Kernel Mode Code Segment
    0xFFFF00000092CF00, // Kernel Mode Data Segment
    0xFFFF000000FAAF00, // User Mode Code Segment
    0xFFFF000000F2CF00  // User Mode Data Segment
};

gdtr gdt_data;

void gdt_init() {
    gdt_data = (gdtr) {
        .size = (sizeof(u64) * 5) - 1,
        .offset = (u64)&gdt_table
    };

    __asm__ volatile ("lgdt %0" :: "m"(gdt_data) : "memory");
}