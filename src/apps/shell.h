#pragma once

#include <types.h>
#include <drivers/kb.h>
#include <lib/printf.h>
#include <lib/libc.h>
#include <apps/shell/help.h>
#include <apps/shell/clear.h>
#include <apps/shell/date.h>
#include <apps/shell/uptime.h>
#include <apps/shell/paint.h>

extern const char *shell_cmds[];
extern const char *shell_cmd_descriptions[];

void shell_exec();