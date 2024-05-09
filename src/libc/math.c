#include <libc/math.h>

i32 abs(i32 i) {
    return i < 0 ? -i : i;
}

u64 jdn(u8 days, u8 months, u8 years) {
    return (1461 * (years + 4800 + (months - 14) / 12)) / 4 + (367 * (months - 2 - 12 * ((months - 14) / 12))) / 12 - (3 * ((years + 4900 + (months - 14) / 12) / 100)) / 4 + days - 32075;
}