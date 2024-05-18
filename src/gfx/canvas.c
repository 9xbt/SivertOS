#include <lib/libc.h>
#include <lib/math.h>
#include <gfx/font.h>
#include <gfx/canvas.h>

void cv_clear(fb_t* fb, u32 color) {
    for (u64 y = 0; y < fb->height; y++)
        for (u64 x = 0; x < fb->width; x++)
            fb->address[y * fb->width + x] = color;
}

void cv_copy_portion(fb_t* dest, fb_t* src, u32 x, u32 y, u32 width, u32 height) {
    i32 _x = x < 0 ? 0 : x;
    i32 _y = y < 0 ? 0 : y;

    for (i32 i = 0; i < height; i++)
        memcpy(dest->address + ((i + _y) * dest->width + _x), src->address + ((i + _y) * src->width + _x), width * 4);
}

void cv_draw_line(fb_t* fb, u32 x1, u32 y1, u32 x2, u32 y2, u32 color) {
    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;

    while (x1 != x2 || y1 != y2) {
        if (x1 > 0 && y1 > 0 && x1 < fb->width && y1 < fb->height)
            fb->address[y1 * fb->width + x1] = color;

        int e2 = err;

        if (e2 > -dx) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dy) {
            err += dx;
            y1 += sy;
        }
    }
}

void cv_draw_filled_rectangle(fb_t* fb, i32 x, i32 y, u32 width, u32 height, u32 color) {
    if (x < 0) x = 0;
    if (y < 0) y = 0;

    for (i32 i = y; i < y + height; i++) {
        for (i32 o = x; o < x + width; o++)
            fb->address[i * fb->width + o] = color;
    }
}

void cv_draw_image(fb_t* fb, i32 x, i32 y, fb_t* bmp) {
    i32 _x = x < 0 ? 0 : x;
    i32 _y = y < 0 ? 0 : y;

    for (i32 i = 0; i < bmp->height; i++)
        memcpy(fb->address + ((i + _y) * fb->width + _x), bmp->address + (i * bmp->width), bmp->width * 4);
}

void cv_draw_image_alpha(fb_t* fb, fb_t* bmp, i32 x, i32 y) {
    i32 _x = x < 0 ? 0 : x;
    i32 _y = y < 0 ? 0 : y;

    for (i32 i = 0; i < bmp->height; i++)
        for (i32 o = 0; o < bmp->width; o++) {
            if ((bmp->address[i * bmp->height + o] >> 24) & 0xFF != 0)
                // TODO: add color blending
                fb->address[(i + _y) * fb->width + _x + o] = bmp->address[i * bmp->height + o];
        }
}

void cv_draw_char(fb_t* fb, font_t* font, i32 x, i32 y, char c, u32 color) {
    i32 _x = x < 0 ? 0 : x;
    i32 _y = y < 0 ? 0 : y;

    if (c < 0x20 || c > 0x7F) return;  // Skip non-printable characters

    for (int i = 0; i < font->height; i++) {
        for (int o = 0; o < font->width; o++) {
            // Calculate the index in the font data
            int index = (c - 0x20) * font->height + i;
            // Check if the bit is set in the font data
            if (font->data[index] & (1 << (7 - o))) {
                // Draw the pixel if within bounds
                if (_x + o >= 0 && _x + o < fb->width && _y + i >= 0 && _y + i < fb->height) {
                    fb->address[(_y + i) * fb->width + (_x + o)] = color;
                }
            }
        }
    }
}

void cv_draw_string(fb_t* fb, font_t* font, i32 x, i32 y, char* str, u32 color) {
    for (int i = 0; i < strlen(str); i++) {
        char c = str[i];

        cv_draw_char(fb, font, x + (i * font->width), y, c, color);
    }
}