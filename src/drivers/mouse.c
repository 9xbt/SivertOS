#include <drivers/mouse.h>

u8 mouse_read();

void mouse_handler(registers* regs) {
    printf("Mouse Interrupt!\n");

}

u8 mouse_read() {
    return inb(0x60);
}

void mouse_init() {
    // mouse interrupt is 12

    outb(0x64, 0x20); // Enable auxiliary PS/2 port
    outb(0x64, 0xA8); // Enable auxiliary PS/2 device
    

    irq_register(12, mouse_handler);
}