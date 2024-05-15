#pragma once

#include <lib/printf.h>
#include <drivers/kb.h>
#include <drivers/mouse.h>
#include <kernel/kernel.h>
#include <flanterm/flanterm.h>
#include <gfx/canvas.h>

void shell_cmd_paint(int argc, char** argv);