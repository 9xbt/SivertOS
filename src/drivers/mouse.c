#include <drivers/mouse.h>

u8 mouse_cycle = 0;
i8 mouse_byte[3];

mouse_t mouse_state;

void mouse_handler(registers* regs) {
    (void)regs;

    u8 status = inb(0x64);

	if (status & 1)
		mouse_state.last = mouse_state.current;

	while (status & 1) {
		i8 mouse_in = inb(0x60);
		if (status & 0x20) {
			switch (mouse_cycle) {
				case 0:
					mouse_byte[0] = mouse_in;
					//if (!(mouse_in & 8)) return;
					mouse_cycle++;
					break;
				case 1:
					mouse_byte[1] = mouse_in;
					mouse_cycle++;
					break;
				case 2:
					mouse_byte[2] = mouse_in;

					if (mouse_byte[0] & 0x80 || mouse_byte[0] & 0x40) {
						/* x/y overflow? bad packet! */
						break;
					}

					mouse_state.current.left   = mouse_byte[0] & 1;
					mouse_state.current.right  = mouse_byte[0] & 2;
					mouse_state.current.middle = mouse_byte[0] & 4;
					mouse_state.current.x 	  += mouse_byte[1];
					mouse_state.current.y 	  -= mouse_byte[2];
					mouse_cycle = 0;

					if (mouse_state.current.x < 0) mouse_state.current.x = 0;
					if (mouse_state.current.y < 0) mouse_state.current.y = 0;
					if (mouse_state.current.x >= (i32)framebuffer->width) mouse_state.current.x = framebuffer->width - 1;
					if (mouse_state.current.y >= (i32)framebuffer->height) mouse_state.current.y = framebuffer->height - 1;
					break;
			}
		}
		status = inb(0x64);
    }
}

void mouse_wait(u8 a_type) {
	u32 timeout = 100000;

	if (!a_type) {
		while (--timeout) {
			if ((inb(0x64) & 1) == 1) {
				return;
			}
		}
		return;
	} else {
		while (--timeout) {
			if (!((inb(0x64) & 2))) {
				return;
			}
		}
		return;
	}
}

void mouse_write(u8 a_write) {
    mouse_wait(1);
    outb(0x64, 0xD4);
    mouse_wait(1);
    outb(0x60, a_write);
}

u8 mouse_read() {
    mouse_wait(0);
    return inb(0x60);
}

void mouse_init() {
    u8 status;
    asm volatile ("cli");
    mouse_wait(1);
    outb(0x64, 0xA8);
    mouse_wait(1);
    outb(0x64, 0x20);
    mouse_wait(0);
    status = (inb(0x60) | 2);
    mouse_wait(1);
    outb(0x64, 0x60);
    mouse_wait(1);
    outb(0x60, status);
    mouse_write(0xF6);
    mouse_read();
    mouse_write(0xF4);
    mouse_read();
    asm volatile ("sti");

    irq_register(12, mouse_handler);
}