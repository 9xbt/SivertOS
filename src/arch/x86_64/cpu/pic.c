#include <arch/x86_64/cpu/pic.h>
#include <arch/x86_64/io.h>

void pic_remap() {
    uint8_t a1, a2;

    a1 = inb(PIC1_DAT);
    a2 = inb(PIC2_DAT);

    // This will start the init sequence in cascade mode
    outb(PIC1_CMD, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_CMD, ICW1_INIT | ICW1_ICW4);
    outb(PIC1_DAT, 0x20); // Master PIC offset
    outb(PIC2_DAT, 0x28); // Slave  PIC offset
    outb(PIC1_DAT, 0x04); // Tell master PIC there's slave PIC at IRQ2
    outb(PIC2_DAT, 0x02); // Tell slave PIC it's cascade identity
    outb(PIC1_DAT, ICW4_8086); // Use 8086 PIC
    outb(PIC2_DAT, ICW4_8086);
    outb(PIC1_DAT, a1); // Set mask
    outb(PIC2_DAT, a2);
}

void pic_eoi(u8 no) {
    if (no >= 8) {
        outb(PIC2, PIC_EOI);
    }
    outb(PIC1, PIC_EOI);
}