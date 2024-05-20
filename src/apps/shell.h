#pragma once

#include <types.h>
#include <fs/vfs.h>
#include <lib/libc.h>
#include <lib/alloc.h>
#include <lib/printf.h>
#include <drivers/kb.h>
#include <apps/shell/help.h>
#include <apps/shell/clear.h>
#include <apps/shell/date.h>
#include <apps/shell/uptime.h>
#include <apps/shell/paint.h>
#include <apps/shell/ls.h>
#include <apps/shell/cat.h>
#include <apps/shell/cd.h>
#include <apps/shell/crash.h>
#include <apps/shell/gui.h>

extern const int shell_cmd_count;
extern const char *shell_cmds[];
extern const char *shell_cmd_descriptions[];

extern vfs_node* shell_current_dir;

void shell_init();
void shell_exec();