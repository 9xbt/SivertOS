#include <gfx/font.h>
#include <lib/alloc.h>

font_t* font_create(u8* data, u8 width, u8 height) {
    font_t* font = kmalloc(sizeof(font_t));
    font->data = data;
    font->width = width;
    font->height = height;

    return font;
}

void font_destroy(font_t* font) {
    kfree(font);
}