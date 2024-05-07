#include <drivers/kb.h>

u8 kb_key_pressed = false;
u8 kb_current_char = '\0';
u8 kb_caps = false;
u8 kb_shift = false;

void kb_handler(registers* regs) {
    (void)regs;

    u8 key = inb(0x60);

    if (!(key & 0x80)) {
        // Key was pressed
        switch (key) {
            case 0x2a:
                // Left shift
                kb_shift = true;
                break;
            case 0x36:
                // Right shift
                kb_shift = true;
                break;
            case 0x3a:
                // Caps
                kb_caps = !kb_caps;
                break;
            default:
                // Letter(?)
                kb_key_pressed = true;
                if (kb_shift) kb_current_char = kb_map_keys_shift[key];
                else if (kb_caps) kb_current_char = kb_map_keys_caps[key];
                else kb_current_char = kb_map_keys[key];
                break;
        }
    } else {
        switch (key) {
            case 0xaa:
                // Left shift released
                kb_shift = false;
                break;
            case 0xb6:
                // Right shift released
                kb_shift = false;
                break;
        }
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
    printf("kb_get_string called\n");

    memset(buf, NULL, n);
    size_t pos = 0;

    u8 reading = true;
    do {
        if (kb_get_char()) {
            printf("yee\r");

            for (int i = 0; i < 1000000; i++) {
                asm volatile ("nop");
            }
        }
        else {
            printf("noo\r");
        }

        continue;

        if (!kb_key_pressed)
            continue;
        kb_key_pressed = false;

        switch(kb_current_char) {
            case '\n':
                printf("%s", "\n");
                return;

            case '\b':
                if (pos == 0)
                    break;
            
                printf("%c%s", kb_current_char, " \b");

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

        printf("kb_get_string loop\n");
    } while (reading);

    printf("kb_get_string ended\n");
}

void kb_init() {
    irq_register(1, kb_handler);
}