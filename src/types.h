#pragma once

#include <inttypes.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

// Holy-C like types

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef u64 usize;
typedef i64 isize;

typedef uintptr_t uptr;
typedef intptr_t iptr;

typedef char symbol[];