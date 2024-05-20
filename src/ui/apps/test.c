#include <ui/wm.h>
#include <ui/window.h>
#include <ui/apps/test.h>
#include <gfx/canvas.h>
#include <ui/controls/button.h>

void test_start() {
    window_t* wnd = wnd_create_new(250, 200, "Window test", WM_TITLEBAR | WM_BORDER | WM_CLOSABLE | WM_MINIMIZABLE | WM_RESIZABLE | WM_MAXIMIZABLE);
    wnd->paint = test_paint;
    wm_add_window(wnd);

    button_new(wnd, 25, 25, 40, 25, "test_button", "Test", test_button);
}

void test_paint(window_t* wnd) {
    cv_clear(wnd->contents, 0xC0C0C0);

    wm_paint_window(wnd);
}   

void test_button() {

}