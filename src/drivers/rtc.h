#pragma once

#include <types.h>
#include <limine.h>
#include <arch/x86_64/io.h>
#include <kernel/kernel.h>

#define RTC_PORT 0x70
#define RTC_PORT_REPLY 0x71

extern const char *rtc_days[];
extern const char *rtc_months[];

u64 rtc_century();
u64 rtc_year();
u64 rtc_month();
u64 rtc_day();
u64 rtc_hour();
u64 rtc_minute();
u64 rtc_second();
u64 rtc_time();
u64 seconds_since_boot();
void rtc_sleep(u64 seconds);