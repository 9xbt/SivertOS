#pragma once

#include <types.h>
#include <drivers/kb.h>
#include <lib/libc.h>
#include <lib/alloc.h>
#include <lib/printf.h>
#include <apps/shell/help.h>
#include <apps/shell/clear.h>
#include <apps/shell/date.h>
#include <apps/shell/uptime.h>
#include <apps/shell/paint.h>
#include <apps/shell/ls.h>
#include <apps/shell/crash.h>

extern const int shell_cmd_count;
extern const char *shell_cmds[];
extern const char *shell_cmd_descriptions[];

void shell_exec();