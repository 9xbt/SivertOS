#include <gfx/canvas.h>

void cv_draw_line(u32* fb, u32 fb_width, u32 x1, u32 y1, u32 x2, u32 y2, u32 color) {
    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;

    while (x1 != x2 || y1 != y2)
    {
        if (x1 > 0 && y1 > 0 && x1 < fb_width && y1 < 768)
            fb[y1 * fb_width + x1] = color;

        int e2 = err;

        if (e2 > -dx)
        {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dy)
        {
            err += dx;
            y1 += sy;
        }
    }
}