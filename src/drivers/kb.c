#include <drivers/kb.h>

u8 kb_key_pressed = false;
u8 kb_current_char = '\0';
u8 kb_caps = false;
u8 kb_shift = false;

void kb_handler(registers* regs) {
    (void)regs;

    if (inb(0x64) & 1) {
        u8 key = inb(0x60);

        if (!(key & 0x80)) {
            /* Key was pressed */
            switch (key) {
                case 0x2a:
                    /* Left shift */
                    kb_shift = true;
                    break;
                case 0x36:
                    /* Right shift */
                    kb_shift = true;
                    break;
                case 0x3a:
                    /* Caps */ 
                    kb_caps = !kb_caps;
                    break;
                default:
                    /* Letter(?) */
                    kb_key_pressed = true;
                    if (kb_shift) kb_current_char = kb_map_keys_shift[key];
                    else if (kb_caps) kb_current_char = kb_map_keys_caps[key];
                    else kb_current_char = kb_map_keys[key];
                    break;
            }
        } else {
            switch (key) {
                case 0xaa:
                    /* Left shift released */
                    kb_shift = false;
                    break;
                case 0xb6:
                    /* Right shift released */
                    kb_shift = false;
                    break;
            }
        }
    }
    else {
        kb_current_char = 0;
        kb_key_pressed = false;
    }
}

char kb_get_char() {
    if (kb_key_pressed) {
        kb_key_pressed = false;
        return kb_current_char;
    } else {
        return '\0';
    }
}

void kb_get_string(char* buf, size_t n) {
    memset(buf, 0, n);
    size_t pos = 0;

    bool reading = true;
    do {
        asm volatile ("hlt");

        switch(kb_current_char) {
            case '\0':
                break;

            case '\n':
                printf("\n");
                kb_current_char = 0;
                return;

            case '\b':
                if (pos <= 0) {
                    break;
                }
            
                printf("%c \b", kb_current_char);

                buf[pos] = 0;
                pos--;
                break;

            default:
                if (pos >= n - 1)
                    break;

                printf("%c", kb_current_char);

                buf[pos] = kb_current_char;
                pos++;
                break;
        }

        kb_current_char = 0;
    } while (reading);
}

void kb_init() {
    irq_register(1, kb_handler);

    printf("\033[92m[  OK  ]\033[0m Keyboard Driver Initialized.\n");
}