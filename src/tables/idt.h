#pragma once

#include <inttypes.h>

typedef struct {
    uint16_t base_low;              // Lower 16 bits 0-15 of the address to jump to when this interrupt fires
    uint16_t segment_selector;      // Code segment selector in GDT
    uint8_t zero;                   // Unused
    uint8_t type;                   // Types trap, interrupt gates
    uint16_t base_high;             // Upper 16 bits 16-31 of the address to jump to
} __attribute__((packed)) IDT;

typedef struct {
    uint16_t limit;                 // Limit size of all IDT segments
    uint32_t base_address;          // Base address of the first IDT segment
} __attribute__((packed)) IDT_PTR;

extern void load_idt(uint32_t idt_ptr);

IDT g_idt[256];
IDT_PTR g_idt_ptr;

static void idt_set_entry(int index, uint32_t base, uint16_t seg_sel, uint8_t flags) {
    IDT *this = &g_idt[index];

    this->base_low = base & 0xFFFF;
    this->segment_selector = seg_sel;
    this->zero = 0;
    this->type = flags | 0x60;
    this->base_high = (base >> 16) & 0xFFFF;
}

// External exception voids
extern void exception_0();
extern void exception_1();
extern void exception_2();
extern void exception_3();
extern void exception_4();
extern void exception_5();
extern void exception_6();
extern void exception_7();
extern void exception_8();
extern void exception_9();
extern void exception_10();
extern void exception_11();
extern void exception_12();
extern void exception_13();
extern void exception_14();
extern void exception_15();
extern void exception_16();
extern void exception_17();
extern void exception_18();
extern void exception_19();
extern void exception_20();
extern void exception_21();
extern void exception_22();
extern void exception_23();
extern void exception_24();
extern void exception_25();
extern void exception_26();
extern void exception_27();
extern void exception_28();
extern void exception_29();
extern void exception_30();
extern void exception_31();
extern void exception_128();

// External IRQ voids
extern void irq_0();
extern void irq_1();
extern void irq_2();
extern void irq_3();
extern void irq_4();
extern void irq_5();
extern void irq_6();
extern void irq_7();
extern void irq_8();
extern void irq_9();
extern void irq_10();
extern void irq_11();
extern void irq_12();
extern void irq_13();
extern void irq_14();
extern void irq_15();

// Initialize the IDT
void idt_init();