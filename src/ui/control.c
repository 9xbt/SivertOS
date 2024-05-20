#include <ui/control.h>
#include <lib/alloc.h>

control_t* ctl_create_new(u32 width, u32 height, char* name, char* text) {
    control_t* ctl = (control_t*)kmalloc(sizeof(control_t));
    ctl->contents = fb_create_new(width, height);
    ctl->x = 50;
    ctl->y = 50;
    ctl->name = name;
    ctl->text = text;

    return ctl;
}

void ctl_destroy(control_t* ctl) {
    fb_destroy(ctl->contents);
    kfree(ctl);
}