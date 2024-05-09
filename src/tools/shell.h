#pragma once

#include <types.h>
#include <drivers/kb.h>
#include <libc/printf.h>
#include <libc/string.h>
#include <tools/shell/help.h>
#include <tools/shell/clear.h>
#include <tools/shell/paint.h>

extern const char *shell_cmds[];
extern const char *shell_cmd_descriptions[];

void shell_exec();