/*
 *  CREDITS: asterd-og on GitHub
 *  https://github.com/asterd-og/QuasarOS/
 */

#include <arch/x86_64/tables/idt/idt.h>
#include <arch/x86_64/cpu/serial.h>
#include <arch/x86_64/cpu/pic.h>
#include <flanterm/flanterm.h>
#include <kernel/kernel.h>
#include <lib/printf.h>
#include <lib/libc.h>

__attribute__((aligned(0x10)))
static idt_entry idt_entries[256];
static idtr      idt_data;
extern void*     idt_int_table[];

void* irq_handlers[16] = {0};

static const char* idt_msg[32] = {
    "Division by zero",
    "Debug",
    "Non-maskable interrupt",
    "Breakpoint",
    "Detected overflow",
    "Out-of-bounds",
    "Invalid opcode",
    "No coprocessor",
    "Double fault",
    "Coprocessor segment overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown interrupt",
    "Coprocessor fault",
    "Alignment check",
    "Machine check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};

void idt_init() {
    asm volatile ("cli");

    for (u16 vec = 0; vec < 48; vec++)
        idt_set_entry(vec, idt_int_table[vec]);

    idt_data = (idtr) {
        .size   = (u16)sizeof(idt_entry) * 48 - 1,
        .offset = (u64)idt_entries
    };

    asm volatile ("lidt %0" : : "m"(idt_data) : "memory");
    asm volatile ("sti");
}

void idt_reinit() {
    asm ("lidt %0" : : "m"(idt_data) : "memory");
    asm ("sti");
}

void idt_set_entry(u8 vec, void* isr) {
    idt_entries[vec].low  = (u64)isr & 0xFFFF;
    idt_entries[vec].cs   = 0x28;
    idt_entries[vec].ist  = 0;
    idt_entries[vec].attr = (u8)0x8E;
    idt_entries[vec].mid  = ((u64)isr >> 16) & 0xFFFF;
    idt_entries[vec].high = ((u64)isr >> 32) & 0xFFFFFFFF;
    idt_entries[vec].resv = 0;
}

void irq_register(u8 vec, void* handler) {
    irq_handlers[vec] = handler;
}

void irq_unregister(u8 vec) {
    irq_handlers[vec] = NULL;
}

void isr_handler(registers* r) {
    if (r->int_no == 0xFF)
        return; // Spurious interrupt   

    asm volatile("cli");

    for (u64 y = 0; y < framebuffer->height; y++) {
        for (u64 x = 0; x < framebuffer->width; x++) { 
            fb_addr[y * framebuffer->width + x] = 0xAA;
        }
    }

    flanterm_write(flanterm_context, "\033[37;44m\033[H\033[2J\033[?25l", 21);
    printf("SivertOS 0.0.1\nSystem fault!\n\n"
        "RAX=0x%18x   RBX=0x%18x   RCX=0x%18x   RDX=0x%18x\n"
        "RSI=0x%18x   RDI=0x%18x   RBP=0x%18x   RSP=0x%18x\n"
        "R8 =0x%18x   R9 =0x%18x   R10=0x%18x   R11=0x%18x\n"
        "R12=0x%18x   R13=0x%18x   R14=0x%18x   R15=0x%18x\n"
        "RIP=0x%18x   RFL=0x%18x\n\n"
        "Error code: %s\n\nPlease restart your computer.",
        
        (u32)r->rax, (u32)r->rbx, (u32)r->rcx, (u32)r->rdx,
        (u32)r->rsi, (u32)r->rdi, (u32)r->rbp, (u32)r->rsp,
        (u32)r->r8,  (u32)r->r9,  (u32)r->r10, (u32)r->r11,
        (u32)r->r12, (u32)r->r13, (u32)r->r14, (u32)r->r15,
        (u32)r->rip, (u32)r->rflags, idt_msg[r->int_no]);

    for (;;) asm volatile("hlt");
}

void irq_handler(registers* r) {
    void(*handler)(registers*);

    handler = irq_handlers[r->int_no - 32];

    if ((u64)irq_handlers[r->int_no - 32] != 0) {
        handler(r);
    }
    
    pic_eoi(r->int_no - 32);
}