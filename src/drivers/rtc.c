/*
 * CREDITS: ilobilo on GitHub (original version)
 * https://github.com/ilobilo/
 */

#include <drivers/rtc.h>

volatile struct limine_boot_time_request boot_time_request = {
    .id = LIMINE_BOOT_TIME_REQUEST,
    .revision = 0,
};

const char *rtc_days[] = {
    "Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri"
};

const char *rtc_months[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

u64 bcd_to_bin(u64 value) {
    return (value >> 4) * 10 + (value & 15);
}

u64 rtc_century() {
    outb(0x70, 0x32);
    return bcd_to_bin(inb(RTC_PORT_REPLY));
}

u64 rtc_year() {
    outb(0x70, 0x09);
    return bcd_to_bin(inb(RTC_PORT_REPLY));
}

u64 rtc_month() {
    outb(RTC_PORT, 0x08);
    return bcd_to_bin(inb(RTC_PORT_REPLY));
}

u64 rtc_day() {
    outb(RTC_PORT, 0x07);
    return bcd_to_bin(inb(RTC_PORT_REPLY));
}

u64 rtc_day_of_week() {
    u64 year = rtc_year();
    u64 month = rtc_month();
    u64 day = rtc_day();

    if (month < 3) {
        month += 12;
        year--;
    }

    return (day + (13 * (month + 1) / 5) + (year % 100) + ((year % 100) / 4) + ((year / 100) / 4) + 5 * (year / 100)) % 7;
}

u64 rtc_hour() {
    outb(RTC_PORT, 0x04);
    return bcd_to_bin(inb(RTC_PORT_REPLY)) + 2;
}

u64 rtc_minute() {
    outb(RTC_PORT, 0x02);
    return bcd_to_bin(inb(RTC_PORT_REPLY));
}

u64 rtc_second() {
    outb(RTC_PORT, 0x00);
    return bcd_to_bin(inb(RTC_PORT_REPLY));
}

u64 rtc_time() {
    return rtc_hour() * 3600 + rtc_minute() * 60 + rtc_second();
}

uint64_t epoch()
{
    uint64_t seconds = rtc_second(), minutes = rtc_minute(), hours = rtc_hour() - 2, days = rtc_day() + 1, months = rtc_month(), years = rtc_year(), centuries = rtc_century();

    uint64_t jdn_current = jdn(days, months, centuries * 100 + years);
    uint64_t jdn_1970 = jdn(1, 1, (u16)1970);
    uint64_t diff = jdn_current - jdn_1970;

    return (diff * (60 * 60 * 24)) + hours * 3600 + minutes * 60 + seconds;
}

u64 seconds_since_boot() {
    return epoch() - boot_time_request.response->boot_time;
}

void rtc_sleep(u64 seconds) {
    u64 last_sec = rtc_time() + seconds;
    while (last_sec != rtc_time());
}