#include "idt.h"

// Initialize the IDT
void idt_init() {
    g_idt_ptr.base_address = g_idt;
    g_idt_ptr.limit = sizeof(g_idt) - 1;
    pic_init();

    idt_set_entry(0, exception_0, 0x08, 0x8E);
    idt_set_entry(1, exception_1, 0x08, 0x8E);
    idt_set_entry(2, exception_2, 0x08, 0x8E);
    idt_set_entry(3, exception_3, 0x08, 0x8E);
    idt_set_entry(4, exception_4, 0x08, 0x8E);
    idt_set_entry(5, exception_5, 0x08, 0x8E);
    idt_set_entry(6, exception_6, 0x08, 0x8E);
    idt_set_entry(7, exception_7, 0x08, 0x8E);
    idt_set_entry(8, exception_8, 0x08, 0x8E);
    idt_set_entry(9, exception_9, 0x08, 0x8E);
    idt_set_entry(10, exception_10, 0x08, 0x8E);
    idt_set_entry(11, exception_11, 0x08, 0x8E);
    idt_set_entry(12, exception_12, 0x08, 0x8E);
    idt_set_entry(13, exception_13, 0x08, 0x8E);
    idt_set_entry(14, exception_14, 0x08, 0x8E);
    idt_set_entry(15, exception_15, 0x08, 0x8E);
    idt_set_entry(16, exception_16, 0x08, 0x8E);
    idt_set_entry(17, exception_17, 0x08, 0x8E);
    idt_set_entry(18, exception_18, 0x08, 0x8E);
    idt_set_entry(19, exception_19, 0x08, 0x8E);
    idt_set_entry(20, exception_20, 0x08, 0x8E);
    idt_set_entry(21, exception_21, 0x08, 0x8E);
    idt_set_entry(22, exception_22, 0x08, 0x8E);
    idt_set_entry(23, exception_23, 0x08, 0x8E);
    idt_set_entry(24, exception_24, 0x08, 0x8E);
    idt_set_entry(25, exception_25, 0x08, 0x8E);
    idt_set_entry(26, exception_26, 0x08, 0x8E);
    idt_set_entry(27, exception_27, 0x08, 0x8E);
    idt_set_entry(28, exception_28, 0x08, 0x8E);
    idt_set_entry(29, exception_29, 0x08, 0x8E);
    idt_set_entry(30, exception_30, 0x08, 0x8E);
    idt_set_entry(31, exception_31, 0x08, 0x8E);
    idt_set_entry(32, irq_0, 0x08, 0x8E);
    idt_set_entry(33, irq_1, 0x08, 0x8E);
    idt_set_entry(34, irq_2, 0x08, 0x8E);
    idt_set_entry(35, irq_3, 0x08, 0x8E);
    idt_set_entry(36, irq_4, 0x08, 0x8E);
    idt_set_entry(37, irq_5, 0x08, 0x8E);
    idt_set_entry(38, irq_6, 0x08, 0x8E);
    idt_set_entry(39, irq_7, 0x08, 0x8E);
    idt_set_entry(40, irq_8, 0x08, 0x8E);
    idt_set_entry(41, irq_9, 0x08, 0x8E);
    idt_set_entry(42, irq_10, 0x08, 0x8E);
    idt_set_entry(43, irq_11, 0x08, 0x8E);
    idt_set_entry(44, irq_12, 0x08, 0x8E);
    idt_set_entry(45, irq_13, 0x08, 0x8E);
    idt_set_entry(46, irq_14, 0x08, 0x8E);
    idt_set_entry(47, irq_15, 0x08, 0x8E);
    idt_set_entry(128, exception_128, 0x08, 0x8E);

    load_idt((uint32_t)&g_idt_ptr);
    asm volatile("sti");
}